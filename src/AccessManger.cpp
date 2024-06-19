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
    } else if (role.find("chef") != std::string::npos) {
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
    std::cout<<token<<std::endl;
    return token;
}

void AccessManager::grantEmployeeAccess(const std::string& email) {
    std::cout << "Granting employee access to " << email << std::endl;
    Employee * E1 = new Employee();
    if(E1->connectToServer() == 1) {
        E1->mailID = email;
        E1->showOptions();
        E1->sendRole("employee");
        E1->messageTransfer();
    } else {
        std::cout<<"unable to connect to server"<<std::endl;
    }
}

void AccessManager::grantChefAccess(const std::string& email) {
    std::cout << "Granting chef access to " << email << std::endl;
    Chef * E1 = new Chef();
    if(E1->connectToServer() == 1) {
        E1->mailID = email;
        E1->showOptions();
        E1->sendRole("chef");
        E1->messageTransfer();
    } else {
        std::cout<<"unable to connect to server"<<std::endl;
    }
}

void AccessManager::grantAdminAccess(const std::string& email) {
    std::cout << "Granting admin access to " << email << std::endl;
    Admin * E1 = new Admin();
    if(E1->connectToServer() == 1) {
    E1->mailID = email;
    E1->showOptions();
    E1->sendRole("Admin");
    E1->messageTransfer();
     } else {
        std::cout<<"unable to connect to server"<<std::endl;
    }
}
