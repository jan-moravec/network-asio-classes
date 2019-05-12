#include "networkclientudp.h"
#include <iostream>

NetworkClientUdp::NetworkClientUdp(const std::string &host, const std::string &port): NetworkClientBase (host, port)
{
}

void NetworkClientUdp::connect()
{
    io_context = std::make_shared<boost::asio::io_context>();
    resolver = std::make_unique<boost::asio::ip::udp::resolver>(*io_context);
    socket = std::make_unique<boost::asio::ip::udp::socket>(*io_context);

    boost::system::error_code ec;
    boost::asio::connect(*socket, resolver->resolve(host, port), ec);

    if (ec) {
        connected = false;
        std::cout << __PRETTY_FUNCTION__ << ": " << ec.message() << std::endl;
    } else {
        connected = true;
    }
}

void NetworkClientUdp::disconnect()
{
    boost::system::error_code ec;
    socket->shutdown(boost::asio::ip::udp::socket::shutdown_both, ec);
    socket->close(ec);
    io_context->stop();
    connected = false;
}

int NetworkClientUdp::write(const uint8_t *buffer, std::size_t size)
{
    boost::system::error_code ec;

    size_t length = socket->send(boost::asio::buffer(buffer, size), 0, ec);
    if (ec) {
        std::cout << __PRETTY_FUNCTION__ << ": " << ec.message() << std::endl;
        return -1;
    }

    return length;
}

int NetworkClientUdp::wait(std::chrono::steady_clock::duration timeout)
{
    boost::system::error_code ec;

    socket->async_wait(boost::asio::ip::udp::socket::wait_read,
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

int NetworkClientUdp::available()
{
    boost::system::error_code ec;
    std::size_t available = socket->available(ec);
    if (ec) {
        std::cout << __PRETTY_FUNCTION__ << ": " << ec.message() << std::endl;
        return -1;
    }

    return available;
}

int NetworkClientUdp::read_some(uint8_t *buffer, std::size_t size)
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

        std::size_t length = socket->receive(boost::asio::buffer(buffer, available), 0, ec);
        if (ec) {
            std::cout << __PRETTY_FUNCTION__ << ": " << ec.message() << std::endl;
            return -1;
        }

        return length;
    }

    return 0;
}

int NetworkClientUdp::read_some_wait(uint8_t *buffer, std::size_t size)
{
    boost::system::error_code ec;

    std::size_t length = socket->receive(boost::asio::buffer(buffer, size), 0, ec); // boost::asio::socket_base::wait_read
    if (ec) {
        std::cout << __PRETTY_FUNCTION__ << ": " << ec.message() << std::endl;
        return -1;
    }

    return length;
}

int NetworkClientUdp::read_exactly(uint8_t *buffer, std::size_t size, std::chrono::steady_clock::duration timeout)
{
    boost::system::error_code ec;
    std::chrono::steady_clock::time_point stop = std::chrono::steady_clock::now() + timeout;
    bool timedout = false;
    std::size_t n = 0;

    do {
        socket->async_receive(boost::asio::buffer(&buffer[n], size-n),
                              [&](const boost::system::error_code& result_error, std::size_t result_n)
                              {
                                  ec = result_error;
                                  n += result_n;
                              });

        timedout = run_until(stop);

        if (!timedout && ec) {
            std::cout << __PRETTY_FUNCTION__ << ": " << ec.message() << std::endl;
            return -1;
        }
    } while (!timedout && size != n);

    return n;
}

int NetworkClientUdp::read_until(std::string &buffer, const std::string &delim, std::chrono::steady_clock::duration timeout)
{
    boost::system::error_code ec;
    std::chrono::steady_clock::time_point stop = std::chrono::steady_clock::now() + timeout;
    bool timedout = false;
    std::size_t n = 0;
    std::size_t n_last = 0;
    std::size_t found;

    const std::size_t max_size = 65536;
    buffer.resize(65536);

    do {
        socket->async_receive(boost::asio::buffer(&buffer[n], max_size-n),
                              [&](const boost::system::error_code& result_error, std::size_t result_n)
                              {
                                  ec = result_error;
                                  n += result_n;
                              });

        timedout = run_until(stop);
        found = buffer.find(delim, n_last);
        n_last = n;

        if (!timedout && ec) {
            std::cout << __PRETTY_FUNCTION__ << ": " << ec.message() << std::endl;
            return -1;
        }
    } while (!timedout && found == std::string::npos);

    buffer.resize(n);
    return n;
}

bool NetworkClientUdp::run_for(std::chrono::steady_clock::duration timeout)
{
    io_context->restart();
    io_context->run_for(timeout);

    if (!io_context->stopped()) {
        socket->cancel();
        io_context->run();
        return true;
    }

    return false;
}

bool NetworkClientUdp::run_until(const std::chrono::steady_clock::time_point &timepoint)
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
