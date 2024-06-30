#ifndef HEADER_H_CLIENT
#define HEADER_H_CLIENT 

#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>
#include <thread>
#include <mutex>

// Link with the Ws2_32.lib library
#pragma comment(lib, "Ws2_32.lib")

#define MAX_LEN 200

class Client
{
private:
    bool exitFlag = false;
    std::thread tSend, tReceive;
    struct sockaddr_in client;
    int portNumber;
public:
    SOCKET clientSocket;
    ~Client() {
        closesocket(clientSocket);
        WSACleanup();
    }
    std::string mailID;
    int createSocket();
    int connectSocket();
    void assignClientAddress(const std::string& ipAddress, int port);
    void sendRole(const std::string& role);
    void messageTransfer();
    void handleCtrlC(int signal);
    void sendMessage(SOCKET clientSocket);
    void recvMessage(SOCKET clientSocket);
    bool connectToServer();
    bool verifyUser();
    void setEmail(const std::string& email);
    std::string getEmail();
    SOCKET getClientSocket();
};

#endif