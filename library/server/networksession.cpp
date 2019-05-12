#include "networksession.h"
#include <iostream>

NetworkSession::NetworkSession(std::unique_ptr<NetworkSessionBase> session): session(std::move(session))
{
}

NetworkSession::~NetworkSession()
{
}

void NetworkSession::run()
{
    //std::cout << __PRETTY_FUNCTION__ << std::endl;
    while (true) {
        uint8_t data[1024];
        int length = session->read_some_wait(data, 1024);

        if (length >= 0) {
            //std::cout << __PRETTY_FUNCTION__ << ": " << length << " " << (char *) data << std::endl;
            session->write(data, length);
        } else {
            break;
        }
    }
}
