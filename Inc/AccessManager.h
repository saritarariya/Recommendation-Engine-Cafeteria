#ifndef ACCESSMANAGER_H
#define ACCESSMANAGER_H
#include <iostream>
#include <string>
#include <vector>
#include "Client.h"

class AccessManager
{
public:
    void grantAccess(const std::string &email);
    AccessManager(Client *);

private:
    Client *client;
    std::string extractRole(const std::string &email);
    void grantEmployeeAccess(const std::string &email);
    void grantChefAccess(const std::string &email);
    void grantAdminAccess(const std::string &email);
};

#endif
