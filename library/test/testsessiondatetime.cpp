#include "testsessiondatetime.h"

TestSessionDateTime::TestSessionDateTime(std::unique_ptr<NetworkSessionBase> session_interface): NetworkSession(std::move(session_interface))
{

}

void TestSessionDateTime::run()
{
    example_datetime();
}
