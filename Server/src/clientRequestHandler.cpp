#include "ClientRequestHandler.h"

ClientRequestHandler::ClientRequestHandler(AdminDatabaseManager &adminDbManager, EmployeeDatabaseManager &employeeDbManager, ChefDatabaseManager &chefDbManager)
    : adminDbManager(adminDbManager), employeeDbManager(employeeDbManager), chefDbManager(chefDbManager) {}

void ClientRequestHandler::processRequest(const std::string &request, const SOCKET clientSocket, const int id)
{
    this->userID = id;
    if (adminDbManager.connect() || employeeDbManager.connect() || chefDbManager.connect())
    {
        if (request == "showAllMenuItems")
        {
            handleShowAllMenuItems(clientSocket);
        }
        else if (request.substr(0, 6) == "getID:")
        {
            handleGetID(request, clientSocket, id);
        }
        else if (request.substr(0, 12) == "addMenuItem:")
        {
            handleAddMenuItem(request, clientSocket);
        }
        else if (request.substr(0, 15) == "deleteMenuItem:")
        {
            handleDeleteMenuItem(request, clientSocket);
        }
        else if (request.substr(0, 15) == "updateMenuItem:")
        {
            handleUpdateMenuItem(request, clientSocket);
        }
        else if (request == "getAllFeedbacks:")
        {
            handleGetAllFeedbacks(clientSocket);
        }
        else if (request == "viewNotifications:")
        {
            handleViewNotifications(clientSocket);
        }
        else if (request.substr(0, 16) == "provideFeedback:")
        {
            handleProvideFeedback(request, clientSocket, id);
        }
        else if (request.substr(0, 11) == "submitVote:")
        {
            handleSubmitVote(request, clientSocket);
        }
        else if (request.substr(0, 14) == "getFoodItemId:")
        {
            handleGetFoodItemId(request, clientSocket);
        }
        else if (request.substr(0, 16) == "getMenuItemName:")
        {
            handleGetMenuItemName(request, clientSocket);
        }
        else if (request.substr(0, 20) == "getVotesForFoodItem:")
        {
            handleGetVotesForFoodItem(request, clientSocket);
        }
        else if (request.find("isProfileCreated:") == 0)
        {
            handleIsProfileCreated(request, clientSocket);
        }
        else if (request.find("savePreference:") == 0)
        {
            handleSavePreference(request, clientSocket);
        }
        else if (request.find("fetchEmployeePreferences:") == 0)
        {
            handleFetchEmployeePreferences(request, clientSocket);
        }
        else if (request.substr(0, 22) == "Rolled out food items:")
        {
            handleRolledOutFoodItems(request, clientSocket, id);
        }
        else if (request.substr(0, 19) == "getFoodItemDetails:")
        {
            handleGetFoodItemDetails(request, clientSocket);
        }
        else
        {
            std::string response = "Unknown request";
            sendResponse(clientSocket, response);
        }
    }
}

void ClientRequestHandler::sendResponse(const SOCKET clientSocket, const std::string &response)
{
    int bytesSent = send(clientSocket, response.c_str(), response.size(), 0);
    if (bytesSent == SOCKET_ERROR)
    {
        std::cerr << "Failed to send response to client. Error code: " << WSAGetLastError() << std::endl;
    }
    else
    {
        std::cout << "Response sent successfully. Bytes sent: " << bytesSent << std::endl;
    }
}

void ClientRequestHandler::handleShowAllMenuItems(const SOCKET clientSocket)
{
    std::string response = adminDbManager.showAllMenuItems();
    sendResponse(clientSocket, response);
}

void ClientRequestHandler::handleGetID(const std::string &request, const SOCKET clientSocket, const int id)
{
    std::cout << id << std::endl;
    std::string response = std::to_string(id) + '\0';
    sendResponse(clientSocket, response);
}

void ClientRequestHandler::handleAddMenuItem(const std::string &request, const SOCKET clientSocket)
{
    std::string remaining = request.substr(12);
    size_t pos = 0;
    std::string delimiter = "\n";

    pos = remaining.find(delimiter);
    std::string name = remaining.substr(0, pos);
    remaining.erase(0, pos + delimiter.length());

    pos = remaining.find(delimiter);
    std::string description = remaining.substr(0, pos);
    remaining.erase(0, pos + delimiter.length());

    pos = remaining.find(delimiter);
    double price = std::stod(remaining.substr(0, pos));
    remaining.erase(0, pos + delimiter.length());

    pos = remaining.find(delimiter);
    std::string category = remaining.substr(0, pos);
    remaining.erase(0, pos + delimiter.length());

    pos = remaining.find(delimiter);
    bool availability = std::stoi(remaining.substr(0, pos));
    remaining.erase(0, pos + delimiter.length());

    pos = remaining.find(delimiter);
    std::string type = remaining.substr(0, pos);
    remaining.erase(0, pos + delimiter.length());

    pos = remaining.find(delimiter);
    std::string spiceLevel = remaining.substr(0, pos);
    remaining.erase(0, pos + delimiter.length());

    pos = remaining.find(delimiter);
    std::string cuisine = remaining.substr(0, pos);
    remaining.erase(0, pos + delimiter.length());

    bool isSweet = std::stoi(remaining);

    bool success = adminDbManager.addMenuItem(name, description, price, category, availability, type, spiceLevel, cuisine, isSweet);

    std::string response = success ? "Menu item added successfully" : "Failed to add menu item";
    sendResponse(clientSocket, response);
}

