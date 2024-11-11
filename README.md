# DNS Resolver Technical Documentation
## Table of Contents
1. [Overview](#overview)
2. [Architecture](#architecture)
3. [Features](#features)
4. [Implementation Details](#implementation-details)
5. [Usage Guide](#usage-guide)
6. [Configuration](#configuration)
7. [Error Handling](#error-handling)
8. [Future Enhancements](#future-enhancements)

## Overview
The DNS Resolver is a robust C++ implementation of a Domain Name System resolver that supports multiple record types, asynchronous resolution, and advanced features like DNSSEC validation. This document provides comprehensive technical documentation of the system's architecture, features, and usage.

### Key Classes
1. **DNSResolver**: Main class handling DNS resolution
2. **Options**: Command-line argument parser and configuration
3. **Statistics**: Performance metrics tracking

## Features

### Record Type Support
- A Records (IPv4)
- AAAA Records (IPv6)
- MX Records (Mail Exchange)
- TXT Records (Text)
- SOA Records (Start of Authority)

### Advanced Capabilities
1. **Asynchronous Resolution**
   ```cpp
   auto futureRecords = resolver.resolveAsync(domain);
   auto records = futureRecords.get();
   ```

2. **Multi-Server Support**
   ```cpp
   config.nameservers = {
       "8.8.8.8", "8.8.4.4",        // Google DNS
       "1.1.1.1", "1.0.0.1",        // Cloudflare DNS
       "9.9.9.9",                    // Quad9 DNS
       "208.67.222.222"             // OpenDNS
   };
   ```

3. **DNSSEC Validation**
   - Automatic signature verification
   - Chain of trust validation
   - RRSIG record processing

## Implementation Details

### Record Type Handling
```cpp
std::optional<DNSRecordType> stringToRecordType(const std::string& type) {
    static const std::map<std::string, DNSRecordType> typeMap = {
        {"A", DNSRecordType::A},
        {"AAAA", DNSRecordType::AAAA},
        {"MX", DNSRecordType::MX},
        {"TXT", DNSRecordType::TXT},
        {"SOA", DNSRecordType::SOA}
    };

    auto it = typeMap.find(type);
    return it != typeMap.end() ? std::optional{it->second} : std::nullopt;
}
```

### Output Formatting
```cpp
namespace Color {
    const std::string Reset   = "\033[0m";
    const std::string Bold    = "\033[1m";
    const std::string Blue    = "\033[34m";
    const std::string Green   = "\033[32m";
    const std::string Yellow  = "\033[33m";
    const std::string Red     = "\033[31m";
}
```

### Record Output Format
```
Record:
  Type: [Record Type]
  Name: [Domain Name]
  TTL: [Time To Live]
  Data: [Record Data]
  [Additional Type-Specific Fields]
----------------------------------------
```

## Usage Guide

### Command Line Interface
```bash
cd build
./dns-resolver
```

### Build Commands
```bash
cd build
cmake ..
make
```

## Configuration

### Default Configuration
```cpp
DNSResolver::Config config;
config.enableParallelQueries = true;
config.enableDNSSEC = true;
config.connectionPoolSize = 10;
```

### Performance Settings
- Connection pool size: 10 concurrent connections
- Parallel query support enabled
- DNSSEC validation enabled by default

## Error Handling

### Error Categories
1. **Network Errors**
   - Connection failures
   - Timeout issues
   - DNS server unreachable

2. **Resolution Errors**
   - Invalid domain names
   - Unsupported record types
   - DNSSEC validation failures

3. **System Errors**
   - Memory allocation failures
   - Configuration errors
   - Internal state errors

### Error Output Format
```cpp
try {
    // DNS operations
} catch (const std::exception& e) {
    std::cerr << Color::Red << "Fatal error: " << e.what() << Color::Reset << "\n";
    return 1;
}
```

## Future Enhancements

### Planned Features
1. **Extended Protocol Support**
   - DNS over HTTPS (DoH)
   - DNS over TLS (DoT)
   - DANE validation

2. **Performance Improvements**
   - Enhanced caching mechanisms
   - Query optimization
   - Improved connection pooling

3. **Additional Features**
   - Configuration file support
   - Extended statistics reporting
   - GUI interface
   - Additional record type support

### Development Roadmap
1. Q2 2024: DoH/DoT implementation
2. Q3 2024: Enhanced caching system
3. Q4 2024: GUI development
4. Q1 2025: Additional record types

## Appendix A: Statistics Format
```
Resolver Statistics:
  Total queries:  [count]
  Cache hits:     [count]
  Cache misses:   [count]
  Failed queries: [count]
```

## Appendix B: Color Coding Reference
| Color  | Usage                     |
|--------|---------------------------|
| Blue   | Record types and names    |
| Green  | Successful data           |
| Yellow | Warnings                  |
| Red    | Errors                    |
| Bold   | Headers and labels        |
