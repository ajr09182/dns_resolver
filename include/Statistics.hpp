#pragma once
#include <chrono>
#include <atomic>

class Statistics {
public:
    Statistics() = default;

    // Copy constructor - copy atomic values
    Statistics(const Statistics& other)
        : totalQueries(other.totalQueries.load())
        , cacheHits(other.cacheHits.load())
        , cacheMisses(other.cacheMisses.load())
        , failedQueries(other.failedQueries.load())
        , totalResolutionTime(other.totalResolutionTime) {}

    // Copy assignment operator
    Statistics& operator=(const Statistics& other) {
        if (this != &other) {
            totalQueries.store(other.totalQueries.load());
            cacheHits.store(other.cacheHits.load());
            cacheMisses.store(other.cacheMisses.load());
            failedQueries.store(other.failedQueries.load());
            totalResolutionTime = other.totalResolutionTime;
        }
        return *this;
    }

    // Increment operators
    void incrementTotalQueries() { ++totalQueries; }
    void incrementCacheHits() { ++cacheHits; }
    void incrementCacheMisses() { ++cacheMisses; }
    void incrementFailedQueries() { ++failedQueries; }

    // Getters
    uint64_t getTotalQueries() const { return totalQueries.load(); }
    uint64_t getCacheHits() const { return cacheHits.load(); }
    uint64_t getCacheMisses() const { return cacheMisses.load(); }
    uint64_t getFailedQueries() const { return failedQueries.load(); }
    std::chrono::nanoseconds getResolutionTime() const { return totalResolutionTime; }

    void addResolutionTime(std::chrono::nanoseconds time) {
        totalResolutionTime += time;
    }

    double getAverageResolutionTime() const {
    uint64_t queries = totalQueries.load();
    if (queries == 0) return 0.0;
    return std::chrono::duration<double>(totalResolutionTime).count() / queries;
    }

    double getCacheHitRate() const {
    uint64_t queries = totalQueries.load();
    if (queries == 0) return 0.0;
    return static_cast<double>(cacheHits.load()) / queries;
    }

public:
    std::atomic<uint64_t> totalQueries{0};
    std::atomic<uint64_t> cacheHits{0};
    std::atomic<uint64_t> cacheMisses{0};
    std::atomic<uint64_t> failedQueries{0};
    std::chrono::nanoseconds totalResolutionTime{0};
};