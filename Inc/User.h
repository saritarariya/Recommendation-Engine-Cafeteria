#ifndef USER_H
#define USER_H

#include <string>
#include "Client.h"

class User
{
public:
    User(Client *client) : client(client) {}
    virtual ~User() {}
    virtual void performRoleFunctions() = 0;
    Client *client;
    bool sendRequest(const std::string &request);
    std::string receiveResponse();
};
#endif
