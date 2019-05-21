#include "networkserverbase.h"
#include "networksession.h"
#include <iostream>

NetworkServerBase::NetworkServerBase(const std::string &port): port(port)
{
    if (debug) {
        std::cout << __PRETTY_FUNCTION__ << ": " << port << std::endl;
    }
}

NetworkServerBase::~NetworkServerBase()
{
    if (debug) {
        std::cout << __PRETTY_FUNCTION__ << ": " << port << std::endl;
    }
}
