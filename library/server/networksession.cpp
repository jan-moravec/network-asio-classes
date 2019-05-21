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
        if (debug) {
            std::cout << __PRETTY_FUNCTION__ << ": tcp" << std::endl;
        }
        return;
    }

    io_udp = dynamic_cast<NetworkSessionUdp *>(io.get());
    if (io_udp != nullptr) {
        protocol = udp;
        if (debug) {
            std::cout << __PRETTY_FUNCTION__ << ": udp" << std::endl;
        }
        return;
    }

    io_icmp = dynamic_cast<NetworkSessionIcmp *>(io.get());
    if (io_icmp != nullptr) {
        protocol = icmp;
        if (debug) {
            std::cout << __PRETTY_FUNCTION__ << ": icmp" << std::endl;
        }
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
        int length = io->read_some_wait(b, 1);
        std::cout << __PRETTY_FUNCTION__ << ": " << io->get_client_ip() << " - " << io->get_id() << std::endl;

        if (length > 0) {
            std::time_t now = std::time(nullptr);
            std::string time_string(std::ctime(&now));
            io->write(time_string);
        } else if (length < 0) {
            break;
        }
    }
}
