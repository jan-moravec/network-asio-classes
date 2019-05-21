#include "networkclientbase.h"
#include <iostream>

NetworkClientBase::NetworkClientBase(const std::string &host, const std::string &port): host(host), port(port)
{
    if (debug) {
        std::cout << __PRETTY_FUNCTION__ << ": " << host << " - " << port << std::endl;
    }
}

NetworkClientBase::~NetworkClientBase()
{
    if (debug) {
        std::cout << __PRETTY_FUNCTION__ << ": " << host << " - " << port << std::endl;
    }
}

int NetworkClientBase::write(const std::string &buffer)
{
    return write(reinterpret_cast<const uint8_t *>(buffer.c_str()), buffer.size());
}
