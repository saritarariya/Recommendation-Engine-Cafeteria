#include <iostream>
#include <csignal>
#include "Server.h"

Server hostServer;

void signalHandler(int signal)
{
    hostServer.handleCtrlC(signal);
}

int main()
{
    
    std::signal(SIGINT, signalHandler);
    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0) {
        std::cerr << "WSAStartup failed: " << result << std::endl;
        return 1;
    }
    if (hostServer.createSocket() != 0)
    {
        std::cerr << "Failed to initialize Winsock." << std::endl;
        return 1;
    }

    hostServer.assignServerAddress();

    if (hostServer.bindSocketAddress() != 0)
    {
        std::cerr << "Failed to bind socket." << std::endl;
        return 1;
    }

    if (hostServer.listenFunction() != 0)
    {
        std::cerr << "Failed to listen on socket." << std::endl;
        return 1;
    }

    if (!hostServer.handleMultipleClients())
    {
        std::cerr << "Failed to handle multiple clients." << std::endl;
        return 1;
    }

    return 0;
}
