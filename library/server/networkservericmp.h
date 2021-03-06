#ifndef NETWORKSERVERICMP_H
#define NETWORKSERVERICMP_H

#include <memory>
#include <boost/asio.hpp>
#include "networkserverbase.h"

class NetworkServerIcmp: public NetworkServerBase
{
public:
    NetworkServerIcmp(const std::string &port);

    void open() override;
    void close() override;

    std::unique_ptr<NetworkSessionBase> accept() override;

protected:
    std::unique_ptr<boost::asio::io_context> io_context;
    std::shared_ptr<boost::asio::ip::icmp::socket> socket;
};

#endif // NETWORKSERVERICMP_H
