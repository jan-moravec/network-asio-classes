#ifndef TESTCLIENTDATETIME_H
#define TESTCLIENTDATETIME_H

#include "library/client/networkclient.h"

class TestClientDateTime: public NetworkClient
{
public:
    TestClientDateTime(const std::string &host, const std::string &port, Protocol protocol);

    void run();
};

#endif // TESTCLIENTDATETIME_H
