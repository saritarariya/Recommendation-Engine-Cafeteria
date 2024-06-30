#ifndef HEADER_H_CHEF
#define HEADER_H_CHEF

#include <string>
#include <iostream>
#include "User.h"
#include "Client.h"

class Chef : public User
{

private:
    // std::string rollOutFoodItems();
    // std::string getLastDayVoting();
    // std::string getFoodItemsToRollOut();
public:
    Chef(Client *client) : User(client) {}
    void performRoleFunctions();
};

#endif