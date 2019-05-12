#ifndef NETWORKSERVER_H
#define NETWORKSERVER_H

#include <memory>
#include "networkserverbase.h"

class NetworkServer
{
public:
    enum Protocol { tcp, udp, icmp };
    NetworkServer(const std::string &port, Protocol protocol);
    NetworkServer(const NetworkServer&) = delete;
    NetworkServer& operator=(const NetworkServer&) = delete;

    NetworkServerBase &interface() { return *server; }
protected:
    std::unique_ptr<NetworkServerBase> server;
    Protocol protocol;
};

#endif // NETWORKSERVER_H
