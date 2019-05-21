#include "networkserverudp.h"
#include "networksessionudp.h"
#include <iostream>
#include <thread>

NetworkServerUdp::NetworkServerUdp(const std::string &port): NetworkServerBase(port)
{
}

void NetworkServerUdp::open()
{
    if (debug) {
        std::cout << __PRETTY_FUNCTION__ << ": " << port << std::endl;
    }
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
    if (debug) {
        std::cout << __PRETTY_FUNCTION__ << ": " << port << std::endl;
    }
    boost::system::error_code ec;
    socket->close(ec);
    io_context->stop();
    opened = false;
}

std::unique_ptr<NetworkSessionBase> NetworkServerUdp::accept()
{
    if (debug) {
        std::cout << __PRETTY_FUNCTION__ << ": " << port << std::endl;
    }
    std::unique_ptr<NetworkSessionBase> session_interface = std::make_unique<NetworkSessionUdp>(socket, counter++);
    return session_interface;
}

