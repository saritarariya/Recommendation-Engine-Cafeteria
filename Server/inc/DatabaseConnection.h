#ifndef DATABASECONNECTION_H
#define DATABASECONNECTION_H

#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/exception.h>

using namespace std;
using namespace sql;

class DatabaseConnection
{
private:
    string DatabaseServer = "tcp://127.0.0.1:3306";
    string username = "root";
    string password = "Madhusakshi@123";
    string database = "CafeteriaProjectDatabase";
    Connection *databaseConnection = NULL;

public:
    bool connect();
    Connection* getConnection();
    int loginUser(const string &Username, const string &Password);
};

#endif // DATABASECONNECTION_H

