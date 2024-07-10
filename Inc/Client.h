#ifndef HEADER_H_CLIENT
#define HEADER_H_CLIENT

#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>
#include <thread>
#include <mutex>

#pragma comment(lib, "Ws2_32.lib")

#define MAX_LEN 200

class Client
{
private:
    bool exitFlag = false;
    std::thread tSend, tReceive;
    struct sockaddr_in client;
    int portNumber;
    std::string mailID;
    std::string password;
    std::string role;
public:
    SOCKET clientSocket;
    ~Client()
    {
        closesocket(clientSocket);
        WSACleanup();
    }
    int createSocket();
    int connectSocket();
    void assignClientAddress(const std::string &ipAddress, int port);
    void handleCtrlC(int signal);
    bool connectToServer();
    bool verifyUser();
    void setEmail(const std::string &email);
    void setRole(const std::string &role);
    std::string getRole();
    std::string getEmail();
    SOCKET getClientSocket();
    void setPassword(const std::string& password);
};

#endif