#ifndef NETWORKCLIENT_H
#define NETWORKCLIENT_H

#include "networkclientbase.h"
#include <memory>

class NetworkClient
{
public:
    enum Protocol { tcp, udp, icmp };
    NetworkClient(const std::string &host, const std::string &port, Protocol protocol);

    NetworkClientBase &interface() { return *client; }

protected:
    std::unique_ptr<NetworkClientBase> client;
    Protocol protocol;
};

#endif // NETWORKCLIENT_H
