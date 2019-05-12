#ifndef NETWORKSESSIONTCP_H
#define NETWORKSESSIONTCP_H

#include <cstdint>
#include <string>
#include <boost/asio.hpp>
#include "networksessionbase.h"

class NetworkSessionTcp: public NetworkSessionBase
{
public:
    NetworkSessionTcp(boost::asio::ip::tcp::socket socket, unsigned id);

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
    boost::asio::ip::tcp::socket socket;
    bool check_error(const boost::system::error_code &ec, const char *function_name);
};

#endif // NETWORKSESSIONTCP_H
