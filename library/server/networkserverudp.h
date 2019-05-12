#ifndef NETWORKSERVERUDP_H
#define NETWORKSERVERUDP_H

#include <memory>
#include <boost/asio.hpp>
#include "networkserverbase.h"

class NetworkServerUdp: public NetworkServerBase
{
public:
    NetworkServerUdp(const std::string &port);

    void open() override;
    void close() override;

    std::unique_ptr<NetworkSessionBase> accept() override;

protected:
    std::unique_ptr<boost::asio::io_context> io_context;
    std::shared_ptr<boost::asio::ip::udp::socket> socket;
};

#endif // NETWORKSERVERUDP_H
