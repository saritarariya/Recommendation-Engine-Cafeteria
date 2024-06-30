#ifndef HEADER_H_EMPLOYEE
#define HEADER_H_EMPLOYEE

#include <string>
#include <iostream>
#include "User.h"
#include "Client.h"

class Employee : public User
{   
    public:
    Employee(Client* client) : User(client) {}
    // std::string provideFeedback();
    // std::string chooseFoodItemsForNextDay();
    // int provideRating(); 
    // std::string getFoodItemsForNextDay();
    void performRoleFunctions();
    // void performRoleFunctions() override {
    //     // Define employee-specific functions here
    //     std::cout << "Employee role functions" << std::endl;
    // }

    // void employeeFunctions() {
    //     // Implement employee-specific functions using sendRequest and receiveResponse
    // }
};
#endif