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
    virtual ~NetworkServerBase();

    virtual void open() = 0;
    virtual void close() = 0;

    virtual int accept() = 0;

    operator bool() const { return opened; }
    bool is_opened() const { return opened; }

protected:
    bool opened = false;
    std::string port;
    unsigned counter = 0;

    void handle_session(std::unique_ptr<NetworkSessionBase> session_interface);
};

#endif // NETWORKSERVERBASE_H
