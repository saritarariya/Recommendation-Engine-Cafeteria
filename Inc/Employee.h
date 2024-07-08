#ifndef HEADER_H_EMPLOYEE
#define HEADER_H_EMPLOYEE

#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include "User.h"
#include "Client.h"

class Employee : public User
{   
    public:
    Employee(Client* client) : User(client) {}
    void voteForFoodItems();
    // std::string getFoodItemsForNextDay();
    void performRoleFunctions();
    void viewNotifications();
    void provideFeedback();
    void viewAllMenuItems();
};
#endif