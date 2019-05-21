#ifndef NETWORKSERVERBASE_H
#define NETWORKSERVERBASE_H

#include <string>
#include <vector>
#include <memory>
#include "networksessionbase.h"

class NetworkServerBase
{
public:
    NetworkServerBase(const std::string &port);
    NetworkServerBase(const NetworkServerBase&) = delete;
    NetworkServerBase& operator=(const NetworkServerBase&) = delete;
    virtual ~NetworkServerBase();

    virtual void open() = 0;
    virtual void close() = 0;

    virtual std::unique_ptr<NetworkSessionBase> accept() = 0;

    operator bool() const { return opened; }
    bool is_opened() const { return opened; }

    void set_debug(bool debug) { this->debug = debug;  }
    bool get_debug() const { return debug;  }

protected:
    bool opened = false;
    std::string port;
    unsigned counter = 0;
    bool debug = false;
};

#endif // NETWORKSERVERBASE_H
