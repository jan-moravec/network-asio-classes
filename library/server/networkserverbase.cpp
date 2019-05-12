#include "networkserverbase.h"
#include "networksession.h"
#include <iostream>

NetworkServerBase::NetworkServerBase(const std::string &port): port(port)
{
}
NetworkServerBase::~NetworkServerBase()
{
}

/*void NetworkServerBase::handle_session(std::unique_ptr<NetworkSessionBase> session_interface)
{
    NetworkSession session(std::move(session_interface));
    session.run();
}*/
