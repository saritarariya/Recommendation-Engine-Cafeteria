#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <iostream>
#include <iomanip>
#include <sstream>
#include <stdlib.h>
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
    bool loginUser(const string &email);
    bool addMenuItem(const string &name, const string &description, double price, const string &category, bool availability);
    bool deleteMenuItem(const string &name);
    bool updateMenuItem(const string &name, double price, bool availability);
    std::string showAllMenuItems();
};

#endif // DATABASE_MANAGER_H
