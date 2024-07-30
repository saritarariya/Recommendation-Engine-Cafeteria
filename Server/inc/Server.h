#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>
#include <thread>
#include <mutex>
#include <vector>
#include <cassert>
#include "clientRequestHandler.h"

#pragma comment(lib, "Ws2_32.lib")

struct ClientsData
{
    int clientCount;
    SOCKET socket;
    std::string email;
    int clientID;
};

class Server
{
private:
    SOCKET serverSocket;
    SOCKET clientSocket;
    struct sockaddr_in server, client;
    std::vector<ClientsData> collectionOfClients;
    std::mutex clientsMutex;
    int countOfClients;
    void handleClient(const SOCKET clientSocket);
    void endConnection(int id);
    void closeServer();
public:
    Server();
    ~Server();
    int createSocket();
    void assignServerAddress();
    int bindSocketAddress();
    bool handleMultipleClients();
    SOCKET getSocketHandler();
    void handleCtrlC(int signal);
    int listenFunction();
};

#endif // SERVER_H
