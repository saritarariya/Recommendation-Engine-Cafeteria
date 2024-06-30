
#include <iostream>
#include <csignal>
#include "Server.h" // Ensure this header file includes the necessary definitions

// Global server instance
Server hostServer;

// Signal handler for graceful shutdown
void signalHandler(int signal)
{
    hostServer.handleCtrlC(signal);
}

int main()
{
    
    // Set up the signal handler for Ctrl+C (SIGINT)
    std::signal(SIGINT, signalHandler);
    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0) {
        std::cerr << "WSAStartup failed: " << result << std::endl;
        return 1;
    }
    // Step 1: Initialize Winsock
    if (hostServer.createSocket() != 0)
    {
        std::cerr << "Failed to initialize Winsock." << std::endl;
        return 1;
    }

    // Step 2: Assign server address
    hostServer.assignServerAddress();

    // Step 3: Bind the socket
    if (hostServer.bindSocketAddress() != 0)
    {
        std::cerr << "Failed to bind socket." << std::endl;
        return 1;
    }

    // Step 4: Listen for incoming connections
    if (hostServer.listenFunction() != 0)
    {
        std::cerr << "Failed to listen on socket." << std::endl;
        return 1;
    }

    // Step 5: Handle multiple clients
    if (!hostServer.handleMultipleClients())
    {
        std::cerr << "Failed to handle multiple clients." << std::endl;
        return 1;
    }

    return 0;
}
