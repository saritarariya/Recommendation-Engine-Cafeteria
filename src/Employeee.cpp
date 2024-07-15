#include "Employee.h"

void Employee::viewNotifications()
{
    std::string request = "viewNotifications:";
    sendRequest(request);
    std::string response = receiveResponse();
    std::cout << "Server response:" << std::endl;
    std::cout << response << std::endl;
}

void Employee::provideFeedback()
{
    std::string request = "showAllMenuItems";
    sendRequest(request);
    std::string response = receiveResponse();
    std::cout << "Server response:" << std::endl;
    std::cout << response << std::endl;

    int foodItemId, rating;
    std::string comment;
    std::string FoodItemName;
    std::cout << "Enter Food Item name: ";
    std::cin.ignore();
    std::getline(std::cin, FoodItemName);
    std::cout << "Enter Rating (1-5): ";
    std::cin >> rating;

    std::cin.ignore(1, '\n');
    std::cout << "Enter Comment: ";
    std::getline(std::cin, comment);
    
    std::string request1 = "getFoodItemId: " +  FoodItemName;
    sendRequest(request1);
    std::string foodItemIdStr = receiveResponse();
    foodItemId = std::stoi(foodItemIdStr);
    std::ostringstream oss;  
    oss << "provideFeedback:" << foodItemId << "," << rating << "," << comment;
    std::string request2 = oss.str();

    sendRequest(request2);
    std::string response1 = receiveResponse();
    std::cout << "Server response:" << std::endl;
    std::cout << response1 << std::endl;
}

std::vector<std::string> Employee::getRolledOutFoodItems()
{
    std::vector<std::string> foodItems;
    std::string request = "viewNotifications:";
    sendRequest(request);
    std::string response = receiveResponse();

    std::vector<std::string> notifications;
    std::istringstream iss(response);
    std::string line;
    while (std::getline(iss, line))
    {
        notifications.push_back(line);
    }
    for (const auto &notification : notifications)
    {
        if (notification.find("Rolled out food items:") != std::string::npos)
        {
            std::cout << notification << std::endl;
            std::istringstream iss(notification.substr(22));
            std::string foodItem;

            while (std::getline(iss, foodItem, ','))
            {
                foodItems.push_back(foodItem);
            }
        }
    }
    return foodItems;
}

void Employee::voteForFoodItems()
{
    std::string request = "getID:";
    sendRequest(request);
    std::string userID = receiveResponse();
    int ID = std::stoi(userID);
    std::vector<std::string> foodItems = getRolledOutFoodItems();
    std::vector<std::string> recommendFoodItemsList  = recommendFoodItems(ID, foodItems);
    for (size_t i = 0; i < recommendFoodItemsList.size(); ++i)
    {
        std::cout << i + 1 << ". " << recommendFoodItemsList[i] << std::endl;
    }

    std::cout << "Enter the number of the food item to vote for: ";
    int itemChoice;
    std::cin >> itemChoice;

    if (itemChoice >= 0 && itemChoice <= recommendFoodItemsList.size())
    {
        std::string request1 = "getFoodItemId:" + recommendFoodItemsList[itemChoice - 1];
        sendRequest(request1);
        std::string foodItemIdStr = receiveResponse();
        int foodItemId = std::stoi(foodItemIdStr);

        if (foodItemId != -1)
        {
            std::ostringstream oss;
            oss << "submitVote:" << userID << "," << foodItemId;

            std::string request2 = oss.str();
            sendRequest(request2);
            std::string response = receiveResponse();
            std::cout << "Server response: " << response << std::endl;
        }
        else
        {
            std::cout << "Note able to fetch the correct food item ID.";
        }
    }
    else
    {
        std::cout << "Invalid choice." << std::endl;
    }
}

void Employee::performRoleFunctions()
{
    int choice;
    do
    {
        std::cout << "Please choose an operation:" << std::endl;
        std::cout << "1. Provide Feedback" << std::endl;
        std::cout << "2. Choose Food Items for Next Day" << std::endl;
        std::cout << "3. View Notifications" << std::endl;
        std::cout << "4. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice)
        {
        case 1:
            provideFeedback();
            break;
        case 2:
            voteForFoodItems();
            break;
        case 3:
            viewNotifications();
            break;
        case 4:
            std::cout << "Exiting..." << std::endl;
            break;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
            break;
        }
    } while (choice != 5);
}

void Employee::viewAllMenuItems()
{
    std::string request = "showAllMenuItems";
    sendRequest(request);
    std::string response = receiveResponse();
    std::cout << "Server response:" << std::endl;
    std::cout << response << std::endl;
}

