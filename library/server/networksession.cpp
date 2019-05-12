#include "networksession.h"
#include <iostream>

NetworkSession::NetworkSession(std::unique_ptr<NetworkSessionBase> session_interface): io(std::move(session_interface))
{
    check_protocol();
}

NetworkSession::~NetworkSession()
{
}

void NetworkSession::check_protocol()
{
    io_tcp = dynamic_cast<NetworkSessionTcp *>(io.get());
    if (io_tcp != nullptr) {
        protocol = tcp;
        return;
    }

    io_udp = dynamic_cast<NetworkSessionUdp *>(io.get());
    if (io_udp != nullptr) {
        protocol = udp;
        return;
    }

    io_icmp = dynamic_cast<NetworkSessionIcmp *>(io.get());
    if (io_icmp != nullptr) {
        protocol = icmp;
        return;
    }
}

void NetworkSession::example_echo()
{
    const int max_data = 65536;
    uint8_t data[max_data];

    while (true) {
        int length = io->read_some_wait(data, max_data);

        if (length > 0) {
            io->write(data, length);
        } else if (length < 0) {
            break;
        }
    }
}

void NetworkSession::example_datetime()
{
    while (true) {
        uint8_t b[1];
        int ret = io->read_some(b, 1);

        if (ret > 0) {
            std::time_t now = std::time(nullptr);
            std::string time_string(std::ctime(&now));
            io->write(time_string);
        } else if (ret < 0) {
            break;
        }
    }
}
