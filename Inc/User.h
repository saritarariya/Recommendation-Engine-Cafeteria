#ifndef USER_H
#define USER_H

#include <string>
#include "Client.h"

class User {
public:
    virtual ~User() {}
    virtual void performRoleFunctions() = 0;

protected:
    bool sendRequest(const std::string& request , Client *client) {
        if(client->getClientSocket() == INVALID_SOCKET) {
            std::cout<<"I am not connected to server\n";
        }
        if (send(client->getClientSocket(), request.c_str(), request.size(), 0) == -1)
          {
            std::cout<<"failed to send your request to server.\n";
            std::cout<<WSAGetLastError();
            return false;
          }
        return true;
        std::cout <<"request sent sucessfully\n";
    }

    std::string receiveResponse(Client *client) {
        char buffer[256];
        int bytesReceived = recv(client->getClientSocket(), buffer, sizeof(buffer), 0);
        if (bytesReceived > 0) {
            buffer[bytesReceived] = '\0';
            return std::string(buffer);
        }
        return "";
    }
};

#endif
