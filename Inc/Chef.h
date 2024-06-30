#ifndef HEADER_H_CHEF
#define HEADER_H_CHEF

#include <string>
#include <iostream>
#include "User.h"
#include "Client.h"

class Chef : public User
{
    public:
    Client*client;
    Chef(Client* client);
    // std::string rollOutFoodItems();
    // std::string getMonthlyReport(std::string foodItem);
    // std::string getLastDayVoting();
    // std::string getFoodItemsToRollOut();
    void performRoleFunctions();
    // void performRoleFunctions() override {
    //     // Define chef-specific functions here
    //     std::cout << "Chef role functions" << std::endl;
    // }

    // void chefFunctions() {
    //     // Implement chef-specific functions using sendRequest and receiveResponse
    // }
};

#endif