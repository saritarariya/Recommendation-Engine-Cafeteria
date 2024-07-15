#ifndef EMPLOYEE_DATABASEMANAGER_H
#define EMPLOYEE_DATABASEMANAGER_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <memory>
#include <iomanip>
#include "DatabaseConnection.h"

using namespace sql;

class EmployeeDatabaseManager
{
private:
    DatabaseConnection *dbConnection;

public:
    EmployeeDatabaseManager(DatabaseConnection *connection);
    bool sendFeedback(int userID, int foodItemID, int rating, const string &comments);
    std::vector<std::string> getNotifications();
    bool storeFeedback(int userId, int foodItemId, int rating, const std::string &comment);
    bool storeVote(int userId, int foodItemId);
    int getFoodItemId(const std::string &foodItem);
    std::string getMenuItemName(int foodItemId);
    bool isProfileCreated(int userId);
    bool savePreference(int userId, const std::string& preferenceType, const std::string& preferenceValue);
    std::string fetchEmployeePreferences(int employeeId);
    std::string showFoodItemDetails(const std::string& foodItemName);
    bool connect();
};

#endif // EMPLOYEE_DATABASEMANAGER_H
