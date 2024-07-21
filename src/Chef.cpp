#include "Chef.h"

std::vector<std::string> Chef::getFoodItemsToRollOut()
{
    std::vector<int> topFoodItemIds;
    RecommendationEngine engine;
    std::string request = "getAllFeedbacks:";
    sendRequest(request);
    std::string response = receiveResponse();

    if (response.empty())
    {
        std::cerr << "Failed to retrieve feedbacks. Please try again later." << std::endl;
        return {};
    }

    engine.parseAndAddFeedbacks(response);
    topFoodItemIds = engine.getTopFoodItems();

    std::vector<std::string> topFoodItems;
    for (const auto &id : topFoodItemIds)
    {
        topFoodItems.push_back(getMenuItemName(id));
    }

    displayTopFoodItems(topFoodItems);
    return topFoodItems;
}

void Chef::displayTopFoodItems(const std::vector<std::string> &topFoodItems)
{
    std::cout << "Top 5 Recommended Food Items:" << std::endl;
    for (size_t i = 0; i < topFoodItems.size() && i < 5; ++i)
    {
        std::cout << i + 1 << ". " << topFoodItems[i] << std::endl;
    }
}

void Chef::chooseFoodItemsForNextDay()
{
    std::vector<std::string> topFoodItems = getFoodItemsToRollOut();
    std::vector<std::string> chosenItems;

    while (chosenItems.size() < 5)
    {
        displayFoodItemOptions();
        std::string prompt = "Enter your choice:";
        std::string errorMessage = "Invalid choice. Please try again.";
        int choice = getValidatedNumericInput(prompt, errorMessage, 4);
        if (choice == 1)
        {
            chosenItems = chooseFromTopRecommended(topFoodItems, chosenItems);
        }
        if (choice == 2)
        {
            viewAllMenuItems();
        }
        if (choice == 3)
        {
            displayChosenItems(chosenItems);
        }
        std::cout << "You have chosen " << chosenItems.size() << " items out of 5." << std::endl;
    }
    finalizeChosenItems(chosenItems);
}

void Chef::displayFoodItemOptions()
{
    std::cout << "Choose Food Items to Roll out for Next Day:" << std::endl;
    std::cout << "1. Choose from Top 5 Recommended Food Items" << std::endl;
    std::cout << "2. View all Menu Items" << std::endl;
    std::cout << "3. View Chosen Items" << std::endl;
}

int Chef::getValidatedNumericInput(const std::string &prompt, const std::string &errorMessage, int range)
{
    std::string input;
    while (true)
    {
        std::cout << prompt;
        std::getline(std::cin, input);
        if (!input.empty() && std::all_of(input.begin(), input.end(), ::isdigit))
        {
            int choice = stoi(input);
            if (choice < range && choice > 0)
            {
                return choice;
            }
        }
        std::cout << errorMessage << std::endl;
    }
}

std::vector<std::string> Chef::chooseFromTopRecommended(const std::vector<std::string> &topFoodItems, std::vector<std::string> chosenItems)
{
    displayTopFoodItems(topFoodItems);
    std::string prompt = "Enter the number of the food item to choose (1-5): ";
    std::string errorMessage = "Invalid choice. Please select a number between 1 and 5.";
    int itemChoice = getValidatedNumericInput(prompt, errorMessage, 6);
    chosenItems.push_back(topFoodItems[itemChoice - 1]);
    return chosenItems;
}

void Chef::displayChosenItems(const std::vector<std::string> &chosenItems)
{
    std::cout << "Chosen Items:" << std::endl;
    for (const auto &item : chosenItems)
    {
        std::cout << item << std::endl;
    }
}

void Chef::finalizeChosenItems(const std::vector<std::string> &chosenItems)
{
    std::cout << "Final Chosen Food Items for Next Day:" << std::endl;
    for (const auto &item : chosenItems)
    {
        std::cout << item << std::endl;
    }
    std::ostringstream oss;
    for (size_t i = 0; i < chosenItems.size(); ++i)
    {
        if (i != 0)
        {
            oss << ",";
        }
        oss << chosenItems[i];
    }
    std::string chosenItemsStr = oss.str();
    std::string request = "Rolled out food items:" + chosenItemsStr;
    sendRequest(request);

    std::string response = receiveResponse();
    if (response.empty())
    {
        std::cerr << "Failed to roll out food items. Please try again later." << std::endl;
    }
    else
    {
        std::cout << "Server response:" << response << std::endl;
    }
}

