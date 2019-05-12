#ifndef NETWORKSERVERTCP_H
#define NETWORKSERVERTCP_H

#include <memory>
#include <boost/asio.hpp>
#include "networkserverbase.h"

class NetworkServerTcp: public NetworkServerBase
{
public:
    NetworkServerTcp(const std::string &port);

    void open() override;
    void close() override;

    std::unique_ptr<NetworkSessionBase> accept() override;

protected:
    std::unique_ptr<boost::asio::io_context> io_context;
    std::unique_ptr<boost::asio::ip::tcp::acceptor> acceptor;
};

#endif // NETWORKSERVERTCP_H
