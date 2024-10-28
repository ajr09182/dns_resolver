// DNSCache.hpp
#pragma once
#include "DNSRecordTypes.hpp"
#include <unordered_map>
#include <chrono>
#include <mutex>
#include <list>
#include <string>

class DNSCache
{
public:
    struct CacheEntry
    {
        std::vector<DNSRecord> records;
        std::chrono::system_clock::time_point insertTime;
        std::chrono::system_clock::time_point lastAccess;
    };

    explicit DNSCache(size_t maxSize = 1000);

    bool get(const std::string &key, std::vector<DNSRecord> &records);
    void put(const std::string &key, const std::vector<DNSRecord> &records);
    void evictExpired();
    void clear();
    size_t size() const;

    // Static helper to create consistent cache keys
    static std::string createCacheKey(const std::string &domain, uint16_t type)
    {
        return domain + "_" + std::to_string(type);
    }

private:
    std::unordered_map<std::string, CacheEntry> cache;
    std::list<std::string> lruList;
    mutable std::mutex cacheMutex;
    const size_t maxCacheSize;

    void evictLRU();
    void updateLRU(const std::string &key);
};