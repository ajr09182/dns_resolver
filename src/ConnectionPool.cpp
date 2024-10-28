#include "ConnectionPool.hpp"
#include <stdexcept>

DNSConnection::DNSConnection(const std::string &nameserver, uint16_t port)
    : valid(false), serverAddress(nameserver, port)
{
    try
    {
        socket = std::make_unique<Poco::Net::DatagramSocket>();
        socket->connect(serverAddress);
        valid = true;
    }
    catch (const std::exception &e)
    {
        valid = false;
    }
}

bool DNSConnection::isValid() const
{
    return valid;
}

void DNSConnection::query(const std::string &domain, DNSRecordType type)
{
    if (!valid)
        throw std::runtime_error("Invalid connection");

    auto queryData = DNSQuery::buildQuery(domain, type);
    socket->sendTo(queryData.data(), queryData.size(), serverAddress);
}

std::vector<DNSRecord> DNSConnection::getResponse()
{
    if (!valid)
        throw std::runtime_error("Invalid connection");

    std::vector<uint8_t> buffer(BUFFER_SIZE);
    Poco::Net::SocketAddress sender;

    socket->setReceiveTimeout(Poco::Timespan(5, 0)); // 5 second timeout
    int received = socket->receiveFrom(buffer.data(), buffer.size(), sender);

    if (received <= 0)
    {
        throw std::runtime_error("Failed to receive response");
    }

    buffer.resize(received);
    return DNSQuery::parseResponse(buffer);
}

ConnectionPool::ConnectionPool(size_t poolSize, const std::vector<std::string> &nameservers)
    : maxSize(poolSize)
{

    if (nameservers.empty())
    {
        throw std::runtime_error("No nameservers provided");
    }

    for (size_t i = 0; i < poolSize; ++i)
    {
        const std::string &ns = nameservers[i % nameservers.size()];
        auto conn = std::make_shared<DNSConnection>(ns, 53);
        if (conn->isValid())
        {
            connections.push(conn);
        }
    }

    if (connections.empty())
    {
        throw std::runtime_error("Failed to create any valid connections");
    }
}

std::shared_ptr<DNSConnection> ConnectionPool::acquire()
{
    std::unique_lock<std::mutex> lock(poolMutex);
    cv.wait(lock, [this]()
            { return !connections.empty(); });

    auto conn = connections.front();
    connections.pop();
    return conn;
}

void ConnectionPool::release(std::shared_ptr<DNSConnection> conn)
{
    if (conn && conn->isValid())
    {
        std::lock_guard<std::mutex> lock(poolMutex);
        connections.push(conn);
        cv.notify_one();
    }
}