void Employee::createProfile(int userId)
{
    if (isProfileCreated(userId))
    {
        std::cout << "Profile already created. Skipping profile creation." << std::endl;
        return;
    }

    std::string preferenceType, preferenceValue;

    std::cout << "Please answer these questions to know your preferences" << std::endl;

    std::cout << "1) Please select one-\n- Vegetarian\n- Non Vegetarian\n- Eggetarian" << std::endl;
    std::cin.ignore(); 
    std::getline(std::cin, preferenceValue);
    preferenceType = "Diet";
    savePreference(userId, preferenceType, preferenceValue);

    std::cout << "2) Please select your spice level\n- High\n- Medium\n- Low" << std::endl;
    std::getline(std::cin, preferenceValue);
    preferenceType = "Spice Level";
    savePreference(userId, preferenceType, preferenceValue);

    std::cout << "3) What do you prefer most?\n- North Indian\n- South Indian\n- Other" << std::endl;
    std::getline(std::cin, preferenceValue);
    preferenceType = "Cuisine";
    savePreference(userId, preferenceType, preferenceValue);

    std::cout << "4) Do you have a sweet tooth?\n- Yes\n- No" << std::endl;
    std::getline(std::cin, preferenceValue);
    preferenceType = "Sweet Tooth";
    savePreference(userId, preferenceType, preferenceValue);
}

bool Employee::isProfileCreated(int userId) {
    std::string request = "isProfileCreated:" + std::to_string(userId);
    sendRequest(request);
    std::string response = receiveResponse();
    std::cout << "Server response:" << std::endl;
    std::cout << response << std::endl;
    return response == "true";
}

bool Employee::savePreference(int userId, const std::string &preferenceType, const std::string &preferenceValue) {
    std::string request = "savePreference:" + std::to_string(userId) + ":" + preferenceType + ":" + preferenceValue;
    sendRequest(request);
    std::string response = receiveResponse();
    std::cout << "Server response:" << std::endl;
    std::cout << response << std::endl;
    return response == "Preference saved successfully";
}

std::string Employee::fetchEmployeePreferences(int employeeId) {
    std::string request = "fetchEmployeePreferences:" + std::to_string(employeeId);
    sendRequest(request);
    std::string response = receiveResponse();
    return response.empty() ? "No preferences found" : response;
}

std::vector<std::string> Employee::recommendFoodItems(int employeeId, const std::vector<std::string> &availableFoodItems)
{
    std::string preferenceString = fetchEmployeePreferences(employeeId);
    std::vector<std::pair<std::string, std::string>> preferences = parsePreferences(preferenceString);
    std::vector<std::pair<std::string, int>> foodItemMatches;
    for (const auto &availableFoodItem : availableFoodItems)
    {
        getFoodItemDetails(availableFoodItem);
        int matchCount = 0;
        for (const auto &preference : preferences)
        {
            if ((preference.first == "Diet") && (preference.second == foodItem->getType()))
            {
                matchCount++;
            }
            else if ((preference.first == "Spice Level") && (preference.second == foodItem->getSpiceLevel()))
            {
                matchCount++;
            }
            else if ((preference.first == "Cuisine") && (preference.second == foodItem->getCuisine()))
            {
                matchCount++;
            }
            else if ((preference.first == "Sweet Tooth") && (preference.second == foodItem->isFoodSweet()))
            {
                matchCount++;
            }
        }
        foodItemMatches.push_back({availableFoodItem, matchCount});
    }
    
    for (size_t i = 0; i < foodItemMatches.size() - 1; ++i) {
        for (size_t j = 0; j < foodItemMatches.size() - i - 1; ++j) {
            if (foodItemMatches[j].second < foodItemMatches[j + 1].second) {
                std::swap(foodItemMatches[j], foodItemMatches[j + 1]);
            }
        }
    }

    std::vector<std::string> recommendedItems;
    for (const auto &item : foodItemMatches)
    {
        if (item.second > 0) 
        {
            recommendedItems.push_back(item.first);
        }
    }
    return recommendedItems;
}

std::vector<std::pair<std::string, std::string>> Employee::parsePreferences(const std::string &preferenceString)
{
    std::vector<std::pair<std::string, std::string>> preferences;
    std::istringstream stream(preferenceString);
    std::string line;
    std::string type, value;

    while (std::getline(stream, line))
    {
        if (line.find("Preference Type:") != std::string::npos)
        {
            type = line.substr(line.find(":") + 2);
        }
        else if (line.find("Preference Value:") != std::string::npos)
        {
            value = line.substr(line.find(":") + 2);
            preferences.emplace_back(type, value);
        }
    }
    return preferences;
}

void Employee::getFoodItemDetails(std::string foodItemName)
{
    std::string request = "getFoodItemDetails:" + foodItemName;
    sendRequest(request);
    std::string response = receiveResponse();
    parseFoodItemDetailString(response);
}

void Employee::parseFoodItemDetailString(std::string foodItemDetailString)
{
    std::istringstream stream(foodItemDetailString);
    std::string line;
    std::vector<std::string> fields;

    while (std::getline(stream, line, ':')) {
        fields.push_back(line);
    }
    if (fields.size() < 9) {
        std::cerr << "Invalid food item detail string format." << std::endl;
        return;
    }
    std::string name = fields[0];
    std::string description = fields[1];
    double price = std::stod(fields[2]);
    std::string category = fields[3];
    bool availability = (fields[4] == "Yes");
    std::string type = fields[5];
    std::string spiceLevel = fields[6];
    std::string cuisine = fields[7];
    bool isSweet = (fields[8] == "Yes");
    foodItem = new FoodItem(name, description, price, category, availability, type, spiceLevel, cuisine, isSweet);
}
