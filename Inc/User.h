#ifndef USER_H
#define USER_H

#include <string>
#include "Client.h"

class User {
public:
    User(Client* client) : client(client) {}
    virtual ~User() {}
    virtual void performRoleFunctions() = 0;

protected:
    Client* client;

    bool sendRequest(const std::string& request) {
        if (send(client->getClientSocket(), request.c_str(), request.size(), 0) == -1) {
            std::cout << "Failed to send your request to server. Error code: " << WSAGetLastError() << std::endl;
            return false;
        }
        return true;
    }

    std::string receiveResponse() {
        char buffer[10000];
        int bytesReceived = recv(client->getClientSocket(), buffer, sizeof(buffer), 0);

        if (bytesReceived > 0) {
            buffer[bytesReceived] = '\0';
            return std::string(buffer);
        } else {
            std::cout << "No response received or connection closed. Error code: " << WSAGetLastError() << std::endl;  // Log if no response is received
        }
        return "";
    }
};

#endif
