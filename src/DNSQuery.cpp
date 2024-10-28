#include "DNSQuery.hpp"
#include <random>
#include <cstring>
#include <stdexcept>
#include <arpa/inet.h>
#include <netinet/in.h>

void DNSQuery::write16bits(std::vector<uint8_t> &buffer, size_t offset, uint16_t value)
{
    buffer[offset] = (value >> 8) & 0xFF;
    buffer[offset + 1] = value & 0xFF;
}

uint16_t DNSQuery::read16bits(const std::vector<uint8_t> &buffer, size_t &offset)
{
    uint16_t value = (buffer[offset] << 8) | buffer[offset + 1];
    offset += 2;
    return value;
}

std::vector<uint8_t> DNSQuery::buildQuery(const std::string &domain, DNSRecordType type)
{
    std::vector<uint8_t> query;
    query.resize(12); // DNS header size

    uint16_t id = generateQueryId();
    uint16_t flags = 0x0100; // Standard query with recursion desired

    write16bits(query, 0, id);
    write16bits(query, 2, flags);
    write16bits(query, 4, 1);  // One question
    write16bits(query, 6, 0);  // No answers
    write16bits(query, 8, 0);  // No authority records
    write16bits(query, 10, 0); // No additional records

    // Add domain name
    auto encodedDomain = encodeDomainName(domain);
    query.insert(query.end(), encodedDomain.begin(), encodedDomain.end());

    // Add query type and class
    query.resize(query.size() + 4);
    write16bits(query, query.size() - 4, static_cast<uint16_t>(type));
    write16bits(query, query.size() - 2, 1); // IN class

    return query;
}

std::string DNSQuery::decodeDomainName(const std::vector<uint8_t> &response, size_t &offset)
{
    std::string domain;
    uint8_t labelLength;

    while ((labelLength = response[offset++]) > 0)
    {
        if ((labelLength & 0xC0) == 0xC0)
        {
            // Handle compression
            uint16_t pointer = ((labelLength & 0x3F) << 8) | response[offset++];
            size_t savedOffset = offset;
            offset = pointer;
            domain += decodeDomainName(response, offset);
            offset = savedOffset;
            return domain;
        }

        if (!domain.empty())
        {
            domain += ".";
        }
        domain.append(reinterpret_cast<const char *>(&response[offset]), labelLength);
        offset += labelLength;
    }

    return domain;
}

std::vector<DNSRecord> DNSQuery::parseResponse(const std::vector<uint8_t> &response)
{
    if (response.size() < 12)
    {
        throw std::runtime_error("Response too short");
    }

    std::vector<DNSRecord> records;
    size_t offset = 0;

    // Parse header
    uint16_t id = read16bits(response, offset);
    uint16_t flags = read16bits(response, offset);
    uint16_t qdcount = read16bits(response, offset);
    uint16_t ancount = read16bits(response, offset);
    uint16_t nscount = read16bits(response, offset);
    uint16_t arcount = read16bits(response, offset);

    // Check for errors
    if ((flags & 0x000F) != 0)
    {
        throw std::runtime_error("DNS server returned error code: " +
                                 std::to_string(flags & 0x000F));
    }

    // Skip questions
    for (uint16_t i = 0; i < qdcount; ++i)
    {
        std::string name = decodeDomainName(response, offset);
        offset += 4; // Skip qtype and qclass
    }

    // Parse answers
    for (uint16_t i = 0; i < ancount; ++i)
    {
        DNSRecord record;
        record.name = decodeDomainName(response, offset);

        record.type = static_cast<DNSRecordType>(read16bits(response, offset));
        offset += 2; // Skip class

        // Read TTL (32 bits)
        record.ttl = (response[offset] << 24) | (response[offset + 1] << 16) |
                     (response[offset + 2] << 8) | response[offset + 3];
        offset += 4;

        uint16_t rdlength = read16bits(response, offset);

        switch (record.type)
        {
        case DNSRecordType::A:
            if (rdlength == 4)
            {
                std::string ipv4 = std::to_string(response[offset]) + "." +
                                   std::to_string(response[offset + 1]) + "." +
                                   std::to_string(response[offset + 2]) + "." +
                                   std::to_string(response[offset + 3]);
                record.data.push_back(ipv4);
            }
            break;

        case DNSRecordType::AAAA:
            if (rdlength == 16)
            {
                char ipv6[INET6_ADDRSTRLEN];
                unsigned char ipv6_bytes[16];
                std::copy(response.begin() + offset,
                          response.begin() + offset + 16,
                          ipv6_bytes);

                if (inet_ntop(AF_INET6, ipv6_bytes, ipv6, INET6_ADDRSTRLEN))
                {
                    record.data.push_back(std::string(ipv6));
                }
            }
            break;

        case DNSRecordType::CNAME:
        case DNSRecordType::NS:
        case DNSRecordType::PTR:
        {
            size_t rdataOffset = offset;
            record.data.push_back(decodeDomainName(response, rdataOffset));
            break;
        }

        case DNSRecordType::MX:
        {
            uint16_t preference = read16bits(response, offset);
            size_t rdataOffset = offset;
            std::string exchange = decodeDomainName(response, rdataOffset);
            record.mx.preference = preference;
            record.mx.exchange = exchange;
            record.data.push_back(std::to_string(preference) + " " + exchange);
            break;
        }

        case DNSRecordType::TXT:
        {
            size_t rdataOffset = offset;
            uint8_t txtLength = response[rdataOffset++];
            std::string txtData(response.begin() + rdataOffset,
                                response.begin() + rdataOffset + txtLength);
            record.data.push_back(txtData);
            break;
        }
        }

        offset += rdlength;
        records.push_back(record);
    }

    return records;
}

std::vector<uint8_t> DNSQuery::encodeDomainName(const std::string &domain)
{
    std::vector<uint8_t> encoded;
    size_t start = 0;
    size_t dot = domain.find('.');

    while (dot != std::string::npos || start < domain.length())
    {
        size_t len = (dot == std::string::npos) ? domain.length() - start : dot - start;
        if (len > 63)
        {
            throw std::runtime_error("Domain label too long");
        }

        encoded.push_back(static_cast<uint8_t>(len));
        encoded.insert(encoded.end(),
                       domain.begin() + start,
                       domain.begin() + start + len);

        if (dot == std::string::npos)
            break;
        start = dot + 1;
        dot = domain.find('.', start);
    }

    encoded.push_back(0); // Null terminator
    return encoded;
}

uint16_t DNSQuery::generateQueryId()
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<uint16_t> dis(0, UINT16_MAX);
    return dis(gen);
}