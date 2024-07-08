#include "clientRequestHandler.h"

ClientRequestHandler::ClientRequestHandler(DatabaseManager &dbManager) : dbManager(dbManager) {}

void ClientRequestHandler::processRequest(const std::string &request, const SOCKET clientSocket, const int id)
{
    if (dbManager.connect())
    {

        if (request == "showAllMenuItems")
        {
            std::string response = dbManager.showAllMenuItems();
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
        else if (request.substr(0, 6) == "getID:")
        {
            std::string response = std::to_string(id);
            send(clientSocket, response.c_str(), response.size(), 0);
        }
        else if (request.substr(0, 12) == "addMenuItem:")
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

            bool availability = std::stoi(remaining);

            bool success = dbManager.addMenuItem(name, description, price, category, availability);

            std::string response = success ? "Menu item added successfully" : "Failed to add menu item";
            send(clientSocket, response.c_str(), response.size(), 0);
        }

        else if (request.substr(0, 15) == "deleteMenuItem:")
        {
            std::string name = request.substr(15);
            bool success = dbManager.deleteMenuItem(name);
            std::string response = success ? "Menu item deleted successfully" : "Failed to delete menu item";
            send(clientSocket, response.c_str(), response.size(), 0);
        }
        else if (request.substr(0, 15) == "updateMenuItem:")
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

            bool availability = std::stoi(remaining);

            bool success = dbManager.updateMenuItem(name, price, availability);

            std::string response = success ? "Menu item updated successfully" : "Failed to update menu item";
            send(clientSocket, response.c_str(), response.size(), 0);
        }
        else if (request == "getAllFeedbacks:")
        {
            std::vector<std::tuple<int, int, int, int, std::string, std::string>> feedbacks = dbManager.getAllFeedbacks();

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
        else if (request.substr(0, 23) == "Rolled out food items:")
        {
            std::string rolledOutItems = request.substr(23);
            std::istringstream iss(rolledOutItems);
            std::vector<std::string> foodItems;
            std::string item;

            while (std::getline(iss, item, ','))
            {
                foodItems.push_back(item);
            }

            bool success = dbManager.storeRolledOutFoodItems(foodItems, id);

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
        else if (request == "viewNotifications:")
        {
            dbManager.connect();
            std::vector<std::string> notifications = dbManager.getNotifications();

            std::string response;
            for (const auto &notification : notifications)
            {
                response += notification + "\n";
            }

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
        else if (request.substr(0, 15) == "provideFeedback:")
        {
            std::string feedbackData = request.substr(15);
            std::istringstream iss(feedbackData);
            std::string token;

            std::vector<std::string> tokens;
            while (std::getline(iss, token, ','))
            {
                tokens.push_back(token);
            }
            if (tokens.size() == 4)
            {
                int foodItemId = std::stoi(tokens[0]);
                int rating = std::stoi(tokens[1]);
                std::string comment = tokens[2];

                bool feedbackSuccess = dbManager.storeFeedback(id, foodItemId, rating, comment);
                std::string response = feedbackSuccess ? "Feedback stored successfully" : "Failed to store feedback";

                send(clientSocket, response.c_str(), response.size(), 0);
            }
            else
            {
                std::string response = "Invalid feedback data";
                send(clientSocket, response.c_str(), response.size(), 0);
            }
        }
        else if (request.substr(0, 10) == "submitVote:")
        {
            std::string voteData = request.substr(10);
            std::istringstream iss(voteData);
            std::string token;

            std::vector<std::string> tokens;
            while (std::getline(iss, token, ','))
            {
                tokens.push_back(token);
            }

            if (tokens.size() == 3)
            {
                int userId = std::stoi(tokens[0]);
                int foodItemId = std::stoi(tokens[1]);
                int voteCount = std::stoi(tokens[2]);

                dbManager.connect();
                bool voteSuccess = dbManager.storeVote(userId, foodItemId, voteCount);
                std::string response = voteSuccess ? "Vote stored successfully" : "Failed to store vote";

                send(clientSocket, response.c_str(), response.size(), 0);
            }
            else
            {
                std::string response = "Invalid vote data";
                send(clientSocket, response.c_str(), response.size(), 0);
            }
        }
        else if (request.substr(0, 17) == "getFoodItemId:")
        {
            std::string foodItem = request.substr(17);
            int foodItemId = dbManager.getFoodItemId(foodItem);
            std::string response = std::to_string(foodItemId);
            send(clientSocket, response.c_str(), response.size(), 0);
        }
        else if (request.substr(0, 21) == "getVotesForFoodItem:")
        {
            int foodItemId = std::stoi(request.substr(21));
            int votes = dbManager.getVotesForFoodItem(foodItemId);
            std::string response = std::to_string(votes);
            send(clientSocket, response.c_str(), response.size(), 0);
        }
        else
        {
            std::string response = "Unknown request";
            send(clientSocket, response.c_str(), response.size(), 0);
        }
    }
}
