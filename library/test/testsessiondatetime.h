#ifndef TESTSESSIONDATETIME_H
#define TESTSESSIONDATETIME_H

#include "library/server/networksession.h"

class TestSessionDateTime: public NetworkSession
{
public:
    TestSessionDateTime(std::unique_ptr<NetworkSessionBase> session_interface);

    void run() override;
};

#endif // TESTSESSIONDATETIME_H
