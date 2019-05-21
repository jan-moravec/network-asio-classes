#ifndef NETWORKSESSIONBASE_H
#define NETWORKSESSIONBASE_H

#include <cstdint>
#include <string>

class NetworkSessionBase
{
public:
    NetworkSessionBase(unsigned id);
    NetworkSessionBase(const NetworkSessionBase&) = delete;
    NetworkSessionBase& operator=(const NetworkSessionBase&) = delete;
    virtual ~NetworkSessionBase();

    virtual int write(const uint8_t *buffer, std::size_t size) = 0; /// Send size
    int write(const std::string &buffer);

    virtual int wait() = 0; /// Wait until some data arrived, 0 = data ready, -1 = error
    virtual int available() = 0;
    virtual int read_some(uint8_t *buffer, std::size_t size) = 0; /// Recieve 0 up to size
    virtual int read_some_wait(uint8_t *buffer, std::size_t size) = 0; /// Wait for data and recieve 1 up to size
    virtual int read_exactly(uint8_t *buffer, std::size_t size) = 0; /// Wait until size recieved, or less if timeout expired
    virtual int read_until(std::string &buffer, const std::string &delim) = 0; /// Wait until buffer ending with delim recieved

    virtual std::string get_client_ip() = 0;

    unsigned get_id() const { return id; }
    void set_debug(bool debug) { this->debug = debug;  }
    bool get_debug() const { return debug;  }

protected:
    bool opened = true;
    unsigned id;
    bool debug = false;
};

#endif // NETWORKSESSIONBASE_H
