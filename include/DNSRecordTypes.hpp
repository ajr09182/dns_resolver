#pragma once
#include <string>
#include <vector>
#include <cstdint>

enum class DNSRecordType : uint16_t
{
    A = 1,
    NS = 2,
    CNAME = 5,
    PTR = 12,
    MX = 15,
    TXT = 16,
    AAAA = 28,
    SRV = 33,
    SOA = 6,
    RRSIG = 46,
    NSEC = 47,
    DNSKEY = 48,
};

struct DNSRecord
{
    DNSRecordType type;
    std::string name;
    std::vector<std::string> data;
    uint32_t ttl;

    struct
    {
        uint16_t preference;
        std::string exchange;
    } mx;

    struct
    {
        std::string mname;
        std::string rname;
        uint32_t serial;
        uint32_t refresh;
        uint32_t retry;
        uint32_t expire;
        uint32_t minimum;
    } soa;

    bool operator==(const DNSRecord &other) const
    {
        return type == other.type &&
               name == other.name &&
               data == other.data;
    }
};