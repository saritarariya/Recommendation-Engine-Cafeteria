#ifndef HEADER_H_ADMIN
#define HEADER_H_ADMIN

#include <iostream>
#include <string>
#include <limits>
#include "User.h"
#include "Client.h"

class Admin : public User
{
public:
    Admin(Client *client) : User(client) {}
    void performRoleFunctions();

private:
    void addMenuItem();
    void deleteMenuItem();
    void updateMenuItem();
    void showOptions();
    void clearInputBuffer();
    void viewAllMenuItems();
};
#endif