void ClientRequestHandler::handleDeleteMenuItem(const std::string &request, const SOCKET clientSocket)
{
    std::string name = request.substr(15);
    bool success = adminDbManager.deleteMenuItem(name);
    std::string response = success ? "Menu item deleted successfully" : "Failed to delete menu item";
    sendResponse(clientSocket, response);
}

void ClientRequestHandler::handleUpdateMenuItem(const std::string &request, const SOCKET clientSocket)
{
    std::string remaining = request.substr(15);
    size_t pos = 0;
    std::string delimiter = "\n";

    pos = remaining.find(delimiter);
    std::string name = remaining.substr(0, pos);
    remaining.erase(0, pos + delimiter.length());

    pos = remaining.find(delimiter);
    double price = std::stod(remaining.substr(0, pos));
    remaining.erase(0, pos + delimiter.length());

    pos = remaining.find(delimiter);
    bool availability = std::stoi(remaining.substr(0, pos));
    remaining.erase(0, pos + delimiter.length());

    pos = remaining.find(delimiter);
    std::string description = remaining.substr(0, pos);
    remaining.erase(0, pos + delimiter.length());

    pos = remaining.find(delimiter);
    std::string category = remaining.substr(0, pos);
    remaining.erase(0, pos + delimiter.length());

    pos = remaining.find(delimiter);
    std::string type = remaining.substr(0, pos);
    remaining.erase(0, pos + delimiter.length());

    pos = remaining.find(delimiter);
    std::string spiceLevel = remaining.substr(0, pos);
    remaining.erase(0, pos + delimiter.length());

    pos = remaining.find(delimiter);
    std::string cuisine = remaining.substr(0, pos);
    remaining.erase(0, pos + delimiter.length());

    bool isSweet = std::stoi(remaining);

    bool success = adminDbManager.updateMenuItem(name, price, availability, description, category, type, spiceLevel, cuisine, isSweet);

    std::string response = success ? "Menu item updated successfully" : "Failed to update menu item";
    sendResponse(clientSocket, response);
}

void ClientRequestHandler::handleGetAllFeedbacks(const SOCKET clientSocket)
{
    std::vector<std::tuple<int, int, int, int, std::string, std::string>> feedbacks = adminDbManager.getAllFeedbacks();

    std::string response;
    for (const auto &feedback : feedbacks)
    {
        response += std::to_string(std::get<0>(feedback)) + "\n";
        response += std::to_string(std::get<1>(feedback)) + "\n";
        response += std::to_string(std::get<2>(feedback)) + "\n";
        response += std::to_string(std::get<3>(feedback)) + "\n";
        response += std::get<4>(feedback) + "\n";
        response += std::get<5>(feedback) + "\n";
    }
    sendResponse(clientSocket, response);
}

void ClientRequestHandler::handleViewNotifications(const SOCKET clientSocket)
{
    std::vector<std::string> notifications = employeeDbManager.getNotifications();

    std::string response = "Notifications:\n";
    for (const auto &notification : notifications)
    {
        response += notification + "\n";
    }

    sendResponse(clientSocket, response);
}

void ClientRequestHandler::handleProvideFeedback(const std::string &request, const SOCKET clientSocket, const int id)
{

    std::string feedbackData = request.substr(16);
    std::istringstream iss(feedbackData);
    std::string token;
    std::vector<std::string> tokens;
    while (std::getline(iss, token, ','))
    {
        tokens.push_back(token);
    }
    if (tokens.size() == 3)
    {
        int foodItemId = std::stoi(tokens[0]);
        int rating = std::stoi(tokens[1]);
        std::string comment = tokens[2];

        bool feedbackSuccess = employeeDbManager.sendFeedback(id, foodItemId, rating, comment);
        std::string response = feedbackSuccess ? "Feedback stored successfully" : "Failed to store feedback";

        send(clientSocket, response.c_str(), response.size(), 0);
    }
    else
    {
        std::string response = "Invalid feedback data";
        send(clientSocket, response.c_str(), response.size(), 0);
    }
}

