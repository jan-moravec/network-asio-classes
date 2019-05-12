#include "networkservertcp.h"
#include "networksessiontcp.h"
#include <iostream>
#include <thread>

NetworkServerTcp::NetworkServerTcp(const std::string &port): NetworkServerBase(port)
{
}

void NetworkServerTcp::open()
{
    io_context = std::make_unique<boost::asio::io_context>();
    acceptor = std::make_unique<boost::asio::ip::tcp::acceptor>(*io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), std::stoi(port)));
    if (acceptor->is_open()) {
        opened = true;
    } else {
        opened = false;
    }
}

void NetworkServerTcp::close()
{
    boost::system::error_code ec;
    acceptor->close(ec);
    io_context->stop();
    opened = false;
}

int NetworkServerTcp::accept()
{
    boost::system::error_code ec;
    boost::asio::ip::tcp::socket socket = acceptor->accept(ec);
    if (ec) {
        std::cout << __PRETTY_FUNCTION__ << ": " << ec.message() << std::endl;
        return -1;
    }

    std::unique_ptr<NetworkSessionBase> session_interface = std::make_unique<NetworkSessionTcp>(std::move(socket), counter++);
    std::thread(&NetworkServerTcp::handle_session, this, std::move(session_interface)).detach();
    return 0;
}
