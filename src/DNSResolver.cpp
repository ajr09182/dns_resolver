#include "DNSResolver.hpp"
#include <iostream>

DNSResolver::DNSResolver(const Config &config)
    : config(config), cache(1000) // Default cache size of 1000 entries
      ,
      connectionPool(config.connectionPoolSize, config.nameservers), logger(std::make_shared<Logger>("dns-resolver.log"))
{
}

std::vector<DNSRecord> DNSResolver::resolveParallel(
    const std::string &domain,
    DNSRecordType type)
{

    std::vector<std::future<std::vector<DNSRecord>>> futures;

    // Query each nameserver in parallel
    for (const auto &ns : config.nameservers)
    {
        futures.push_back(std::async(std::launch::async,
                                     [this, &domain, type, &ns]()
                                     {
                                         return queryNameserver(ns, domain, type);
                                     }));
    }

    // Collect and combine results
    std::vector<DNSRecord> combinedRecords;
    for (auto &future : futures)
    {
        try
        {
            auto records = future.get();
            combinedRecords.insert(combinedRecords.end(),
                                   records.begin(),
                                   records.end());
        }
        catch (const std::exception &e)
        {
            logger->log(LogLevel::WARNING,
                        "Parallel resolution failed: " + std::string(e.what()));
        }
    }

    return combinedRecords;
}

std::vector<DNSRecord> DNSResolver::performRecursiveResolution(
    const std::string &domain,
    DNSRecordType type,
    size_t depth,
    const std::string &nameserver)
{

    if (depth >= config.maxRecursion)
    {
        throw std::runtime_error("Maximum recursion depth exceeded");
    }

    auto records = queryNameserver(nameserver, domain, type);

    // If we got NS records, we need to query them
    bool hasNSRecords = false;
    for (const auto &record : records)
    {
        if (record.type == DNSRecordType::NS)
        {
            hasNSRecords = true;
            auto nsRecords = performRecursiveResolution(
                domain, type, depth + 1, record.data[0]);
            records.insert(records.end(), nsRecords.begin(), nsRecords.end());
        }
    }

    return records;
}

std::vector<DNSRecord> DNSResolver::queryNameserver(
    const std::string &nameserver,
    const std::string &domain,
    DNSRecordType type)
{

    logger->log(LogLevel::DEBUG, "Querying " + nameserver + " for " + domain);

    auto conn = connectionPool.acquire();

    if (!conn)
    {
        logger->log(LogLevel::ERROR, "Failed to acquire connection from pool.");
        throw std::runtime_error("Connection acquisition failed.");
    }

    try
    {
        // Attempt to perform the query
        conn->query(domain, type);

        // Retrieve the response
        auto response = conn->getResponse();

        // Check if the response is empty
        if (response.empty())
        {
            logger->log(LogLevel::WARNING, "No records returned for " + domain);
        }
        else
        {
            logger->log(LogLevel::DEBUG, "Records returned: " + std::to_string(response.size()));
        }

        connectionPool.release(conn);
        return response;
    }
    catch (const std::exception &e)
    {
        logger->log(LogLevel::ERROR, "Query failed: " + std::string(e.what()));
        connectionPool.release(conn);
        throw; // Re-throw the exception for further handling if needed
    }
}

bool DNSResolver::followCNAMEChain(
    std::vector<DNSRecord> &records,
    const std::string &originalDomain,
    size_t depth)
{

    if (depth >= config.maxRecursion)
    {
        return false;
    }

    for (const auto &record : records)
    {
        if (record.type == DNSRecordType::CNAME)
        {
            auto cnameRecords = resolve(record.data[0], DNSRecordType::A);
            records.insert(records.end(), cnameRecords.begin(), cnameRecords.end());
            return followCNAMEChain(records, originalDomain, depth + 1);
        }
    }

    return true;
}

std::future<std::vector<DNSRecord>> DNSResolver::resolveAsync(
    const std::string &domainName,
    DNSRecordType type)
{

    return std::async(std::launch::async,
                      [this, domainName, type]()
                      {
                          return resolve(domainName, type);
                      });
}

std::vector<DNSRecord> DNSResolver::resolve(
    const std::string &domainName,
    DNSRecordType type)
{

    auto start = std::chrono::steady_clock::now();
    stats.incrementTotalQueries();

    try
    {
        // Check cache first
        std::vector<DNSRecord> records;
        if (cache.get(domainName + "_" + std::to_string(static_cast<int>(type)), records))
        {
            stats.incrementCacheHits();
            return records;
        }
        stats.incrementCacheMisses();

        // Perform resolution
        records = config.enableParallelQueries ? resolveParallel(domainName, type) : performRecursiveResolution(domainName, type, 0, config.nameservers[0]);

        // Handle CNAME chain
        if (!followCNAMEChain(records, domainName, 0))
        {
            throw std::runtime_error("CNAME resolution failed");
        }

        // // Validate DNSSEC if enabled
        // if (config.enableDNSSEC && !DNSQuery::validateDNSSEC(domainName, records))
        // {
        //     throw std::runtime_error("DNSSEC validation failed");
        // }

        // Cache results
        cache.put(domainName + "_" + std::to_string(static_cast<int>(type)), records);

        auto end = std::chrono::steady_clock::now();
        stats.addResolutionTime(
            std::chrono::duration_cast<std::chrono::nanoseconds>(end - start));

        return records;
    }
    catch (const std::exception &e)
    {
        stats.incrementFailedQueries();
        logger->log(LogLevel::ERROR,
                    "Resolution failed for " + domainName + ": " + e.what());
        throw;
    }
}

Statistics DNSResolver::getStatistics() const
{
    return stats;
}
