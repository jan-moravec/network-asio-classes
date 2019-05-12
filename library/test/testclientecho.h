#ifndef TESTCLIENTECHO_H
#define TESTCLIENTECHO_H

#include "library/client/networkclient.h"

class TestClientEcho: public NetworkClient
{
public:
    TestClientEcho(const std::string &host, const std::string &port, Protocol protocol);

    void run();
};

#endif // TESTCLIENTECHO_H
