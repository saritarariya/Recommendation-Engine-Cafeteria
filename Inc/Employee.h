#ifndef HEADER_H_EMPLOYEE
#define HEADER_H_EMPLOYEE
#include <string>
#include <iostream>
#include "Client.h"
class Employee
{   
    public:
    // std::string provideFeedback();
    // std::string chooseFoodItemsForNextDay();
    // int provideRating(); 
    // std::string getFoodItemsForNextDay();
    Client* client;
    Employee(Client*);
    void employeeFunctions();
};
#endif