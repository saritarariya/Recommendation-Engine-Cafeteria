#ifndef HEADER_H_CHEF
#define HEADER_H_CHEF

#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <iostream>
#include <limits>
#include <cctype>
#include <algorithm>
#include <vector>
#include "User.h"
#include "Client.h"
#include "RecommendationEngine.h"

class Chef : public User
{
private:
    std::vector<std::string> getFoodItemsToRollOut();
    void chooseFoodItemsForNextDay();
    void viewVotes();
    void viewNotifications();
    void viewAllMenuItems();
    std::string getMenuItemName(const int &foodItemId);
    void viewDiscardMenuItemList();
    void displayTopFoodItems(const std::vector<std::string> &topFoodItems);
    void displayFoodItemOptions();
    std::vector<std::string> chooseFromTopRecommended(const std::vector<std::string> &topFoodItems, std::vector<std::string> chosenItems);
    void displayChosenItems(const std::vector<std::string> &chosenItems);
    void finalizeChosenItems(const std::vector<std::string> &chosenItems);
    std::vector<std::string> parseResponseToList(const std::string &response);
    void processRolledOutItems(const std::string &items);
    int getFoodItemId(const std::string &item);
    int getVotesForFoodItem(int foodItemId);
    void displayMainMenu();
    void displayDiscardMenuItems(const std::vector<int> &discardMenuItemList, std::string &request);
    void handleDiscardMenuItemActions();
    void deleteMenuItem();
    void getDetailedFeedback();
    int getValidatedNumericInput(const std::string &prompt, const std::string &errorMessage, int range);

public:
    Chef(Client *client) : User(client) {}
    void performRoleFunctions();
};
#endif