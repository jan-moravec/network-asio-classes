#include <iostream>
#include <mutex>
#include "library/client/networkclienttcp.h"
#include "library/client/networkclientudp.h"
#include "library/client/networkclient.h"
#include "library/server/networkserver.h"

static std::mutex mutex;

void thread_function(int n)
{
    //std::cout << __PRETTY_FUNCTION__ << " " << n << std::endl;
    NetworkClient client("127.0.0.1", "1234", NetworkClient::udp);
    std::lock_guard<std::mutex> lck(mutex);
    client.interface().connect();
    if (client.interface()) {
        std::string message = "Ahoj serviku!\n";
        client.interface().write(message);

        //std::this_thread::sleep_for(std::chrono::milliseconds(10));
        uint8_t buffer[128]{};
        //std::cout << client.interface().read_exactly(buffer, 25, std::chrono::seconds(5)) << " " << (char *)buffer << std::endl;
        std::string answer;
        std::cout << __PRETTY_FUNCTION__ << " " << n << " " <<  client.interface().read_until(answer, "\n", std::chrono::seconds(10)) << " " << answer << std::endl;
        //std::cout << client.interface().available() << std::endl;
        //std::cout << client.interface().available() << std::endl;
        client.interface().disconnect();
    }
}

int main()
{
    bool run = true;
    NetworkServer server("1234", NetworkServer::udp);
    std::thread server_thread([&]{
        server.interface().open();
        while (run) {
            server.interface().accept();
        }
    });

    std::vector<std::thread> threads;
    for (int i = 0; i < 100; ++i) {
        std::thread thread(thread_function, i);
        threads.push_back(std::move(thread));
        //std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }


    std::cin.get();
    run = false;
    server.interface().close();

    for (std::thread &thread: threads) {
        thread.join();
    }

    server_thread.join();

    /*NetworkClient client("127.0.0.1", "1234", NetworkClient::tcp);
    client.interface().connect();
    if (client.interface()) {
        std::string message = "Ahoj serviku!\n";
        client.interface().write(message);

        //std::this_thread::sleep_for(std::chrono::milliseconds(10));
        uint8_t buffer[128]{};
        //std::cout << client.interface().read_exactly(buffer, 25, std::chrono::seconds(5)) << " " << (char *)buffer << std::endl;
        std::string answer;
        std::cout << client.interface().read_until(answer, "\n", std::chrono::seconds(5)) << " " << answer << std::endl;
        std::cout << client.interface().available() << std::endl;
        std::cout << client.interface().available() << std::endl;
    }
    client.interface().disconnect();*/
}
