#ifndef NETWORKSESSION_H
#define NETWORKSESSION_H

#include <memory>
#include "networksessionbase.h"

class NetworkSession
{
public:
    NetworkSession(std::unique_ptr<NetworkSessionBase> session);
    NetworkSession(const NetworkSession&) = delete;
    NetworkSession& operator=(const NetworkSession&) = delete;
    virtual ~NetworkSession();

    virtual void run();

protected:
    std::unique_ptr<NetworkSessionBase> session;
};

#endif // NETWORKSESSION_H
