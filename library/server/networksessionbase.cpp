#include "networksessionbase.h"

NetworkSessionBase::NetworkSessionBase(unsigned id): id(id)
{
}

NetworkSessionBase::~NetworkSessionBase()
{
}

int NetworkSessionBase::write(const std::string &buffer)
{
    return write(reinterpret_cast<const uint8_t *>(buffer.c_str()), buffer.size());
}
