#include "Employee.h"

void Employee::viewNotifications()
{
    std::string request = "viewNotifications:";
    sendRequest(request);
    std::string response = receiveResponse();
    if (response.empty())
    {
        std::cerr << "Failed to retrieve notifications. Please try again later." << std::endl;
        return;
    }
    std::cout << "Server response:" << response << std::endl;
}

void Employee::displayAllMenuItems()
{
    sendRequest("showAllMenuItems");
    std::string response = receiveResponse();
    if (response.empty())
    {
        std::cerr << "Failed to retrieve menu items. Please try again later." << std::endl;
        return;
    }
    std::cout << "Menu Items:" << std::endl << response << std::endl;
}

int Employee::fetchFoodItemId(const std::string &foodItemName)
{
    std::string trimmedName = foodItemName;
    trimmedName.erase(trimmedName.begin(), std::find_if(trimmedName.begin(), trimmedName.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));

    std::string request = "getFoodItemId: " + trimmedName;
    sendRequest(request);
    std::string response = receiveResponse();
    if (response.empty())
    {
        std::cerr << "Failed to retrieve food item ID." << std::endl;
        return -1;
    }
    return std::stoi(response);
}

void Employee::provideFeedback()
{
    displayAllMenuItems();

    std::string FoodItemName = Utility::getNonEmptyInput("Enter Food Item name: ", "Name cannot be blank.");
    std::string rating = Utility::getNumericInput("Enter Rating (1-5): ", "Invalid input. Enter a numeric value for the rating(1-5)");
    std::string comment = Utility::getNonEmptyInput("Enter comment: ", "Comment cannot be blank.");

    int foodItemId = fetchFoodItemId(FoodItemName);
    if (foodItemId == -1)
    {
        std::cerr << "Failed to fetch the food item ID. Please try again." << std::endl;
        return;
    }
    std::ostringstream oss;
    oss << "provideFeedback:" << foodItemId << "," << rating << "," << comment;
    std::string request = oss.str();

    sendRequest(request);
    std::string response = receiveResponse();
    if (response.empty())
    {
        std::cerr << "Failed to provide feedback. Please try again later." << std::endl;
        return;
    }
    std::cout << "Server response:" << std::endl << response;
}

std::string Employee::viewNotificationsHelper()
{
    sendRequest("viewNotifications:");
    return receiveResponse();
}

std::vector<std::string> Employee::getRolledOutFoodItems()
{
    std::vector<std::string> foodItems;
    std::string response = viewNotificationsHelper();

    if (response.empty())
    {
        std::cerr << "Failed to retrieve rolled out food items. Please try again later." << std::endl;
        return foodItems;
    }

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

std::string Employee::fetchUserId()
{
    sendRequest("getID:");
    return receiveResponse();
}

void Employee::voteForFoodItems()
{
    std::string userIdStr = fetchUserId();
    if (userIdStr.empty())
    {
        std::cerr << "Failed to fetch user ID. Please try again later." << std::endl;
        return;
    }

    int userId = std::stoi(userIdStr);
    std::vector<std::string> rolledOutFoodItems = getRolledOutFoodItems();
    std::vector<std::string> recommendedFoodItems = recommendFoodItems(userId, rolledOutFoodItems);
    for (size_t i = 0; i < recommendedFoodItems.size(); ++i)
    {
        std::cout << i + 1 << ". " << recommendedFoodItems[i] << std::endl;
    }

    std::string prompt = "Enter the number of the food item to vote for:(1-5)";
    std::string errorMessage = "Invalid input please try again";
    std::string itemChoiceStr = Utility::getNumericInput(prompt, errorMessage);
    int itemChoice = stoi(itemChoiceStr);
    if (itemChoice >= 0 && itemChoice <= recommendedFoodItems.size())
    {
        int foodItemId = fetchFoodItemId(recommendedFoodItems[itemChoice - 1]);
        if (foodItemId == -1)
        {
            std::cerr << "Failed to fetch the food item ID. Please try again later." << std::endl;
            return;
        }

        std::ostringstream oss;
        oss << "submitVote:" << userId << "," << foodItemId;
        sendRequest(oss.str());
        std::string response = receiveResponse();
        if (response.empty())
        {
            std::cerr << "Failed to submit vote. Please try again later." << std::endl;
            return;
        }
        std::cout << "Server response: " << response << std::endl;
    }
    else
    {
        std::cout << "Invalid choice." << std::endl;
    }
}

void Employee::displayMainMenu()
{
    std::cout << "Please choose an operation:" << std::endl;
    std::cout << "1. Provide Feedback" << std::endl;
    std::cout << "2. Choose Food Items for Next Day" << std::endl;
    std::cout << "3. View Notifications" << std::endl;
    std::cout << "4. Exit" << std::endl;
}

void Employee::performRoleFunctions()
{
    while (true)
    {
        displayMainMenu();
        std::string prompt =  "Enter your choice: ";
        std::string errorMessage = "Invalid choice. Please try again.";
        std::string choiceStr = Utility::getNonEmptyInput(prompt,errorMessage);
        int choice = stoi(choiceStr);
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
            return;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
            break;
        }
    }
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
        return;
    }
    std::cout << "Please answer these questions to know your preferences" << std::endl;

    std::string preferenceValue = Utility::getValidatedInput("1) Please select one-\n- Vegetarian\n- Non Vegetarian\n- Eggetarian", "Not a valid input.", Utility::isValidType);
    std::string preferenceType = "Diet";
    savePreference(userId, preferenceType, preferenceValue);

    preferenceValue = Utility::getValidatedInput("2) Please select your spice level\n- High\n- Medium\n- Low", "Not a valid input.", Utility::isValidSpiceLevel);
    preferenceType = "Spice Level";
    savePreference(userId, preferenceType, preferenceValue);

    preferenceValue = Utility::getValidatedInput("3) What do you prefer most?\n- North Indian\n- South Indian\n- Other", "Not a valid input.", Utility::isValidCuisine);
    preferenceType = "Cuisine";
    savePreference(userId, preferenceType, preferenceValue);

    preferenceValue = Utility::getBinaryInput("4) Do you have a sweet tooth?\n- Yes\n- No", "Invalid input. Enter 1 for Yes or 0 for No.");
    preferenceType = "Sweet Tooth";
    savePreference(userId, preferenceType, preferenceValue);
}

