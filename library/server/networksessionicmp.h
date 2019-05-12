#ifndef NETWORKSESSIONICMP_H
#define NETWORKSESSIONICMP_H

#include <cstdint>
#include <string>
#include <boost/asio.hpp>
#include "networksessionbase.h"

class NetworkSessionIcmp: public NetworkSessionBase
{
public:
    NetworkSessionIcmp(boost::asio::ip::icmp::socket socket, unsigned id);

    void run() override;

    int write(const uint8_t *buffer, std::size_t size) override;
    using NetworkSessionBase::write;

    int wait() override;
    int available() override;
    int read_some(uint8_t *buffer, std::size_t size) override;
    int read_some_wait(uint8_t *buffer, std::size_t size) override;
    int read_exactly(uint8_t *buffer, std::size_t size) override;
    int read_until(std::string &buffer, const std::string &delim) override;

protected:
    boost::asio::ip::icmp::socket socket;
    bool check_error(const boost::system::error_code &ec, const char *function_name);
};

#endif // NETWORKSESSIONICMP_H
