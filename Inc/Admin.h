#ifndef HEADER_H_ADMIN
#define HEADER_H_ADMIN
#include <iostream>
#include <string>
#include <limits>
#include "User.h"
#include "Client.h"

using namespace std;

class Admin  : public User 
{
    public:
    Client* client;
    Admin(Client* client);
    void addMenuItem();
    void deleteMenuItem();
    void updateMenuItem();
    void performRoleFunctions();
    void showOptions();
    void clearInputBuffer();
    void viewAllMenuItems();
};
#endif