#ifndef DATABASE_MANAGER_H
#define DATABASE_MANAGER_H

#include <iostream>
#include <stdlib.h>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/exception.h>

using namespace std;
using namespace sql;

class DatabaseManager {
private:
    string server = "tcp://127.0.0.1:3306";
    string username = "root";
    string password = "Madhusakshi@123";
    string database = "CafeteriaProjectDatabase";
    Connection* con;

public:
    bool connect();
    bool loginUser(const string& email);
};

#endif // DATABASE_MANAGER_H
