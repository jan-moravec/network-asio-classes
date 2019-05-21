#ifndef NETWORKSESSIONICMP_H
#define NETWORKSESSIONICMP_H

#include <cstdint>
#include <string>
#include <boost/asio.hpp>
#include "networksessionbase.h"

class NetworkSessionIcmp: public NetworkSessionBase
{
public:
    NetworkSessionIcmp(std::shared_ptr<boost::asio::ip::icmp::socket> socket, unsigned id);

    int write(const uint8_t *buffer, std::size_t size) override;
    using NetworkSessionBase::write;

    int wait() override;
    int available() override;
    int read_some(uint8_t *buffer, std::size_t size) override;
    int read_some_wait(uint8_t *buffer, std::size_t size) override;
    int read_exactly(uint8_t *buffer, std::size_t size) override;
    int read_until(std::string &buffer, const std::string &delim) override;
    std::string get_client_ip() override;

protected:
    std::shared_ptr<boost::asio::ip::icmp::socket> socket;
    boost::asio::ip::icmp::endpoint sender_endpoint;
    bool check_error(const boost::system::error_code &ec, const char *function_name);
};

#endif // NETWORKSESSIONICMP_H
