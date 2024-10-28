#pragma once
#include "DNSCache.hpp"
#include "DNSQuery.hpp"
#include "ConnectionPool.hpp"
#include "Logger.hpp"
#include "Statistics.hpp"  // Added explicit include
#include <future>
#include <thread>

class DNSResolver {
public:
    struct Config {
        size_t maxRecursion = 10;
        size_t queryTimeout = 5000;
        size_t maxRetries = 3;
        size_t connectionPoolSize = 10;
        bool enableDNSSEC = true;
        bool enableParallelQueries = true;
        std::vector<std::string> nameservers;
    };

    explicit DNSResolver(const Config& config);

    std::vector<DNSRecord> resolve(const std::string& domainName,
                                 DNSRecordType type = DNSRecordType::A);

    std::future<std::vector<DNSRecord>> resolveAsync(
        const std::string& domainName,
        DNSRecordType type = DNSRecordType::A);

    Statistics getStatistics() const;
    void clearCache();
    void setConfig(const Config& config);

private:
    Config config;
    DNSCache cache;
    ConnectionPool connectionPool;
    std::shared_ptr<Logger> logger;
    Statistics stats;

    std::vector<DNSRecord> performRecursiveResolution(
        const std::string& domain,
        DNSRecordType type,
        size_t depth,
        const std::string& nameserver);

    std::vector<DNSRecord> queryNameserver(
        const std::string& nameserver,
        const std::string& domain,
        DNSRecordType type);

    std::vector<DNSRecord> resolveParallel(
        const std::string& domain,
        DNSRecordType type);

    bool followCNAMEChain(
        std::vector<DNSRecord>& records,
        const std::string& originalDomain,
        size_t depth);
};