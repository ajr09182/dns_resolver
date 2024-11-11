#include "DNSResolver.hpp"
#include <iostream>
#include <iomanip>
#include <string>

// ANSI color codes for prettier output
namespace Color
{
    const std::string Reset = "\033[0m";
    const std::string Bold = "\033[1m";
    const std::string Blue = "\033[34m";
    const std::string Green = "\033[32m";
    const std::string Red = "\033[31m";
}

void printRecord(const DNSRecord &record)
{
    std::cout << Color::Bold << "Record Details:" << Color::Reset << "\n";
    std::cout << "  Name: " << Color::Blue << record.name << Color::Reset << "\n";
    std::cout << "  Type: " << Color::Blue << static_cast<int>(record.type) << Color::Reset << "\n";
    std::cout << "  TTL:  " << record.ttl << "\n";

    std::cout << "  Data: ";
    if (record.data.empty())
    {
        std::cout << Color::Red << "No data" << Color::Reset << "\n";
    }
    else
    {
        std::cout << Color::Green;
        for (const auto &data : record.data)
        {
            std::cout << data << " ";
        }
        std::cout << Color::Reset << "\n";
    }

    switch (record.type)
    {
    case DNSRecordType::MX:
        std::cout << "  MX Details:\n"
                  << "    Preference: " << Color::Blue << record.mx.preference << Color::Reset << "\n"
                  << "    Exchange:   " << Color::Blue << record.mx.exchange << Color::Reset << "\n";
        break;

    case DNSRecordType::SOA:
        std::cout << "  SOA Details:\n"
                  << "    MNAME:  " << Color::Blue << record.soa.mname << Color::Reset << "\n"
                  << "    RNAME:  " << Color::Blue << record.soa.rname << Color::Reset << "\n"
                  << "    Serial: " << Color::Blue << record.soa.serial << Color::Reset << "\n";
        break;
    }

    std::cout << std::string(50, '-') << "\n";
}

int main()
{
    try
    {
        // Initialize resolver with default config
        DNSResolver::Config config;
        config.enableParallelQueries = true;
        config.enableDNSSEC = true;
        config.connectionPoolSize = 10;
        config.nameservers = {
            "8.8.8.8", "8.8.4.4",              // Google DNS
            "1.1.1.1", "1.0.0.1",              // Cloudflare DNS
            "9.9.9.9",                         // Quad9 DNS
            "208.67.222.222", "208.67.220.220" // OpenDNS
        };

        DNSResolver resolver(config);

        // Available record types
        std::vector<DNSRecordType> types = {
            DNSRecordType::A,
            DNSRecordType::AAAA,
            DNSRecordType::MX,
            DNSRecordType::TXT};

        // Get domain from user
        std::string domain;
        std::cout << Color::Bold << "Enter domain to resolve: " << Color::Reset;
        std::cin >> domain;

        // Standard resolution
        std::cout << Color::Bold << "\nResolving " << domain << "...\n"
                  << Color::Reset;
        for (auto type : types)
        {
            std::cout << "\nQuerying records of type " << static_cast<int>(type) << "...\n";
            auto records = resolver.resolve(domain, type);

            if (records.empty())
            {
                std::cout << Color::Red << "No records found.\n"
                          << Color::Reset;
                continue;
            }

            std::cout << Color::Green << "Found " << records.size() << " record(s)\n"
                      << Color::Reset;
            for (const auto &record : records)
            {
                printRecord(record);
            }
        }

        // Async resolution
        std::cout << Color::Bold << "\nPerforming async resolution...\n"
                  << Color::Reset;
        auto futureRecords = resolver.resolveAsync(domain);
        auto asyncRecords = futureRecords.get();

        if (asyncRecords.empty())
        {
            std::cout << Color::Red << "No records found in async resolution.\n"
                      << Color::Reset;
        }
        else
        {
            std::cout << Color::Green << "Found " << asyncRecords.size()
                      << " record(s) in async resolution\n"
                      << Color::Reset;
            for (const auto &record : asyncRecords)
            {
                printRecord(record);
            }
        }

        // Print statistics
        auto stats = resolver.getStatistics();
        std::cout << Color::Bold << "\nResolver Statistics:\n"
                  << Color::Reset
                  << "  Total Queries: " << stats.totalQueries << "\n"
                  << "  Cache Hits:    " << stats.cacheHits << "\n"
                  << "  Cache Misses:  " << stats.cacheMisses << "\n"
                  << "  Failed:        " << Color::Red << stats.failedQueries
                  << Color::Reset << "\n";
    }
    catch (const std::exception &e)
    {
        std::cerr << Color::Red << "Error: " << e.what() << Color::Reset << std::endl;
        return 1;
    }

    return 0;
}