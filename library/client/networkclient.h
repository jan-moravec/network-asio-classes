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

    void set_debug(bool debug) { this->debug = debug;  }
    bool get_debug() const { return debug;  }

protected:
    std::unique_ptr<NetworkClientBase> io;
    Protocol protocol;
    bool debug = false;
};

#endif // NETWORKCLIENT_H
