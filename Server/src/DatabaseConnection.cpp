#include "DatabaseConnection.h"

bool DatabaseConnection::connect()
{
    if (databaseConnection == NULL)
    {
        try
        {
            mysql::MySQL_Driver *driver = mysql::get_mysql_driver_instance();
            databaseConnection = driver->connect(DatabaseServer, username, password);
            databaseConnection->setSchema(database);
            return true;
        }
        catch (SQLException &e)
        {
            cerr << "Error connecting to the database: " << e.what() << endl;
            return false;
        }
    }
    return true;
}

Connection *DatabaseConnection::getConnection()
{
    return databaseConnection;
}

int DatabaseConnection::loginUser(const string &Username, const string &Password)
{
    try
    {
        PreparedStatement *pstmt = databaseConnection->prepareStatement("SELECT UserID FROM Users WHERE Username = ? AND Password = ?");
        pstmt->setString(1, Username);
        pstmt->setString(2, Password);
        ResultSet *res = pstmt->executeQuery();
        if (res->next())
        {
            int userId = res->getInt("UserID");
            delete res;
            delete pstmt;
            return userId;
        }
        delete res;
        delete pstmt;
        return -1;
    }
    catch (SQLException &e)
    {
        cerr << "Error logging in: " << e.what() << endl;
        return -1;
    }
}
