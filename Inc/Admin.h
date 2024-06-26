#ifndef HEADER_H_ADMIN
#define HEADER_H_ADMIN
#include <iostream>
#include <string>
#include <limits>
#include "Client.h"
#include "databaseManager.h"

using namespace std; 
class Admin
{
    public:
    Client* client;
    Admin(Client*);
    std::string mailId;
    void addMenuItem(DatabaseManager*);
    void deleteMenuItem(DatabaseManager*);
    void updateMenuItem(DatabaseManager*);
    void adminFunctions(DatabaseManager*);
    void showOptions();
    void clearInputBuffer();
};
#endif