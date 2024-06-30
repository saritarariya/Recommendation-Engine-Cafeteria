#include <iostream>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include "databaseManager.h"

bool DatabaseManager::connect()
{
    if (databaseConnection == NULL)
    {
        try
        {
            mysql::MySQL_Driver *driver = mysql::get_mysql_driver_instance();
            databaseConnection = driver->connect(DatabaseServer, username, password);
            if (databaseConnection)
            {
                databaseConnection->setSchema(database);
                return true;
            }
            else
            {
                cerr << "Failed to connect to database." << endl;
                return false;
            }
        }
        catch (SQLException &e)
        {
            cerr << "SQL Error: " << e.what() << endl;
            return false;
        }
        return true;
    }
    return true;
}

bool DatabaseManager::addMenuItem(const string &name, const string &description, double price, const string &category, bool availability)
{
    if (!databaseConnection)
    {
        cerr << "Not connected to database." << endl;
        return false;
    }

    PreparedStatement *pstmt = nullptr;

    try
    {
        string query = "INSERT INTO menu_items (name, description, price, category, availability) VALUES (?, ?, ?, ?, ?)";
        pstmt = databaseConnection->prepareStatement(query);
        pstmt->setString(1, name);
        pstmt->setString(2, description);
        pstmt->setDouble(3, price);
        pstmt->setString(4, category);
        pstmt->setBoolean(5, availability);

        int updateCount = pstmt->executeUpdate();
        delete pstmt;
        return updateCount > 0;
    }
    catch (SQLException &e)
    {
        cerr << "SQL Error: " << e.what() << endl;
        delete pstmt;
        return false;
    }
}

bool DatabaseManager::deleteMenuItem(const string &name)
{
    if (!databaseConnection)
    {
        cerr << "Not connected to database." << endl;
        return false;
    }

    PreparedStatement *pstmt = nullptr;

    try
    {
        string query = "DELETE FROM menu_items WHERE name = ?";
        pstmt = databaseConnection->prepareStatement(query);
        pstmt->setString(1, name);

        int updateCount = pstmt->executeUpdate();
        delete pstmt;
        return updateCount > 0;
    }
    catch (SQLException &e)
    {
        cerr << "SQL Error: " << e.what() << endl;
        delete pstmt;
        return false;
    }
}

bool DatabaseManager::updateMenuItem(const string &name, double price, bool availability)
{
    if (!databaseConnection)
    {
        cerr << "Not connected to database." << endl;
        return false;
    }

    PreparedStatement *pstmt = nullptr;

    try
    {
        string query = "UPDATE menu_items SET price = ?, availability = ? WHERE name = ?";
        pstmt = databaseConnection->prepareStatement(query);
        pstmt->setDouble(1, price);
        pstmt->setBoolean(2, availability);
        pstmt->setString(3, name);

        int updateCount = pstmt->executeUpdate();
        delete pstmt;
        return updateCount > 0;
    }
    catch (SQLException &e)
    {
        cerr << "SQL Error: " << e.what() << endl;
        delete pstmt;
        return false;
    }
}

bool DatabaseManager::loginUser(const string &email)
{
    if (!databaseConnection)
    {
        cerr << "Not connected to database." << endl;
        return false;
    }

    PreparedStatement *pstmt = nullptr;
    ResultSet *res = nullptr;

    try
    {
        string query = "SELECT * FROM users WHERE email = ?";
        pstmt = databaseConnection->prepareStatement(query);
        pstmt->setString(1, email);

        res = pstmt->executeQuery();

        if (res->next())
        {
            delete res;
            delete pstmt;
            std::cout << email << "Joined" << "\n";
            return true;
        }
        else
        {
            delete res;
            delete pstmt;
            return false;
        }
    }
    catch (SQLException &e)
    {
        cerr << "SQL Error: " << e.what() << endl;
        delete res;
        delete pstmt;
        return false;
    }
}

std::string DatabaseManager::showAllMenuItems()
{
    stringstream response;
    if (!databaseConnection)
    {
        cerr << "Not connected to database." << endl;
        return response.str();
    }

    Statement *stmt = nullptr;
    ResultSet *res = nullptr;
    try
    {
        string query = "SELECT * FROM menu_items";
        stmt = databaseConnection->createStatement();
        res = stmt->executeQuery(query);

        response << "\nMenu Items:\n";
        response << "-------------------------------------------------\n";
        response << setw(20) << left << "Name" << setw(50) << left << "Description" << setw(10) << left << "Price" << setw(15) << left << "Category" << setw(15) << left << "Availability" << "\n";
        response << "-------------------------------------------------\n";
        while (res->next())
        {
            string name = res->getString("name");
            string description = res->getString("description");
            double price = res->getDouble("price");
            string category = res->getString("category");
            bool availability = res->getBoolean("availability");

            response << setw(20) << left << name << setw(50) << left << description << setw(10) << left << price << setw(15) << left << category << setw(15) << left << (availability ? "Yes" : "No") << "\n";
        }
        response << "-------------------------------------------------\n";

        delete res;
        delete stmt;
    }
    catch (SQLException &e)
    {
        cerr << "SQL Error: " << e.what() << endl;
        delete res;
        delete stmt;
        return response.str();
    }
    return response.str();
}

std::vector<tuple<int, string, string, int, string, string>> DatabaseManager::getAllFeedbacks()
{
    std::vector<tuple<int, string, string, int, string, string>> feedbacks;

    if (!databaseConnection)
    {
        cerr << "Not connected to database." << endl;
        return feedbacks;
    }

    PreparedStatement *pstmt = nullptr;
    ResultSet *res = nullptr;

    try
    {
        string query = "SELECT * FROM feedback";
        pstmt = databaseConnection->prepareStatement(query);

        res = pstmt->executeQuery();

        while (res->next())
        {
            int feedbackId = res->getInt("feedback_id");
            string menuItemName = res->getString("menu_item_name");
            string feedback_date = res->getString("feedback_date");
            int rating = res->getInt("rating");
            string comments = res->getString("comments");
            string email = res->getString("email");

            feedbacks.push_back(make_tuple(feedbackId, menuItemName, feedback_date, rating, comments, email));
        }

        delete res;
        delete pstmt;
    }
    catch (SQLException &e)
    {
        cerr << "SQL Error: " << e.what() << endl;
        delete res;
        delete pstmt;
    }

    return feedbacks;
}

bool DatabaseManager::sendFeedback(const string &menuItemName, const string &feedbackDate, int rating, const string &comments, const string &email)
{
    if (!databaseConnection)
    {
        cerr << "Not connected to database." << endl;
        return false;
    }

    PreparedStatement *pstmt = nullptr;

    try
    {
        string query = "INSERT INTO feedback (menuItemName, feedback_date, rating, comments, email) VALUES (?, ?, ?, ?, ?)";
        pstmt = databaseConnection->prepareStatement(query);
        pstmt->setString(1, menuItemName);
        pstmt->setString(2, feedbackDate);
        pstmt->setInt(3, rating);
        pstmt->setString(4, comments);
        pstmt->setString(5, email);

        int rowsInserted = pstmt->executeUpdate();
        delete pstmt;

        if (rowsInserted == 1)
        {
            cout << "Feedback sent successfully." << endl;
            return true;
        }
        else
        {
            cerr << "Failed to send feedback." << endl;
            return false;
        }
    }
    catch (SQLException &e)
    {
        cerr << "SQL Error: " << e.what() << endl;
        delete pstmt;
        return false;
    }
}

