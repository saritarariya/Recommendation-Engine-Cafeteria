#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <iostream>
#include <iomanip>
#include <sstream>
#include <stdlib.h>
#include <tuple>
#include <vector>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/exception.h>

using namespace std;
using namespace sql;

class DatabaseManager
{
private:
    string DatabaseServer = "tcp://127.0.0.1:3306";
    string username = "root";
    string password = "Madhusakshi@123";
    string database = "CafeteriaProjectDatabase";
    Connection *databaseConnection = NULL;
    
public:
    bool connect();
    int loginUser(const string &email, const string &password);
    bool addMenuItem(const string &name, const string &description, double price, const string &category, bool availability);
    bool deleteMenuItem(const string &name);
    bool updateMenuItem(const string &name, double price, bool availability);
    std::string showAllMenuItems();
    std::vector<std::tuple<int, int, int, int, std::string, std::string>> getAllFeedbacks();
    bool sendFeedback(const string &menuItemName, const string &feedbackDate, int rating, const string &comments, const string &email);
    bool storeRolledOutFoodItems(const std::vector<std::string> &foodItems , int id);
    std::vector<std::string> getNotifications();
    bool storeFeedback(int userId, int foodItemId, int rating, const std::string &comment);
    bool storeVote(int userId, int foodItemId, int voteCount);
    int getFoodItemId(const std::string &foodItem);
    int getVotesForFoodItem(int foodItemId);
};

#endif // DATABASE_MANAGER_H
