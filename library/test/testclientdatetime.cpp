#include "testclientdatetime.h"
#include <iostream>
#include <thread>

TestClientDateTime::TestClientDateTime(const std::string &host, const std::string &port, Protocol protocol): NetworkClient(host, port, protocol)
{

}

void TestClientDateTime::run()
{
    io->connect();
    if (*io){
        std::cout << __PRETTY_FUNCTION__ << ": Connected." << std::endl;
    } else {
        std::cout << __PRETTY_FUNCTION__ << ": Error connecting." << std::endl;
    }

    for (int i = 0; i < 5; ++i) {
        io->write(" ");
        std::string answer;
        io->read_until(answer, "\0", std::chrono::seconds(1));
        std::cout << __PRETTY_FUNCTION__ << ": " << answer;

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    io->disconnect();
}
