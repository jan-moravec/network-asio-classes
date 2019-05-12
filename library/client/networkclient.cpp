#include "networkclient.h"
#include "networkclienttcp.h"
#include "networkclientudp.h"
#include "networkclienticmp.h"

#include <iostream>

NetworkClient::NetworkClient(const std::string &host, const std::string &port, Protocol protocol): protocol(protocol)
{
    switch (protocol) {
    case tcp:
        client = std::make_unique<NetworkClientTcp>(host, port);
        break;
    case udp:
        client = std::make_unique<NetworkClientUdp>(host, port);
        break;
    case icmp:
        client = std::make_unique<NetworkClientIcmp>(host, port);
        break;
    }

    //client->connect();
    //if (*client){
    //    std::cout << __PRETTY_FUNCTION__ << ": Connected to " << host << " " << port;
    //} else {
    //    std::cout << __PRETTY_FUNCTION__ << ": Error connecting to " << host << " " << port;
    //}
}
