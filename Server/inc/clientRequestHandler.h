#ifndef CLIENTREQUESTHANDLER_H
#define CLIENTREQUESTHANDLER_H

#include <string>
#include <WinSock2.h>
#include "AdminDatabaseManager.h"
#include "EmployeeDatabaseManager.h"
#include "ChefDatabaseManager.h"

class ClientRequestHandler
{
private:
    AdminDatabaseManager &adminDbManager;
    EmployeeDatabaseManager &employeeDbManager;
    ChefDatabaseManager &chefDbManager;
    int userID;
    void sendResponse(const SOCKET clientSocket, const std::string &response);
    void handleShowAllMenuItems(const SOCKET clientSocket);
    void handleGetID(const std::string &request, const SOCKET clientSocket, const int id);
    void handleAddMenuItem(const std::string &request, const SOCKET clientSocket);
    void handleDeleteMenuItem(const std::string &request, const SOCKET clientSocket);
    void handleUpdateMenuItem(const std::string &request, const SOCKET clientSocket);
    void handleGetAllFeedbacks(const SOCKET clientSocket);
    void handleViewNotifications(const SOCKET clientSocket);
    void handleProvideFeedback(const std::string &request, const SOCKET clientSocket, const int id);
    void handleSubmitVote(const std::string &request, const SOCKET clientSocket);
    void handleGetFoodItemId(const std::string &request, const SOCKET clientSocket);
    void handleGetMenuItemName(const std::string &request, const SOCKET clientSocket);
    void handleGetVotesForFoodItem(const std::string &request, const SOCKET clientSocket);
    void handleIsProfileCreated(const std::string &request, const SOCKET clientSocket);
    void handleSavePreference(const std::string &request, const SOCKET clientSocket);
    void handleFetchEmployeePreferences(const std::string &request, const SOCKET clientSocket);
    void handleRolledOutFoodItems(const std::string &request, const SOCKET clientSocket, int userID);
    void handleGetFoodItemDetails(const std::string &request, const SOCKET clientSocket);
    void handleUpdateDiscardMenuItemList(const std::string &request, const SOCKET clientSocket);
public:
    ClientRequestHandler(AdminDatabaseManager &adminDbManager, EmployeeDatabaseManager &employeeDbManager, ChefDatabaseManager &chefDbManager);
    void processRequest(const std::string &request, const SOCKET clientSocket, const int id);
};

#endif // CLIENTREQUESTHANDLER_H
