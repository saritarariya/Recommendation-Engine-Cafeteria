#ifndef HEADER_H_CLIENT
#define HEADER_H_CLIENT

#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>

#pragma comment(lib, "Ws2_32.lib")

#define MAX_LEN 200

class Client
{
private:
    struct sockaddr_in client;
    int portNumber;
    std::string mailID;
    std::string password;
    std::string role;
    std::string userID;
    SOCKET clientSocket;
    int createSocket();
    int connectSocket();
    void assignClientAddress(const std::string &ipAddress, int port);

public:
    bool connectToServer();
    bool verifyUser();
    void setEmail(const std::string &email);
    void setRole(const std::string &role);
    std::string getRole();
    std::string getEmail();
    SOCKET getClientSocket();
    void setPassword(const std::string& password);
    int getUserID();
};
#endif