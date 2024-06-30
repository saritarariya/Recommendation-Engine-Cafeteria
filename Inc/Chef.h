#ifndef HEADER_H_CHEF
#define HEADER_H_CHEF

#include <string>
#include <iostream>
#include <vector>
#include "User.h"
#include "Client.h"
#include "RecommendationEngine.h"

class Chef : public User
{

private:
    // std::string rollOutFoodItems();
    // std::string getLastDayVoting();
public:
    Chef(Client *client) : User(client) {}
    void performRoleFunctions();
    std::vector<std::string> getFoodItemsToRollOut();
};

#endif