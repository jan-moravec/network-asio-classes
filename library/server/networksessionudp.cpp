#include "networksessionudp.h"
#include <iostream>

NetworkSessionUdp::NetworkSessionUdp(std::shared_ptr<boost::asio::ip::udp::socket> socket, unsigned id): NetworkSessionBase(id), socket(socket)
{
}

void NetworkSessionUdp::run()
{
    std::cout << __PRETTY_FUNCTION__ << ": " << id << " - " << socket->remote_endpoint().address().to_string() << " - " << socket->remote_endpoint().port() << std::endl;
    while (true) {
        uint8_t data[1024];
        int length = read_some_wait(data, 1024);

        if (length >= 0) {
            write(data, length);
        } else {
            break;
        }
    }
}

int NetworkSessionUdp::write(const uint8_t *buffer, std::size_t size)
{
    boost::system::error_code ec;

    size_t length = socket->send_to(boost::asio::buffer(buffer, size), sender_endpoint, 0, ec);
    if (check_error(ec, __PRETTY_FUNCTION__)) {
        return -1;
    }

    return length;
}

int NetworkSessionUdp::wait()
{
    boost::system::error_code ec;

    socket->wait(boost::asio::ip::udp::socket::wait_read, ec);

    if (check_error(ec, __PRETTY_FUNCTION__)) {
        return -1;
    }

    return 0;
}

int NetworkSessionUdp::available()
{
    boost::system::error_code ec;
    std::size_t available = socket->available(ec);
    if (check_error(ec, __PRETTY_FUNCTION__)) {
        return -1;
    }

    return available;
}

int NetworkSessionUdp::read_some(uint8_t *buffer, std::size_t size)
{
    boost::system::error_code ec;

    std::size_t available = socket->available(ec);
    if (check_error(ec, __PRETTY_FUNCTION__)) {
        return -1;
    }

    if (available > 0) {
        if (available > size) {
            available = size;
        }

        std::size_t length = socket->receive(boost::asio::buffer(buffer, available), 0, ec);
        if (check_error(ec, __PRETTY_FUNCTION__)) {
            return -1;
        }

        return length;
    }

    return 0;
}

int NetworkSessionUdp::read_some_wait(uint8_t *buffer, std::size_t size)
{
    boost::system::error_code ec;

    std::size_t length = socket->receive_from(boost::asio::buffer(buffer, size), sender_endpoint, 0, ec);
    if (check_error(ec, __PRETTY_FUNCTION__)) {
        return -1;
    }

    return length;
}

int NetworkSessionUdp::read_exactly(uint8_t *buffer, std::size_t size)
{
    boost::system::error_code ec;
    std::size_t n = 0;

    do {
        n += socket->receive(boost::asio::buffer(&buffer[n], size-n), 0, ec);

        if (check_error(ec, __PRETTY_FUNCTION__)) {
            return -1;
        }

    } while (size != n);

    return n;
}

int NetworkSessionUdp::read_until(std::string &buffer, const std::string &delim)
{
    boost::system::error_code ec;
    std::size_t n = 0;
    std::size_t n_last = 0;
    std::size_t found;

    const std::size_t max_size = 65536;
    buffer.resize(65536);

    do {
        socket->receive(boost::asio::buffer(&buffer[n], max_size-n), 0, ec);

        found = buffer.find(delim, n_last);
        n_last = n;

        if (check_error(ec, __PRETTY_FUNCTION__)) {
            return -1;
        }
    } while (found == std::string::npos);

    buffer.resize(n);
    return n;
}

bool NetworkSessionUdp::check_error(const boost::system::error_code &ec, const char *function_name)
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
