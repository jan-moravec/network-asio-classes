#include "networksessiontcp.h"
#include <iostream>

NetworkSessionTcp::NetworkSessionTcp(boost::asio::ip::tcp::socket socket, unsigned id): NetworkSessionBase(id), socket(std::move(socket))
{
}

int NetworkSessionTcp::write(const uint8_t *buffer, std::size_t size)
{
    boost::system::error_code ec;

    size_t length = boost::asio::write(socket, boost::asio::buffer(buffer, size), ec);
    if (check_error(ec, __PRETTY_FUNCTION__)) {
        return -1;
    }

    return length;
}

int NetworkSessionTcp::wait()
{
    boost::system::error_code ec;

    socket.wait(boost::asio::ip::tcp::socket::wait_read, ec);

    if (check_error(ec, __PRETTY_FUNCTION__)) {
        return -1;
    }

    return 0;
}

int NetworkSessionTcp::available()
{
    boost::system::error_code ec;
    std::size_t available = socket.available(ec);
    if (check_error(ec, __PRETTY_FUNCTION__)) {
        return -1;
    }

    return available;
}

int NetworkSessionTcp::read_some(uint8_t *buffer, std::size_t size)
{
    boost::system::error_code ec;

    std::size_t available = socket.available(ec);
    if (check_error(ec, __PRETTY_FUNCTION__)) {
        return -1;
    }

    if (available > 0) {
        if (available > size) {
            available = size;
        }

        std::size_t length = boost::asio::read(socket, boost::asio::buffer(buffer, available), ec);
        if (check_error(ec, __PRETTY_FUNCTION__)) {
            return -1;
        }

        return length;
    }

    return 0;
}

int NetworkSessionTcp::read_some_wait(uint8_t *buffer, std::size_t size)
{
    boost::system::error_code ec;

    std::size_t length = socket.read_some(boost::asio::buffer(buffer, size), ec);
    if (check_error(ec, __PRETTY_FUNCTION__)) {
        return -1;
    }

    return length;
}

int NetworkSessionTcp::read_exactly(uint8_t *buffer, std::size_t size)
{
    boost::system::error_code ec;
    std::size_t n = boost::asio::read(socket, boost::asio::buffer(buffer, size), ec);

    if (check_error(ec, __PRETTY_FUNCTION__)) {
        return -1;
    }

    return n;
}

int NetworkSessionTcp::read_until(std::string &buffer, const std::string &delim)
{
    boost::system::error_code ec;
    std::size_t n = boost::asio::read_until(socket, boost::asio::dynamic_buffer(buffer), delim, ec);

    if (check_error(ec, __PRETTY_FUNCTION__)) {
        return -1;
    }

    return n;
}

std::string NetworkSessionTcp::get_client_ip()
{
    boost::system::error_code ec;
    std::string address = socket.remote_endpoint().address().to_string(ec);
    if (ec) {
        std::cout << __PRETTY_FUNCTION__ << ": " << ec.message() << std::endl;
        return {};
    }

    return address;
}

bool NetworkSessionTcp::check_error(const boost::system::error_code &ec, const char *function_name)
{
    if (ec) {
        if (ec == boost::asio::error::eof) {
            opened = false;
            return true;
        }

        std::cout << function_name << ": " << ec.message() << std::endl;
        return true;
    }

    return false;
}
