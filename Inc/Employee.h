#ifndef HEADER_H_EMPLOYEE
#define HEADER_H_EMPLOYEE

#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <FoodItem.h>
#include "User.h"
#include "Client.h"

class Employee : public User
{
    public:
    FoodItem *foodItem;
    Employee(Client* client) : User(client) {}
    void voteForFoodItems();
    void performRoleFunctions();
    void viewNotifications();
    void provideFeedback();
    void viewAllMenuItems();
    void createProfile(int userId);
    bool isProfileCreated(int userId);
    bool savePreference(int userId, const std::string& preferenceType, const std::string& preferenceValue);
    std::vector<std::string> getRolledOutFoodItems();
    std::vector<std::string> recommendFoodItems(int employeeId, const std::vector<std::string>& availableFoodItems);
    std::vector<std::pair<std::string, std::string>> parsePreferences(const std::string& preferenceString);
    std::string fetchEmployeePreferences(int employeeId);
    void getFoodItemDetails(std::string foodItemID);
    void parseFoodItemDetailString(std::string foodItemDetailString);
};
#endif