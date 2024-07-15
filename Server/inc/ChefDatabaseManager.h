#ifndef CHEF_DATABASEMANAGER_H
#define CHEF_DATABASEMANAGER_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <memory>
#include <iomanip>
#include "DatabaseConnection.h"

using namespace std;
using namespace sql;

class ChefDatabaseManager
{
private:
    DatabaseConnection *dbConnection;

public:
    ChefDatabaseManager(DatabaseConnection *connection);
    bool storeRolledOutFoodItems(const std::vector<std::string> &foodItems, int id);
    int getTotalVotesForFoodItem(int foodItemId);
    bool connect();
};

#endif // CHEF_DATABASEMANAGER_H
