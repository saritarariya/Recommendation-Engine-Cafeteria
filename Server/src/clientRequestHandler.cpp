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
        else if (request.substr(0, 10) == "loginUser:")
        {
            std::string email = request.substr(10);
            bool loginSuccess = dbManager.loginUser(email);
            std::string response = loginSuccess ? "Login successful" : "Login failed";
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
        else
        {
            std::string response = "Unknown request";
            send(clientSocket, response.c_str(), response.size(), 0);
        }
    }
}

