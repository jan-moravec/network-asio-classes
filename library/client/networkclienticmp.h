#ifndef NETWORKCLIENTICMP_H
#define NETWORKCLIENTICMP_H

#include <memory>
#include <boost/asio.hpp>
#include "networkclientbase.h"

class NetworkClientIcmp: public NetworkClientBase
{
public:
    NetworkClientIcmp(const std::string &host, const std::string &port);

    void connect() override;
    void disconnect() override;

    int write(const uint8_t *buffer, std::size_t size) override;
    using NetworkClientBase::write;

    int wait(std::chrono::steady_clock::duration timeout) override;
    int available() override;
    int read_some(uint8_t *buffer, std::size_t size) override;
    int read_some_wait(uint8_t *buffer, std::size_t size) override;
    int read_exactly(uint8_t *buffer, std::size_t size, std::chrono::steady_clock::duration timeout) override;
    int read_until(std::string &buffer, const std::string &delim, std::chrono::steady_clock::duration timeout) override;

protected:
    std::shared_ptr<boost::asio::io_context> io_context;
    std::unique_ptr<boost::asio::ip::icmp::resolver> resolver;
    std::unique_ptr<boost::asio::ip::icmp::socket> socket;
    bool run_for(std::chrono::steady_clock::duration timeout); /// Run operation with timeout
    bool run_until(const std::chrono::steady_clock::time_point &timepoint); /// Run operation until timepoint
};
#endif // NETWORKCLIENTICMP_H