void Chef::viewNotifications()
{
    std::string request = "viewNotifications:";
    sendRequest(request);
    std::string response = receiveResponse();

    if (response.empty())
    {
        std::cerr << "Failed to retrieve notifications. Please try again later." << std::endl;
    }
    else
    {
        std::cout << "Server response:" << response << std::endl;
    }
}

void Chef::viewVotes()
{
    std::string request = "viewNotifications:";
    sendRequest(request);
    std::string response = receiveResponse();

    if (response.empty())
    {
        std::cerr << "Failed to retrieve votes. Please try again later." << std::endl;
        return;
    }

    std::vector<std::string> notifications = parseResponseToList(response);

    for (const auto &notification : notifications)
    {
        if (notification.find("Rolled out food items:") != std::string::npos)
        {
            processRolledOutItems(notification.substr(22));
        }
    }
}

std::vector<std::string> Chef::parseResponseToList(const std::string &response)
{
    std::vector<std::string> list;
    std::istringstream iss(response);
    std::string line;
    while (std::getline(iss, line))
    {
        list.push_back(line);
    }
    return list;
}

void Chef::processRolledOutItems(const std::string &items)
{
    std::istringstream itemStream(items);
    std::string foodItem;
    std::vector<std::string> foodItems;

    while (std::getline(itemStream, foodItem, ','))
    {
        foodItems.push_back(foodItem);
    }

    for (const auto &item : foodItems)
    {
        int foodItemId = getFoodItemId(item);
        int votes = getVotesForFoodItem(foodItemId);
        std::cout << "Food Item: " << item << " - Votes: " << votes << std::endl;
    }
}

int Chef::getFoodItemId(const std::string &item)
{
    std::string request = "getFoodItemId:" + item;
    sendRequest(request);
    std::string response = receiveResponse();

    if (response.empty())
    {
        std::cerr << "Failed to retrieve Food Item ID for " << item << ". Please try again later." << std::endl;
        return -1;
    }

    return std::stoi(response);
}

int Chef::getVotesForFoodItem(int foodItemId)
{
    std::string request = "getVotesForFoodItem:" + std::to_string(foodItemId);
    sendRequest(request);
    std::string response = receiveResponse();

    if (response.empty())
    {
        std::cerr << "Failed to retrieve votes for Food Item ID " << foodItemId << ". Please try again later." << std::endl;
        return -1;
    }

    return std::stoi(response);
}

