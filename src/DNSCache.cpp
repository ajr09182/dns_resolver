// DNSCache.cpp
#include "DNSCache.hpp"
#include <algorithm>
#include <iostream>

DNSCache::DNSCache(size_t maxSize) : maxCacheSize(maxSize) {}

bool DNSCache::get(const std::string &key, std::vector<DNSRecord> &records)
{
    std::lock_guard<std::mutex> lock(cacheMutex);

    auto it = cache.find(key);
    if (it == cache.end())
    {
        return false;
    }

    auto now = std::chrono::system_clock::now();
    std::vector<DNSRecord> validRecords;

    // Check each record's TTL
    for (const auto &record : it->second.records)
    {
        auto recordExpiry = it->second.insertTime + std::chrono::seconds(record.ttl);
        if (now < recordExpiry)
        {
            // Calculate remaining TTL
            auto elapsedSeconds = std::chrono::duration_cast<std::chrono::seconds>(
                                      now - it->second.insertTime)
                                      .count();
            DNSRecord updatedRecord = record;
            updatedRecord.ttl = std::max(0u,
                                         record.ttl - static_cast<uint32_t>(elapsedSeconds));
            validRecords.push_back(updatedRecord);
        }
    }

    // If all records have expired, remove the entry
    if (validRecords.empty())
    {
        cache.erase(it);
        auto lruIt = std::find(lruList.begin(), lruList.end(), key);
        if (lruIt != lruList.end())
        {
            lruList.erase(lruIt);
        }
        return false;
    }

    records = validRecords;
    it->second.lastAccess = now;
    updateLRU(key);
    return true;
}

void DNSCache::put(const std::string &key, const std::vector<DNSRecord> &records)
{
    if (records.empty())
    {
        return;
    }

    std::lock_guard<std::mutex> lock(cacheMutex);

    auto now = std::chrono::system_clock::now();

    // Create cache entry
    CacheEntry entry{
        records,
        now, // Insert time
        now  // Last access time
    };

    // Ensure we don't exceed max cache size
    while (cache.size() >= maxCacheSize && !lruList.empty())
    {
        evictLRU();
    }

    // Update or insert the entry
    cache[key] = entry;
    updateLRU(key);
}

void DNSCache::updateLRU(const std::string &key)
{
    auto it = std::find(lruList.begin(), lruList.end(), key);
    if (it != lruList.end())
    {
        lruList.erase(it);
    }
    lruList.push_front(key);
}

void DNSCache::evictLRU()
{
    if (!lruList.empty())
    {
        auto key = lruList.back();
        cache.erase(key);
        lruList.pop_back();
    }
}

void DNSCache::evictExpired()
{
    std::lock_guard<std::mutex> lock(cacheMutex);
    auto now = std::chrono::system_clock::now();

    for (auto it = cache.begin(); it != cache.end();)
    {
        bool hasValidRecords = false;
        for (const auto &record : it->second.records)
        {
            auto recordExpiry = it->second.insertTime + std::chrono::seconds(record.ttl);
            if (now < recordExpiry)
            {
                hasValidRecords = true;
                break;
            }
        }

        if (!hasValidRecords)
        {
            auto lruIt = std::find(lruList.begin(), lruList.end(), it->first);
            if (lruIt != lruList.end())
            {
                lruList.erase(lruIt);
            }
            it = cache.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void DNSCache::clear()
{
    std::lock_guard<std::mutex> lock(cacheMutex);
    cache.clear();
    lruList.clear();
}

size_t DNSCache::size() const
{
    std::lock_guard<std::mutex> lock(cacheMutex);
    return cache.size();
}