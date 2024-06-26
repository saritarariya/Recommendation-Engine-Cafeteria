#include "AccessManager.h"
#include "Client.h"
#include "Employee.h"
#include "Chef.h"
#include "Admin.h"
#include <iostream>
#include <sstream>

AccessManager::AccessManager() {}

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
    Employee* employee = new Employee(this->dbManager->client); 
    employee->client->sendRole("EMPLOYEE");
}

void AccessManager::grantChefAccess(const std::string& email) {
    std::cout << "Granting chef access to " << email << std::endl;
    Chef*chef = new Chef(this->dbManager->client);
    chef->client->sendRole("chef");
    
}

void AccessManager::grantAdminAccess(const std::string& email) {
    std::cout << "Granting admin access to " << email << std::endl;
    Client *client = new Client();
    Admin*admin = new Admin(client);
    admin->client->connectToServer();
    admin->client->sendRole("HY mehul sarita this side !!!!");
    admin->adminFunctions(dbManager);
}
