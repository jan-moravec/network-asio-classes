#include "networkclientbase.h"

NetworkClientBase::NetworkClientBase(const std::string &host, const std::string &port): host(host), port(port)
{

}

NetworkClientBase::~NetworkClientBase()
{

}

int NetworkClientBase::write(const std::string &buffer)
{
    return write(reinterpret_cast<const uint8_t *>(buffer.c_str()), buffer.size());
}
