#include "clientRequestHandler.h"

ClientRequestHandler::ClientRequestHandler(DatabaseManager &dbManager) : dbManager(dbManager) {}

void ClientRequestHandler::processRequest(const std::string &request, const SOCKET clientSocket, const int id)
{
    if (dbManager.connect())
    {
        std::cout << "Is control reached here 1\n";
        if (request == "showAllMenuItems")
        {
            std::cout << "Is control reached here 2\n";
            std::string response = dbManager.showAllMenuItems(); // Implement this method to return all menu items as a string
            send(clientSocket, response.c_str(), response.size(), 0);
        }
        else if (request.substr(0, 10) == "loginUser:")
        {
            std::string email = request.substr(10);
            bool loginSuccess = dbManager.loginUser(email);
            std::string response = loginSuccess ? "Login successful" : "Login failed";
            send(clientSocket, response.c_str(), response.size(), 0);
        }
        else if (request.substr(0, 13) == "addMenuItem:")
        {
            std::string remaining = request.substr(13);

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
            std::string name = request.substr(15); // Extract the name from the request string
            bool success = dbManager.deleteMenuItem(name);
            std::string response = success ? "Menu item deleted successfully" : "Failed to delete menu item";
            send(clientSocket, response.c_str(), response.size(), 0);
        }
        else if (request.substr(0, 16) == "updateMenuItem:")
        {
            std::string remaining = request.substr(16);
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

std::string ClientRequestHandler::receiveEmail(const SOCKET clientSocket)
{
    char buffer[100];
    int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
    buffer[bytesReceived] = '\0';
    return std::string(buffer);
}

std::string ClientRequestHandler::receiveString(const SOCKET clientSocket)
{
    char buffer[256];
    int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
    buffer[bytesReceived] = '\0';
    return std::string(buffer);
}

double ClientRequestHandler::receiveDouble(const SOCKET clientSocket)
{
    char buffer[64];
    int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
    buffer[bytesReceived] = '\0';
    return std::stod(buffer);
}

bool ClientRequestHandler::receiveBool(const SOCKET clientSocket)
{
    char buffer[5];
    int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
    buffer[bytesReceived] = '\0';
    return (std::string(buffer) == "true");
}
