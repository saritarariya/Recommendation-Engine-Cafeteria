#include "AccessManager.h"
#include "Client.h"
#include "Employee.h"
#include "Chef.h"
#include "Admin.h"
#include <iostream>
#include <sstream>

AccessManager::AccessManager(Client *client) {
    this->client = client;
}

void AccessManager::grantAccess(const std::string& email) {
    std::string role = extractRole(email);
    if (role.find("employee") != std::string::npos) {
        grantEmployeeAccess(email);
    } else if (role.find("chef") != std::string::npos) {
        grantChefAccess(email);
    } else if (role.find("admin") != std::string::npos) {
        grantAdminAccess(email);
    }
}

std::string AccessManager::extractRole(const std::string& email) {
    std::istringstream iss(email);
    std::string token;
    while (std::getline(iss, token, '.')) {
        if (token.find("@") != std::string::npos) {
            break;
        }
    }
    return token;
}

void AccessManager::grantEmployeeAccess(const std::string& email) {
    std::cout << "Granting employee access to " << email << std::endl;
    Employee* employee = new Employee(client);
    employee->performRoleFunctions();
    delete employee;
}

void AccessManager::grantChefAccess(const std::string& email) {
    std::cout << "Granting chef access to " << email << std::endl;
    Chef* chef = new Chef(client);
    chef->getFoodItemsToRollOut();
    delete chef;
}

void AccessManager::grantAdminAccess(const std::string& email) {
    std::cout << "Granting admin access to " << email << std::endl;
    Admin* admin = new Admin(client);
    admin->performRoleFunctions();
    delete admin;
}
