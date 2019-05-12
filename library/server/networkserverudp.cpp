#include "networkserverudp.h"
#include "networksessionudp.h"
#include <iostream>
#include <thread>

NetworkServerUdp::NetworkServerUdp(const std::string &port): NetworkServerBase(port)
{
}

void NetworkServerUdp::open()
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    io_context = std::make_unique<boost::asio::io_context>();
    socket = std::make_shared<boost::asio::ip::udp::socket>(*io_context, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), std::stoi(port)));
    if (socket->is_open()) {
        opened = true;
    } else {
        opened = false;
    }
}

void NetworkServerUdp::close()
{
    boost::system::error_code ec;
    socket->close(ec);
    io_context->stop();
    opened = false;
}

int NetworkServerUdp::accept()
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    std::unique_ptr<NetworkSessionBase> session_interface = std::make_unique<NetworkSessionUdp>(socket, counter++);
    handle_session(std::move(session_interface));
    return 0;
}

