#ifndef HEADER_H_ADMIN
#define HEADER_H_ADMIN

#include <iostream>
#include <string>
#include <limits>
#include <cctype>
#include <algorithm>
#include <vector>
#include "User.h"
#include "Client.h"
#include "Utility.h"

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
    void viewAllMenuItems();
};
#endif
