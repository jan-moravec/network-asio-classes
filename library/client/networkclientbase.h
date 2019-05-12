#ifndef NETWORKCLIENTBASE_H
#define NETWORKCLIENTBASE_H

#include <cstdint>
#include <string>
#include <chrono>

class NetworkClientBase
{
public:
    NetworkClientBase(const std::string &host, const std::string &port);
    virtual ~NetworkClientBase();

    virtual void connect() = 0;
    virtual void disconnect() = 0;

    virtual int write(const uint8_t *buffer, std::size_t size) = 0; /// Send size
    int write(const std::string &buffer);

    virtual int wait(std::chrono::steady_clock::duration timeout) = 0; /// Wait until some data arrived, 0 = data ready, 1 = timed out, -1 = error
    virtual int available() = 0;
    virtual int read_some(uint8_t *buffer, std::size_t size) = 0; /// Recieve 0 up to size
    virtual int read_some_wait(uint8_t *buffer, std::size_t size) = 0; /// Wait for data and recieve 1 up to size
    virtual int read_exactly(uint8_t *buffer, std::size_t size, std::chrono::steady_clock::duration timeout) = 0; /// Wait until size recieved, or less if timeout expired
    virtual int read_until(std::string &buffer, const std::string &delim, std::chrono::steady_clock::duration timeout) = 0; /// Wait until buffer ending with delim recieved

    operator bool() const { return connected; }
    bool is_connected() const { return connected; }

protected:
    bool connected = false;
    std::string host;
    std::string port;
};

#endif // NETWORKCLIENTBASE_H
