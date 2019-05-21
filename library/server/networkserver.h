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

    void open();
    void close();
    std::unique_ptr<NetworkSessionBase> accept();

    operator bool() const { return server->is_opened(); }
    bool is_opened() const { return server->is_opened(); }

    void set_debug(bool debug) { this->debug = debug;  }
    bool get_debug() const { return debug;  }

protected:
    std::unique_ptr<NetworkServerBase> server;
    Protocol protocol;
    bool debug = false;
};

#endif // NETWORKSERVER_H
