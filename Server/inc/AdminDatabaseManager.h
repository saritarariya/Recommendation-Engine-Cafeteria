#ifndef ADMIN_DATABASEMANAGER_H
#define ADMIN_DATABASEMANAGER_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <memory>
#include <iomanip>
#include "DatabaseConnection.h"

using namespace std;
using namespace sql;

class AdminDatabaseManager
{
private:
    DatabaseConnection *dbConnection;

public:
    AdminDatabaseManager(DatabaseConnection *connection);
    bool addMenuItem(const string &name, const string &description, double price, const string &category, bool availability, const string &type, const string &spiceLevel, const string &cuisine, bool isSweet);
    bool deleteFoodItem(const std::string &foodItemName);
    bool updateMenuItem(const string &name, double price, bool availability, const string &description, const string &category, const string &type, const string &spiceLevel, const string &cuisine, bool isSweet);
    std::string showAllMenuItems();
    std::vector<std::tuple<int, int, int, int, std::string, std::string>> getAllFeedbacks();
    bool connect();
};

#endif // ADMIN_DATABASEMANAGER_H

