
#include <iostream>
#include <csignal>
#include "Server.h" // Ensure this header file includes the necessary definitions

// Global server instance
Server server;

// Signal handler for graceful shutdown
void signalHandler(int signal) {
    server.handleCtrlC(signal);
}

int main() {
    // Set up the signal handler for Ctrl+C (SIGINT)
    std::signal(SIGINT, signalHandler);

    // Step 1: Initialize Winsock
    if (server.createSocket() != 0) {
        std::cerr << "Failed to initialize Winsock." << std::endl;
        return 1;
    }

    // Step 2: Assign server address
    server.assignServerAddress();

    // Step 3: Bind the socket
    if (server.bindSocketAddress() != 0) {
        std::cerr << "Failed to bind socket." << std::endl;
        return 1;
    }

    // Step 4: Listen for incoming connections
    if (server.listenFunction() != 0) {
        std::cerr << "Failed to listen on socket." << std::endl;
        return 1;
    }

    // Step 5: Handle multiple clients
    if (!server.handleMultipleClients()) {
        std::cerr << "Failed to handle multiple clients." << std::endl;
        return 1;
    }

    return 0;
}
