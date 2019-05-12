#ifndef TESTSESSION_H
#define TESTSESSION_H

#include "library/server/networksession.h"

class TestSessionEcho: public NetworkSession
{
public:
    TestSessionEcho(std::unique_ptr<NetworkSessionBase> session_interface);

    void run() override;
};

#endif // TESTSESSION_H
