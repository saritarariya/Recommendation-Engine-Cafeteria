#ifndef ACCESSMANAGER_H
#define ACCESSMANAGER_H
#include <iostream>
#include <string>
#include <vector>
#include "databaseManager.h"

class AccessManager {
public:
    struct User {
        std::string email;
        std::string role;
    };
    void grantAccess(const std::string& email);
    AccessManager();
    DatabaseManager *dbManager;
private:
    std::vector<User> users;
    std::string extractRole(const std::string& email);
    void grantEmployeeAccess(const std::string& email);
    void grantChefAccess(const std::string& email);
    void grantAdminAccess(const std::string& email);
};

#endif // ACCESSMANAGER_H
