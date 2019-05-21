#include "networkservertcp.h"
#include "networksessiontcp.h"
#include <iostream>
#include <thread>

NetworkServerTcp::NetworkServerTcp(const std::string &port): NetworkServerBase(port)
{
}

void NetworkServerTcp::open()
{
    if (debug) {
        std::cout << __PRETTY_FUNCTION__ << ": " << port << std::endl;
    }
    io_context = std::make_unique<boost::asio::io_context>();
    acceptor = std::make_unique<boost::asio::ip::tcp::acceptor>(*io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), std::stoi(port)));
    if (acceptor->is_open()) {
        opened = true;
    } else {
        std::cout << __PRETTY_FUNCTION__ << ": Error opening server at port " << port << std::endl;
        opened = false;
    }
}

void NetworkServerTcp::close()
{
    if (debug) {
        std::cout << __PRETTY_FUNCTION__ << ": " << port << std::endl;
    }
    boost::system::error_code ec;
    acceptor->close(ec);
    io_context->stop();
    opened = false;
}

std::unique_ptr<NetworkSessionBase> NetworkServerTcp::accept()
{
    if (debug) {
        std::cout << __PRETTY_FUNCTION__ << ": " << port << std::endl;
    }
    boost::system::error_code ec;
    boost::asio::ip::tcp::socket socket = acceptor->accept(ec);
    if (ec) {
        std::cout << __PRETTY_FUNCTION__ << ": " << ec.message() << std::endl;
        return nullptr;
    }

    std::unique_ptr<NetworkSessionBase> session_interface = std::make_unique<NetworkSessionTcp>(std::move(socket), counter++);
    return session_interface;
}

