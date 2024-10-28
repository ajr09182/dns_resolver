#pragma once
#include "DNSRecordTypes.hpp"
#include <vector>
#include <string>
#include <cstdint>
#include <random>

class DNSQuery
{
public:
    struct QueryPacket
    {
        uint16_t id;
        uint16_t flags;
        std::string domain;
        DNSRecordType type;
    };

    static std::vector<uint8_t> buildQuery(const std::string &domain,
                                           DNSRecordType type);
    static std::vector<DNSRecord> parseResponse(const std::vector<uint8_t> &response);
    // static bool validateDNSSEC(const std::string &domain,
    //                            const std::vector<DNSRecord> &records);

private:
    static std::vector<uint8_t> encodeDomainName(const std::string &domain);
    static std::string decodeDomainName(const std::vector<uint8_t> &response, size_t &offset);
    static uint16_t generateQueryId();
    static void write16bits(std::vector<uint8_t> &buffer, size_t offset, uint16_t value);
    static uint16_t read16bits(const std::vector<uint8_t> &buffer, size_t &offset);
};
