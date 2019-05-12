#ifndef NETWORKPROTOCOL_H
#define NETWORKPROTOCOL_H

#include <memory>
#include <boost/asio.hpp>

class NetworkProtocol
{
public:
    enum Protocol { tcp, udp, icmp };
    NetworkProtocol(Protocol protocol);

    Protocol get_protocol() { return protocol; }

    boost::asio::ip::tcp::resolver &resolver();
    boost::asio::ip::tcp::socket &socket();

    void set_resolver(std::unique_ptr<boost::asio::ip::tcp::resolver> resolver);
    void set_resolver(boost::asio::ip::udp::resolver resolver);
    void set_resolver(boost::asio::ip::icmp::resolver resolver);

private:
    Protocol protocol;
    std::unique_ptr<boost::asio::ip::tcp::resolver> resolver_tcp;
    std::unique_ptr<boost::asio::ip::tcp::socket> socket_tcp;
};

#endif // NETWORKPROTOCOL_H
