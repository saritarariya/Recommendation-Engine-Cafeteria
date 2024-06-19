#ifndef HEADER_H_ADMIN
#define HEADER_H_ADMIN
#include <iostream>
#include <string>
#include "Client.h"

class Admin : public Client
{
    public:
    std::string mailId;
    std::string addMenuItem();
    std::string deleteMenuItem();
    std::string updateMenuItem(std::string price , std::string availabily);
    //std::string getMonthlyReport(std::string foodItem);
    void showOptions();
};
#endif