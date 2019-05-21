#include "networkclient.h"
#include "networkclienttcp.h"
#include "networkclientudp.h"
#include "networkclienticmp.h"

NetworkClient::NetworkClient(const std::string &host, const std::string &port, Protocol protocol): protocol(protocol)
{
    switch (protocol) {
    case tcp:
        io = std::make_unique<NetworkClientTcp>(host, port);
        break;
    case udp:
        io = std::make_unique<NetworkClientUdp>(host, port);
        break;
    case icmp:
        io = std::make_unique<NetworkClientIcmp>(host, port);
        break;
    }
}
