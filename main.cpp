#include <iostream>
#include <thread>
#include "library/server/networkserver.h"
#include "library/test/testsessionecho.h"
#include "library/test/testclientecho.h"
#include "library/test/testsessiondatetime.h"
#include "library/test/testclientdatetime.h"

int main()
{
    bool run = true;

    // First start UDP server.
    NetworkServer server_udp("1234", NetworkServer::udp);
    std::thread server_thread_udp([&]{
        server_udp.open();
        while (run) {
            std::unique_ptr<NetworkSessionBase> session_interface = server_udp.accept();
            if (session_interface) {
                // UDP creates just one session
                TestSessionDateTime session(std::move(session_interface));
                session.run();
            } else {
                break;
            }
        }
    });

    // Now start the UDP client, just one.
    std::thread thread([]{
        TestClientDateTime client("127.0.0.1", "1234", NetworkClient::udp);
        client.run();
    });

    // Start the TCP server
    NetworkServer server_tcp("1234", NetworkServer::tcp);
    std::thread server_thread_tcp([&]{
        server_tcp.open();
        while (run) {
            std::unique_ptr<NetworkSessionBase> session_interface = server_tcp.accept();
            if (session_interface) {
                // There can be many TCP sessions
                std::unique_ptr<TestSessionDateTime> session( new TestSessionDateTime(std::move(session_interface)) );
                std::thread([session = std::move(session)]{
                    session->run();
                }).detach();
            } else {
                break;
            }
        }
    });

    std::vector<std::thread> threads;
    for (int i = 0; i < 3; ++i) {
        std::thread thread([]{
            TestClientDateTime client("127.0.0.1", "1234", NetworkClient::tcp);
            client.run();
        });
        threads.push_back(std::move(thread));
    }

    // Wait until threads finish
    thread.join();
    for (std::thread &thread: threads) {
        thread.join();
    }

    // Close the server
    run = false;
    server_udp.close();
    server_thread_udp.join();

    return 0;
}
