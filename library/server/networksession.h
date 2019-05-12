#ifndef NETWORKSESSION_H
#define NETWORKSESSION_H

#include <memory>
#include "networksessionbase.h"
#include "networksessiontcp.h"
#include "networksessionudp.h"
#include "networksessionicmp.h"

class NetworkSession
{
public:
    NetworkSession(std::unique_ptr<NetworkSessionBase> session_interface);
    NetworkSession(const NetworkSession&) = delete;
    NetworkSession& operator=(const NetworkSession&) = delete;
    virtual ~NetworkSession();
    enum Protocol { unspecified, tcp, udp, icmp };

    virtual void run() = 0;

protected:
    Protocol protocol = unspecified;
    std::unique_ptr<NetworkSessionBase> io;

    NetworkSessionTcp *io_tcp = nullptr;
    NetworkSessionUdp *io_udp = nullptr;
    NetworkSessionIcmp *io_icmp = nullptr;

    void example_echo();
    void example_datetime();

private:
    void check_protocol();
};

#endif // NETWORKSESSION_H