void ClientRequestHandler::handleSubmitVote(const std::string &request, const SOCKET clientSocket)
{
    std::string voteData = request.substr(11);
    std::istringstream iss(voteData);
    std::string token;

    std::vector<std::string> tokens;
    while (std::getline(iss, token, ','))
    {
        tokens.push_back(token);
    }

    if (tokens.size() == 2)
    {
        int userId = std::stoi(tokens[0]);
        int foodItemId = std::stoi(tokens[1]);

        bool voteSuccess = employeeDbManager.storeVote(userId, foodItemId);
        std::string response = voteSuccess ? "Vote stored successfully" : "Failed to store vote";

        std::cout << "Vote storage result: " << response << std::endl;
        send(clientSocket, response.c_str(), response.size(), 0);
    }
    else
    {
        std::string response = "Invalid vote data";
        std::cout << "Invalid vote data: " << voteData << std::endl;
        send(clientSocket, response.c_str(), response.size(), 0);
    }
}

void ClientRequestHandler::handleGetFoodItemId(const std::string &request, const SOCKET clientSocket)
{
    std::string foodItemName = request.substr(15);
    std::cout << foodItemName << std::endl;
    int foodItemId = employeeDbManager.getFoodItemId(foodItemName);

    std::string response = std::to_string(foodItemId) + "\n";
    sendResponse(clientSocket, response);
}

void ClientRequestHandler::handleGetMenuItemName(const std::string &request, const SOCKET clientSocket)
{
    int foodItemId = std::stoi(request.substr(16));
    std::string menuItemName = employeeDbManager.getMenuItemName(foodItemId);

    sendResponse(clientSocket, menuItemName);
}

void ClientRequestHandler::handleGetVotesForFoodItem(const std::string &request, const SOCKET clientSocket)
{
    int foodItemId = std::stoi(request.substr(20));
    int votes = chefDbManager.getTotalVotesForFoodItem(foodItemId);
    std::string response = std::to_string(votes);
    sendResponse(clientSocket, response);
}

void ClientRequestHandler::handleIsProfileCreated(const std::string &request, const SOCKET clientSocket)
{
    std::string userIdStr = request.substr(17); // Extract userId after "isProfileCreated:"
    int userId = std::stoi(userIdStr);

    bool profileCreated = employeeDbManager.isProfileCreated(userId);
    sendResponse(clientSocket, profileCreated ? "true" : "false");
}

void ClientRequestHandler::handleSavePreference(const std::string &request, const SOCKET clientSocket)
{
    std::istringstream iss(request);
    std::cout << request << std::endl;
    std::string command, userIdStr, preferenceType, preferenceValue;
    std::getline(iss, command, ':');
    std::getline(iss, userIdStr, ':');
    std::getline(iss, preferenceType, ':');
    std::getline(iss, preferenceValue, ':');
    int userId = std::stoi(userIdStr);
    std::cout << "U ID =" << userId << "Preference Type = " << preferenceType << "preferenceValue =" << preferenceValue;
    bool success = employeeDbManager.savePreference(userId, preferenceType, preferenceValue);
    std::string response = success ? "Preference saved successfully" : "Failed to save preference";
    sendResponse(clientSocket, response);
}

void ClientRequestHandler::handleFetchEmployeePreferences(const std::string &request, const SOCKET clientSocket)
{
    std::string userIdStr = request.substr(25);
    int userId = std::stoi(userIdStr);

    std::string preferences = employeeDbManager.fetchEmployeePreferences(userId);
    std::string response = preferences.empty() ? "No preferences found" : preferences;
    sendResponse(clientSocket, response);
}

void ClientRequestHandler::handleRolledOutFoodItems(const std::string &request, const SOCKET clientSocket, int userID)
{
    std::string rolledOutItems = request.substr(22);
    std::istringstream iss(rolledOutItems);
    std::vector<std::string> foodItems;
    std::string item;

    while (std::getline(iss, item, ','))
    {
        foodItems.push_back(item);
    }

    bool success = chefDbManager.storeRolledOutFoodItems(foodItems, userID);
    std::string response = success ? "Rolled out food items stored successfully" : "Failed to store rolled out food items";
    int bytesSent = send(clientSocket, response.c_str(), response.size(), 0);
    if (bytesSent == SOCKET_ERROR)
    {
        std::cerr << "Failed to send response to client. Error code: " << WSAGetLastError() << std::endl;
    }
    else
    {
        std::cout << "Response sent successfully. Bytes sent: " << bytesSent << std::endl;
    }
}

void ClientRequestHandler::handleGetFoodItemDetails(const std::string &request, const SOCKET clientSocket)
{
    std::string foodItemName = request.substr(20);
    std::string response = employeeDbManager.showFoodItemDetails(foodItemName);
    sendResponse(clientSocket, response);
}