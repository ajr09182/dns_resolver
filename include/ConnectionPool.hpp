#pragma once
#include <Poco/Net/SocketAddress.h>
#include <Poco/Net/DatagramSocket.h>
#include "DNSQuery.hpp"
#include <queue>
#include <mutex>
#include <memory>
#include <condition_variable>

class DNSConnection
{
public:
    DNSConnection(const std::string &nameserver, uint16_t port);
    bool isValid() const;
    void query(const std::string &domain, DNSRecordType type);
    std::vector<DNSRecord> getResponse();

private:
    std::unique_ptr<Poco::Net::DatagramSocket> socket;
    Poco::Net::SocketAddress serverAddress;
    bool valid;
    static const int BUFFER_SIZE = 4096;
};

class ConnectionPool {
public:
    ConnectionPool(size_t poolSize, const std::vector<std::string>& nameservers);
    std::shared_ptr<DNSConnection> acquire();
    void release(std::shared_ptr<DNSConnection> conn);

private:
    std::queue<std::shared_ptr<DNSConnection>> connections;
    std::mutex poolMutex;
    std::condition_variable cv;
    size_t maxSize;
};