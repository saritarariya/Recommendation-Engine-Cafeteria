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
    static std::string getNonEmptyInput(const std::string &prompt, const std::string &errorMessage);
    static bool isValidCuisine(const std::string &cuisine);
    static bool isValidSpiceLevel(const std::string &spiceLevel);
    static bool isValidType(const std::string &type);
    static bool isValidCategory(const std::string &category);
    static std::string getValidatedInput(const std::string &prompt, const std::string &errorMessage, bool (*isValid)(const std::string &));
    static std::string getNumericInput(const std::string &prompt, const std::string &errorMessage);
    static std::string getBinaryInput(const std::string &prompt, const std::string &errorMessage);
};
#endif
