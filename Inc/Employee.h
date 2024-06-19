#ifndef HEADER_H_EMPLOYEE
#define HEADER_H_EMPLOYEE
#include <string>
#include <iostream>
#include "Client.h"

class Employee : public Client
{   
    public:
    std::string email;
    // std::string provideFeedback();
    // std::string chooseFoodItemsForNextDay();
    // int provideRating(); 
    // std::string getFoodItemsForNextDay();
    void showOptions();
};
#endif