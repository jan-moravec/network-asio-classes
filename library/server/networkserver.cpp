#include "networkserver.h"
#include "networkservertcp.h"
#include "networkserverudp.h"
#include "networkservericmp.h"

#include "networksessionbase.h"
#include <iostream>

NetworkServer::NetworkServer(const std::string &port, Protocol protocol): protocol(protocol)
{
    switch (protocol) {
    case tcp:
        server = std::make_unique<NetworkServerTcp>(port);
        break;
    case udp:
        server = std::make_unique<NetworkServerUdp>(port);
        break;
    case icmp:
        server = std::make_unique<NetworkServerIcmp>(port);
        break;
    }
}

void NetworkServer::open()
{
    server->open();
}

void NetworkServer::close()
{
    server->close();
}

std::unique_ptr<NetworkSessionBase> NetworkServer::accept()
{
    return server->accept();
}
