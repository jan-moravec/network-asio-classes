#ifndef NETWORKCLIENT_H
#define NETWORKCLIENT_H

#include "networkclientbase.h"
#include <memory>

class NetworkClient
{
public:
    enum Protocol { tcp, udp, icmp };
    NetworkClient(const std::string &host, const std::string &port, Protocol protocol);
    NetworkClient(const NetworkClient&) = delete;
    NetworkClient& operator=(const NetworkClient&) = delete;

    NetworkClientBase &interface() { return *io; }

protected:
    std::unique_ptr<NetworkClientBase> io;
    Protocol protocol;
};

#endif // NETWORKCLIENT_H
