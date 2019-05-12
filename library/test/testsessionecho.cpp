#include "testsessionecho.h"

TestSessionEcho::TestSessionEcho(std::unique_ptr<NetworkSessionBase> session_interface): NetworkSession(std::move(session_interface))
{

}

void TestSessionEcho::run()
{
    example_echo();
}
