#include "networkclienttcp.h"
#include <iostream>

NetworkClientTcp::NetworkClientTcp(const std::string &host, const std::string &port): NetworkClientBase (host, port)
{
}

void NetworkClientTcp::connect()
{
    if (debug) {
        std::cout << __PRETTY_FUNCTION__ << ": " << host << " - " << port << std::endl;
    }

    io_context = std::make_shared<boost::asio::io_context>();
    resolver = std::make_unique<boost::asio::ip::tcp::resolver>(*io_context);
    socket = std::make_unique<boost::asio::ip::tcp::socket>(*io_context);

    boost::system::error_code ec;
    boost::asio::connect(*socket, resolver->resolve(host, port), ec);

    if (ec) {
        connected = false;
        std::cout << __PRETTY_FUNCTION__ << ": " << host << " - " << port << " - " << ec.message() << std::endl;
    } else {
        connected = true;
    }
}

void NetworkClientTcp::disconnect()
{
    if (debug) {
        std::cout << __PRETTY_FUNCTION__ << ": " << host << " - " << port << std::endl;
    }

    boost::system::error_code ec;
    socket->shutdown(boost::asio::ip::tcp::socket::shutdown_both, ec);
    socket->close(ec);
    io_context->stop();
    connected = false;
}

int NetworkClientTcp::write(const uint8_t *buffer, std::size_t size)
{
    boost::system::error_code ec;

    size_t length = boost::asio::write(*socket, boost::asio::buffer(buffer, size), ec);
    if (ec) {
        std::cout << __PRETTY_FUNCTION__ << ": " << ec.message() << std::endl;
        return -1;
    }

    return length;
}

int NetworkClientTcp::wait(std::chrono::steady_clock::duration timeout)
{
    boost::system::error_code ec;

    socket->async_wait(boost::asio::ip::tcp::socket::wait_read,
                      [&](const boost::system::error_code& result_error)
                      {
                          ec = result_error;
                      });

    bool timedout = run_for(timeout);

    if (ec) {
        std::cout << __PRETTY_FUNCTION__ << ": " << ec.message() << std::endl;
        return -1;
    }

    if (timedout) {
        return 1;
    }

    return 0;
}

int NetworkClientTcp::available()
{
    boost::system::error_code ec;
    std::size_t available = socket->available(ec);
    if (ec) {
        std::cout << __PRETTY_FUNCTION__ << ": " << ec.message() << std::endl;
        return -1;
    }

    return available;
}

int NetworkClientTcp::read_some(uint8_t *buffer, std::size_t size)
{
    boost::system::error_code ec;

    std::size_t available = socket->available(ec);
    if (ec) {
        std::cout << __PRETTY_FUNCTION__ << ": " << ec.message() << std::endl;
        return -1;
    }

    if (available > 0) {
        if (available > size) {
            available = size;
        }

        std::size_t length = boost::asio::read(*socket, boost::asio::buffer(buffer, available), ec);
        if (ec) {
            std::cout << __PRETTY_FUNCTION__ << ": " << ec.message() << std::endl;
            return -1;
        }

        return length;
    }

    return 0;
}

int NetworkClientTcp::read_some_wait(uint8_t *buffer, std::size_t size)
{
    boost::system::error_code ec;

    std::size_t length = socket->read_some(boost::asio::buffer(buffer, size), ec);
    if (ec) {
        std::cout << __PRETTY_FUNCTION__ << ": " << ec.message() << std::endl;
        return -1;
    }

    return length;
}

int NetworkClientTcp::read_exactly(uint8_t *buffer, std::size_t size, std::chrono::steady_clock::duration timeout)
{
    boost::system::error_code ec;
    std::size_t n = 0;
    boost::asio::async_read(*socket, boost::asio::buffer(buffer, size),
                            [&](const boost::system::error_code& result_error, std::size_t result_n)
                            {
                                ec = result_error;
                                n = result_n;
                            });

    bool timedout = run_for(timeout);

    if (!timedout && ec) {
        std::cout << __PRETTY_FUNCTION__ << ": " << ec.message() << std::endl;
        return -1;
    }

    return n;
}

int NetworkClientTcp::read_until(std::string &buffer, const std::string &delim, std::chrono::steady_clock::duration timeout)
{
    boost::system::error_code ec;
    std::size_t n = 0;
    boost::asio::async_read_until(*socket, boost::asio::dynamic_buffer(buffer), delim,
                                  [&](const boost::system::error_code& result_error, std::size_t result_n)
                                  {
                                      ec = result_error;
                                      n = result_n;
                                  });

    bool timedout = run_for(timeout);

    if (!timedout && ec) {
        std::cout << __PRETTY_FUNCTION__ << ": " << ec.message() << std::endl;
        return -1;
    }

    return n;
}

bool NetworkClientTcp::run_for(std::chrono::steady_clock::duration timeout)
{
    io_context->restart();
    io_context->run_for(timeout);

    if (!io_context->stopped()) {
        socket->cancel(); // close()
        io_context->run();
        return true;
    }

    return false;
}

bool NetworkClientTcp::run_until(const std::chrono::steady_clock::time_point &timepoint)
{
    io_context->restart();
    io_context->run_until(timepoint);

    if (!io_context->stopped()) {
        socket->cancel();
        io_context->run();
        return true;
    }

    return false;
}