void Chef::performRoleFunctions()
{
    while (true)
    {
        displayMainMenu();
        std::string prompt = "Enter your choice :";
        std::string errorMessage = "Invalid choice. Please try again.";
        int choice = getValidatedNumericInput(prompt, errorMessage, 8);
        switch (choice)
        {
        case 1:
            chooseFoodItemsForNextDay();
            break;
        case 2:
            getFoodItemsToRollOut();
            break;
        case 3:
            viewAllMenuItems();
            break;
        case 4:
            viewVotes();
            break;
        case 5:
            viewNotifications();
            break;
        case 6:
            viewDiscardMenuItemList();
            break;
        case 7:
            std::cout << "Exiting..." << std::endl;
            return;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }
}

void Chef::displayMainMenu()
{
    std::cout << "Please choose an operation:" << std::endl;
    std::cout << "1. Choose Food Items to Roll out for Next Day" << std::endl;
    std::cout << "2. Get top five food from recommendation engine." << std::endl;
    std::cout << "3. View all menu items" << std::endl;
    std::cout << "4. View votes on food Items." << std::endl;
    std::cout << "5. View Notifications" << std::endl;
    std::cout << "6. View Discard MenuItem List" << std::endl;
    std::cout << "7. Exit" << std::endl;
}

void Chef::viewAllMenuItems()
{
    std::string request = "showAllMenuItems";
    sendRequest(request);
    std::string response = receiveResponse();
    if (response.empty())
    {
        std::cerr << "Failed to retrieve menu items. Please try again later." << std::endl;
    }
    else
    {
        std::cout << "Server response:" << response << std::endl;
    }
}

std::string Chef::getMenuItemName(const int &foodItemId)
{
    std::string request = "getMenuItemName:" + std::to_string(foodItemId);
    sendRequest(request);
    std::string response = receiveResponse();

    if (response.empty())
    {
        std::cerr << "Failed to retrieve menu item name for ID " << foodItemId << ". Please try again later." << std::endl;
        return "";
    }

    return response;
}

void Chef::viewDiscardMenuItemList()
{
    RecommendationEngine engine;
    std::string requestFeedback = "getAllFeedbacks:";
    sendRequest(requestFeedback);
    std::string responseFeedbacks = receiveResponse();

    if (responseFeedbacks.empty())
    {
        std::cerr << "Failed to retrieve feedbacks. Please try again later." << std::endl;
        return;
    }

    engine.parseAndAddFeedbacks(responseFeedbacks);
    std::vector<int> discardMenuItemList = engine.getItemsToDiscard();
    std::string requestDiscardMenuItemList = "UpdateDiscardMenuItemList:";
    displayDiscardMenuItems(discardMenuItemList, requestDiscardMenuItemList);
    sendRequest(requestDiscardMenuItemList);

    std::string DiscardMenuItemListResponse = receiveResponse();
    if (DiscardMenuItemListResponse.empty())
    {
        std::cerr << "Failed to update discard menu item list. Please try again later." << std::endl;
        return;
    }

    std::cout << DiscardMenuItemListResponse << std::endl;
    handleDiscardMenuItemActions();
}

void Chef::displayDiscardMenuItems(const std::vector<int> &discardMenuItemList, std::string &request)
{
    std::cout << "Discard Menu Item List:" << std::endl;
    for (size_t i = 0; i < discardMenuItemList.size(); ++i)
    {
        request += std::to_string(discardMenuItemList[i]) + ",";
        std::cout << i + 1 << ". " << getMenuItemName(discardMenuItemList[i]) << std::endl;
    }
}

void Chef::handleDiscardMenuItemActions()
{
    std::cout << "1. Remove the Food Item from Menu List:" << std::endl;
    std::cout << "2. Get Detailed Feedback:" << std::endl;
    std::string prompt = "Enter your choice :";
    std::string errorMessage = "Invalid choice. Please try again.";
    int choice = getValidatedNumericInput(prompt, errorMessage, 3);
    if (choice == 1)
    {
        deleteMenuItem();
    }
    else if (choice == 2)
    {
        getDetailedFeedback();
    }
}

void Chef::deleteMenuItem()
{
    std::string name;
    while (true)
    {
        std::cout << "Enter the name of the menu item to delete: ";
        std::getline(std::cin, name);
        if (!name.empty())
        {
            break;
        }
        std::cout << "Menu Item name can not be empty.";
        std::cin.ignore(1, '/n');
    }

    std::string request = "deleteMenuItem:" + name;
    sendRequest(request);
    std::string response = receiveResponse();

    if (response == "Menu item deleted successfully")
    {
        std::cout << "Menu item '" << name << "' deleted successfully!" << std::endl;
    }
    else
    {
        std::cerr << "Failed to delete menu item '" << name << "'. Please try again." << std::endl;
    }
}

void Chef::getDetailedFeedback()
{
    std::string name;
    while (true)
    {
        std::cout << "Enter the name of the menu item to get detailed feedback: ";
        std::getline(std::cin, name);
        if (!name.empty())
        {
            break;
        }
        std::cout << "Menu Item name can not be empty.";
        std::cin.ignore(1, '/n');
    }
    std::string request = "GetDetailedFeedback:" + name;
    sendRequest(request);
    std::string response = receiveResponse();
    if (response.empty())
    {
        std::cerr << "Failed to retrieve detailed feedback for " << name << ". Please try again later." << std::endl;
    }
    else
    {
        std::cout << response << std::endl;
    }
}
