#include "networkservericmp.h"
#include "networksessionicmp.h"
#include <iostream>
#include <thread>

NetworkServerIcmp::NetworkServerIcmp(const std::string &port): NetworkServerBase(port)
{
}

void NetworkServerIcmp::open()
{
    if (debug) {
        std::cout << __PRETTY_FUNCTION__ << ": " << port << std::endl;
    }

    io_context = std::make_unique<boost::asio::io_context>();
    socket = std::make_shared<boost::asio::ip::icmp::socket>(*io_context, boost::asio::ip::icmp::endpoint(boost::asio::ip::icmp::v4(), std::stoi(port)));
    if (socket->is_open()) {
        opened = true;
    } else {
        opened = false;
    }
}

void NetworkServerIcmp::close()
{
    if (debug) {
        std::cout << __PRETTY_FUNCTION__ << ": " << port << std::endl;
    }

    boost::system::error_code ec;
    socket->close(ec);
    io_context->stop();
    opened = false;
}

std::unique_ptr<NetworkSessionBase> NetworkServerIcmp::accept()
{
    if (debug) {
        std::cout << __PRETTY_FUNCTION__ << ": " << port << std::endl;
    }

    std::unique_ptr<NetworkSessionBase> session_interface = std::make_unique<NetworkSessionIcmp>(socket, counter++);
    return session_interface;
}

