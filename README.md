# Network classes for wrapping ASIO - UDP, TCP and ICMP protocols

C++ classes wrapping the Boost Asio libraries. 

The goal was to provide a basic uniform interface for server and client with a simple switch between UDP, TCP and ICMP protocols (just one parameter in the constructor).

## Example application

This is just a fun project for testing the ASIO libraries. I wanted to wrap them and create my own server and client interface with simple protocol selection.

The goal is also to simplify the development of derived classes.

Since the ASIO does not support uniform interface for between the UDP, TCP and ICMP protocols, there is a lot of repeating in the code. I don't like it, but I did not find better implementation.

## Getting Started

The project has classes implementing the ASIO server and client interface and main.cpp, in which the classes are tested.

I wrote the project in Qt Creator.

### Prerequisites

I am using C++14, so newer toolchain is needed. Also, I am using the __PRETTY_FUNCTION__ macro, which I think is a GCC extension. If this is an issue, just use __func__ instead.

## Classes Description

### [Client](library/client)

Here are all the client classes. There is one virtual class NetworkClientBase, defining the interface. Then there are derived classes for TCP, UDP, and ICMP.

The most important class from the user perspective is the NetworkClient, which creates the interface according to the constructor parameter.

Just derive from the NetworkClient and use the io object for implementing the communication.

### [Server](library/server)

Here are all the server classes. It consists of a server and session. There is a base class and derived class for each protocol. 

User needs to run a server and accept (creates) sessions.

The most important class is NetworkSession - just derive from it, override the virtual function run and use the io object for implementing the communication.

### [Test](library/test)

Here are some examples of how to derive from the classes. It is quite simple to use them.

## Recommendation

The code is quite large due to the multiple protocols support. If needed, the code can be simplified just for one protocol.

## Author

* **Jan Moravec**


## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details
