#include "testclientecho.h"
#include <iostream>

TestClientEcho::TestClientEcho(const std::string &host, const std::string &port, Protocol protocol): NetworkClient(host, port, protocol)
{

}

void TestClientEcho::run()
{
    io->connect();
    if (*io){
        std::cout << __PRETTY_FUNCTION__ << ": Connected." << std::endl;
    } else {
        std::cout << __PRETTY_FUNCTION__ << ": Error connecting." << std::endl;
    }

    for (int i = 0; i < 1000; ++i) {
        io->write("Testing " + std::to_string(i));

        std::string answer;
        io->read_until(answer, "\0", std::chrono::seconds(1));
        std::cout << __PRETTY_FUNCTION__ << ": " << answer << std::endl;
    }

    io->disconnect();
}