bool Employee::isProfileCreated(int userId)
{
    std::string request = "isProfileCreated:" + std::to_string(userId);
    sendRequest(request);
    std::string response = receiveResponse();
    std::cout << "Server response:" << std::endl;
    return response == "true";
}

bool Employee::savePreference(int userId, const std::string &preferenceType, const std::string &preferenceValue)
{
    std::string request = "savePreference:" + std::to_string(userId) + ":" + preferenceType + ":" + preferenceValue;
    sendRequest(request);
    std::string response = receiveResponse();
    return response == "Preference saved successfully";
}

std::string Employee::fetchEmployeePreferences(int employeeId)
{
    std::string request = "fetchEmployeePreferences:" + std::to_string(employeeId);
    sendRequest(request);
    std::string response = receiveResponse();
    return response.empty() ? "No preferences found" : response;
}

int Employee::countPreferenceMatches(const std::vector<std::pair<std::string, std::string>> &preferences, const FoodItem *foodItem)
{
    int matchCount = 0;
    for (const auto &preference : preferences)
    {
        if ((preference.first == "Diet" && preference.second == foodItem->getType() ||
            (preference.first == "Spice Level" && preference.second == foodItem->getSpiceLevel()) ||
            (preference.first == "Cuisine" && preference.second == foodItem->getCuisine())))
        {
            ++matchCount;
        }
    }
    return matchCount;
}

std::vector<std::string> Employee::recommendFoodItems(int employeeId, const std::vector<std::string> &availableFoodItems)
{
    std::string preferenceString = fetchEmployeePreferences(employeeId);
    std::vector<std::pair<std::string, std::string>> preferences = parsePreferences(preferenceString);
    std::vector<std::pair<std::string, int>> foodItemMatches;

    for (const auto &availableFoodItem : availableFoodItems)
    {
        foodItem = getFoodItemDetails(availableFoodItem);
        int matchCount = countPreferenceMatches(preferences, foodItem);
        foodItemMatches.push_back({availableFoodItem, matchCount});
    }
    
    for (size_t i = 0; i < foodItemMatches.size() - 1; ++i)
    {
        for (size_t j = 0; j < foodItemMatches.size() - i - 1; ++j)
        {
            if (foodItemMatches[j].second < foodItemMatches[j + 1].second)
            {
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

FoodItem *Employee::getFoodItemDetails(std::string foodItemName)
{
    std::string request = "getFoodItemDetails:" + foodItemName;
    sendRequest(request);
    std::string response = receiveResponse();
    parseFoodItemDetailString(response);
    return parseFoodItemDetailString(response);
}

FoodItem *Employee::parseFoodItemDetailString(std::string foodItemDetailString)
{
    std::istringstream stream(foodItemDetailString);
    std::string line;
    std::vector<std::string> fields;

    while (std::getline(stream, line, ':'))
    {
        fields.push_back(line);
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
    return foodItem;
}
