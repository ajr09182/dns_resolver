#include "DNSResolver.hpp"
#include <iostream>

void printRecord(const DNSRecord &record)
{
    std::cout << "Name: " << record.name << "\n"
              << "Type: " << static_cast<int>(record.type) << "\n"
              << "TTL: " << record.ttl << "\n"
              << "Data: ";

    if (record.data.empty())
    {
        std::cout << "No data\n";
    }
    else
    {
        for (const auto &data : record.data)
        {
            std::cout << data << " ";
        }
        std::cout << "\n";
    }

    // Print type-specific data
    switch (record.type)
    {
    case DNSRecordType::MX:
        std::cout << "MX Preference: " << record.mx.preference << "\n"
                  << "MX Exchange: " << record.mx.exchange << "\n";
        break;

    case DNSRecordType::SOA:
        std::cout << "SOA MNAME: " << record.soa.mname << "\n"
                  << "SOA RNAME: " << record.soa.rname << "\n"
                  << "SOA Serial: " << record.soa.serial << "\n";
        break;
    }

    std::cout << "----------------------------\n";
}

int main()
{
    try
    {
        DNSResolver::Config config;
        config.enableParallelQueries = true;
        config.enableDNSSEC = true;
        config.connectionPoolSize = 10;
        config.nameservers = {
            "8.8.8.8",        // Google Public DNS
            "8.8.4.4",        // Google Public DNS
            "1.1.1.1",        // Cloudflare DNS
            "1.0.0.1",        // Cloudflare DNS
            "9.9.9.9",        // Quad9 DNS
            "208.67.222.222", // OpenDNS
            "208.67.220.220"  // OpenDNS
        };

        DNSResolver resolver(config);

        // Test different record types
        std::vector<DNSRecordType> types = {
            DNSRecordType::A,
            DNSRecordType::AAAA,
            DNSRecordType::MX,
            DNSRecordType::TXT};

        std::string domain = "";
        std::cout << "Enter domain to resolve: ";
        std::cin >> domain;

        for (auto type : types)
        {
            std::cout << "Resolving " << domain << " for type "
                      << static_cast<int>(type) << "...\n";

            auto records = resolver.resolve(domain, type);
            std::cout << "Records found: " << records.size() << "\n";

            if (records.empty())
            {
                std::cout << "No records returned for type " << static_cast<int>(type) << ".\n";
            }

            for (const auto &record : records)
            {
                printRecord(record);
            }
        }

        // Test async resolution
        std::cout << "Starting async resolution...\n";
        std::string domainAsync = "";
        std::cout << "Enter domain to resolve asynchronously: ";
        std::cin >> domainAsync;
        auto futureRecords = resolver.resolveAsync(domainAsync);
        auto googleRecords = futureRecords.get();
        std::cout << "Async resolution completed.\n";

        std::cout << "Async resolution results:\n";
        std::cout << "Records found: " << googleRecords.size() << "\n";
        if (googleRecords.empty())
        {
            std::cout << "No records returned.\n";
        }

        for (const auto &record : googleRecords)
        {
            printRecord(record);
        }

        // Print statistics
        auto stats = resolver.getStatistics();
        std::cout << "\nStatistics:\n"
                  << "Total queries: " << stats.totalQueries << "\n"
                  << "Cache hits: " << stats.cacheHits << "\n"
                  << "Cache misses: " << stats.cacheMisses << "\n"
                  << "Failed queries: " << stats.failedQueries << "\n";
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
