#include "networkserver.h"
#include "networkservertcp.h"
#include "networkserverudp.h"

#include "networksessionbase.h"
#include <iostream>

void run(NetworkSessionBase &session)
{
    while (true) {
        uint8_t data[1024];
        int length = session.read_some_wait(data, 1024);

        if (length >= 0) {
            session.write(data, length);
        } else {
            break;
        }
    }
}

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
        //client = std::make_unique<NetworkClientIcmp>(host, port);
        break;
    }

    //server->open();
    //if (*server) {
    //    server->accept();
    //}
}
