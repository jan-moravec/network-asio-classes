#include "networksessionbase.h"
#include <iostream>

NetworkSessionBase::NetworkSessionBase(unsigned id): id(id)
{
    std::cout << __PRETTY_FUNCTION__ << ": " << id << std::endl;
}

NetworkSessionBase::~NetworkSessionBase()
{
    std::cout << __PRETTY_FUNCTION__ << ": " << id << std::endl;
}

int NetworkSessionBase::write(const std::string &buffer)
{
    return write(reinterpret_cast<const uint8_t *>(buffer.c_str()), buffer.size());
}
