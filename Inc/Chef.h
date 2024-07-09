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
public:
    Chef(Client *client) : User(client) {}
    void performRoleFunctions();
    std::vector<std::string> getFoodItemsToRollOut();
    void chooseFoodItemsForNextDay();
    void viewVotes();
    void viewNotifications();
    void viewAllMenuItems();
    std::string getMenuItemName(const int &foodItemId);
};

#endif