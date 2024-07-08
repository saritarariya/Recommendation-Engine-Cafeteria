
#include "Chef.h"

std::vector<int> Chef::getFoodItemsToRollOut()
{
    std::vector<int> topFoodItems;
    RecommendationEngine engine;
    std::string request = "getAllFeedbacks:";
    sendRequest(request);
    std::string response = receiveResponse();
    engine.parseAndAddFeedbacks(response);
    topFoodItems = engine.getTopFoodItems();
    std::cout << "Top 5 Recommended Food Items:" << std::endl;
    for (size_t i = 0; i < topFoodItems.size() && i < 5; ++i)
    {
        std::cout << i + 1 << ". " << topFoodItems[i] << std::endl;
    }
    return topFoodItems;
}

void Chef::chooseFoodItemsForNextDay()
{
    std::vector<int> topFoodItemsIDs = getFoodItemsToRollOut();
    std::vector<std::string> topFoodItems;
    for (const auto& id : topFoodItemsIDs) {
        topFoodItems.push_back(getMenuItemName(id));
    }

    std::vector<std::string> chosenItems;

    while (chosenItems.size() < 5)
    {
        std::cout << "Choose Food Items to Roll out for Next Day:" << std::endl;
        std::cout << "1. Choose from Top 5 Recommended Food Items" << std::endl;
        std::cout << "2. View all Menu Items" << std::endl;
        std::cout << "3. View Chosen Items" << std::endl;
        std::cout << "Enter your choice: ";
        int choice;
        std::cin >> choice;

        if (choice == 1)
        {
            for (size_t i = 0; i < topFoodItems.size() && i < 5; ++i)
            {
                std::cout << i + 1 << ". " << topFoodItems[i] << std::endl;
            }
            int itemChoice;
            std::cout << "Enter the number of the food item to choose (1-5): ";
            std::cin >> itemChoice;
            if (itemChoice >= 1 && itemChoice <= 5)
            {
                chosenItems.push_back(topFoodItems[itemChoice - 1]);
            }
        }
        else if (choice == 2)
        {
            std::cout << "this logic will implemented later\n";
        }
        std::cout << "You have chosen " << chosenItems.size() << " items out of 5." << std::endl;
    }

    std::cout << "Final Chosen Food Items for Next Day:" << std::endl;
    for (const auto &item : chosenItems)
    {
        std::cout << item << std::endl;
    }

    std::ostringstream oss;
    for (size_t i = 0; i < chosenItems.size(); ++i)
    {
        if (i != 0)
            oss << ",";
        oss << chosenItems[i];
    }
    std::string chosenItemsStr = oss.str();

    std::string request = "Rolled out food items:";
    request = request + chosenItemsStr;
    sendRequest(request);
    std::string response = receiveResponse();
    std::cout << "Server response:" << std::endl;
    std::cout << response << std::endl;
}

void Chef::viewNotifications()
{
    std::string request = "viewNotifications:";
    sendRequest(request);
    std::string response = receiveResponse();
    std::cout << "Server response:" << std::endl;
    std::cout << response << std::endl;
}

void Chef::viewVotes()
{
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
            std::cout << "Rolled out food items: " << notification.substr(21) << std::endl;

            std::istringstream itemStream(notification.substr(21));
            std::string foodItem;
            std::vector<std::string> foodItems;

            while (std::getline(itemStream, foodItem, ','))
            {
                foodItems.push_back(foodItem);
            }

            for (const auto &item : foodItems)
            {
                std::string request = "getFoodItemId:" + item;
                sendRequest(request);
                std::string foodItemIdStr = receiveResponse();
                int foodItemId = std::stoi(foodItemIdStr);

                request = "getVotesForFoodItem:" + std::to_string(foodItemId);
                sendRequest(request);
                std::string votesStr = receiveResponse();
                int votes = std::stoi(votesStr);

                std::cout << "Food Item: " << item << " - Votes: " << votes << std::endl;
            }
        }
    }
}

void Chef::performRoleFunctions()
{
    int choice;
    do
    {
        std::cout << "Please choose an operation:" << std::endl;
        std::cout << "1. Choose Food Items to Roll out for Next Day" << std::endl;
        std::cout << "2. Get top five food from recommendation engine." << std::endl;
        std::cout << "3. View all menu items" << std::endl;
        std::cout << "4. View votes on food Items." << std::endl;
        std::cout << "5. View Notifications" << std::endl;
        std::cout << "6. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

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
            std::cout << "Exiting..." << std::endl;
            break;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
            break;
        }
    } while (choice != 6);
}

void Chef::viewAllMenuItems()
{
    std::string request = "showAllMenuItems";
    sendRequest(request);
    std::string response = receiveResponse();
    std::cout << "Server response:" << std::endl;
    std::cout << response << std::endl;
}

std::string Chef::getMenuItemName(const int &foodItemId) {
    std::string request = "getMenuItemName:" + std::to_string(foodItemId);
    sendRequest(request);
    std::string response = receiveResponse();
    return response;
}
