#ifndef HEADER_H_CHEF
#define HEADER_H_CHEF

#include <string>
#include <iostream>
#include "Client.h"
class Chef
{
    public:
    Client* client;
    std::string mailID;
    Chef(Client*);
    // std::string rollOutFoodItems();
    // std::string getMonthlyReport(std::string foodItem);
    // std::string getLastDayVoting();
    // std::string getFoodItemsToRollOut();
    void chefFunctions();
};

#endif