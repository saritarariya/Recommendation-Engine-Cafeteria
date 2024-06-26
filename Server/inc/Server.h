#ifndef HEADER_H_SERVER
#define HEADER_H_SERVER

#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>
#include <thread>
#include <mutex>
#include <vector>
#include <cassert>

// Link with the Ws2_32.lib library
#pragma comment(lib, "Ws2_32.lib")

struct ClientsData {
    int id;
    SOCKET socket;
    char name[100];  // Adjust size as needed
};

class Server {
    SOCKET serverSocket;
    std::thread thrd;
    std::vector<ClientsData> collectionOfClients;
    int countOfClients = 0;
    std::mutex printMutex, clientsMutex;
    struct sockaddr_in server;
    struct sockaddr_in client;
    SOCKET clientSocket;
public:
    Server() : serverSocket(INVALID_SOCKET), clientSocket(INVALID_SOCKET) {}
    ~Server() {
        closesocket(serverSocket);
        WSACleanup();
    }

    void setName(const int id, const char* name);
    void displayMessageOnServer(const std::string& str);
    void broadcastMessage(const std::string& message, const int senderId);
    void endConnection(const int id);
    void handleClient(const SOCKET clientSocket, const int id);
    int createSocket();
    void assignServerAddress();
    int bindSocketAddress();
    void closeServer();
    bool handleMultipleClients();
    SOCKET getSocketHandler();
    void handleCtrlC(int signal);
    int listenFunction();
};

#endif
