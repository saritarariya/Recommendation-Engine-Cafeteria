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
        string query = "INSERT INTO FoodItems (FoodItemName, description, price, category, availability) VALUES (?, ?, ?, ?, ?)";
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

bool DatabaseManager::deleteMenuItem(const string &FoodItemName)
{
    if (!databaseConnection)
    {
        cerr << "Not connected to database." << endl;
        return false;
    }

    PreparedStatement *pstmt = nullptr;

    try
    {
        string query = "DELETE FROM FoodItems WHERE FoodItemName = ?";
        pstmt = databaseConnection->prepareStatement(query);
        pstmt->setString(1, FoodItemName);

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

bool DatabaseManager::updateMenuItem(const string &FoodItemName, double price, bool availability)
{
    if (!databaseConnection)
    {
        cerr << "Not connected to database." << endl;
        return false;
    }

    PreparedStatement *pstmt = nullptr;

    try
    {
        string query = "UPDATE FoodItems SET price = ?, availability = ? WHERE FoodItemName = ?";
        pstmt = databaseConnection->prepareStatement(query);
        pstmt->setDouble(1, price);
        pstmt->setBoolean(2, availability);
        pstmt->setString(3, FoodItemName);

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

int DatabaseManager::loginUser(const string &email, const string &password)
{
    int userId = -1;
    if (!databaseConnection)
    {
        cerr << "Not connected to database." << endl;
        return false;
    }

    PreparedStatement *pstmt = nullptr;
    ResultSet *res = nullptr;

    try
    {
        string query = "SELECT * FROM users WHERE Username = ? AND Password = ?";
        pstmt = databaseConnection->prepareStatement(query);
        pstmt->setString(1, email);
        pstmt->setString(2, password);

        res = pstmt->executeQuery();

        if (res->next())
        {
            userId = res->getInt("UserID");
            delete res;
            delete pstmt;
            std::cout << email << " Joined" << "\n";
            return userId;
        }
        else
        {
            delete res;
            delete pstmt;
            return userId;
        }
    }
    catch (SQLException &e)
    {
        cerr << "SQL Error: " << e.what() << endl;
        delete res;
        delete pstmt;
        return userId;
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
        string query = "SELECT * FROM FoodItems";
        stmt = databaseConnection->createStatement();
        res = stmt->executeQuery(query);

        response << "\nMenu Items:\n";
        response << "-------------------------------------------------\n";
        response << setw(20) << left << "FoodItemName" << setw(50) << left << "Description" << setw(10) << left << "Price" << setw(15) << left << "Category" << setw(15) << left << "Availability" << "\n";
        response << "-------------------------------------------------\n";
        while (res->next())
        {
            string name = res->getString("FoodItemName");
            string description = res->getString("Description");
            double price = res->getDouble("Price");
            string category = res->getString("Category");
            bool availability = res->getBoolean("Availability");

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

std::vector<std::tuple<int, int, int, int, std::string, std::string>> DatabaseManager::getAllFeedbacks() {
    std::vector<std::tuple<int, int, int, int, std::string, std::string>> feedbacks;

    if (!databaseConnection) {
        cerr << "Not connected to database." << endl;
        return feedbacks;
    }

    PreparedStatement *pstmt = nullptr;
    ResultSet *res = nullptr;

    try {
        string query = "SELECT * FROM Feedback";
        pstmt = databaseConnection->prepareStatement(query);

        res = pstmt->executeQuery();

        while (res->next()) {
            int feedbackId = res->getInt("FeedbackID");
            int userId = res->getInt("UserID");
            int foodItemId = res->getInt("FoodItemID");
            int rating = res->getInt("Rating");
            string comment = res->getString("Comment");
            string createdAt = res->getString("CreatedAt");

            feedbacks.push_back(make_tuple(feedbackId, userId, foodItemId, rating, comment, createdAt));
        }

        delete res;
        delete pstmt;
    } catch (SQLException &e) {
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

bool DatabaseManager::storeRolledOutFoodItems(const std::vector<std::string> &foodItems , int id)
{
    if (!databaseConnection)
    {
        cerr << "Not connected to database." << endl;
        return false;
    }

    PreparedStatement *pstmt = nullptr;

    try
    {
        string query = "INSERT INTO notifications (Message, SenderID) VALUES (?, ?)";
        pstmt = databaseConnection->prepareStatement(query);
        std::ostringstream oss;
        for (size_t i = 0; i < foodItems.size(); ++i)
        {
            if (i != 0)
                oss << ", ";
            oss << foodItems[i];
        }
        std::string message = "Rolled out food items: " + oss.str();
        std::string idStr = std::to_string(id);

        pstmt->setString(1, message);
        pstmt->setInt(2, id);

        pstmt->executeUpdate();
        delete pstmt;
        return true;
    }
    catch (SQLException &e)
    {
        cerr << "SQL Error: " << e.what() << endl;
        delete pstmt;
        return false;
    }
}

std::vector<std::string> DatabaseManager::getNotifications() {
    std::vector<std::string> notifications;

    if (!databaseConnection) {
        std::cerr << "Not connected to database." << std::endl;
        return notifications;
    }

    PreparedStatement *pstmt = nullptr;
    ResultSet *res = nullptr;

    try {
        std::string query = "SELECT Message FROM Notifications";
        pstmt = databaseConnection->prepareStatement(query);

        res = pstmt->executeQuery();

        while (res->next()) {
            notifications.push_back(res->getString("Message"));
        }

        delete res;
        delete pstmt;
    } catch (SQLException &e) {
        std::cerr << "SQL Error: " << e.what() << std::endl;
        delete res;
        delete pstmt;
    }

    return notifications;
}

bool DatabaseManager::storeFeedback(int userId, int foodItemId, int rating, const std::string &comment) {
    if (!databaseConnection) {
        std::cerr << "Not connected to database." << std::endl;
        return false;
    }

    sql::PreparedStatement *pstmt = nullptr;
    try {
        std::string query = "INSERT INTO Feedback (UserID, FoodItemID, Rating, Comment) VALUES (?, ?, ?, ?)";
        pstmt = databaseConnection->prepareStatement(query);
        pstmt->setInt(1, userId);
        pstmt->setInt(2, foodItemId);
        pstmt->setInt(3, rating);
        pstmt->setString(4, comment);

        pstmt->executeUpdate();
        delete pstmt;
        return true;
    } catch (sql::SQLException &e) {
        std::cerr << "SQL Error: " << e.what() << std::endl;
        delete pstmt;
        return false;
    }
}

bool DatabaseManager::storeVote(int userId, int foodItemId) {
    if (!databaseConnection) {
        std::cerr << "Not connected to database." << std::endl;
        return false;
    }

    sql::PreparedStatement *pstmt = nullptr;

    try {
        std::string query = "INSERT INTO Votes (UserID, FoodItemID, VoteCount) VALUES (?, ?, 1) "
                            "ON DUPLICATE KEY UPDATE VoteCount = VoteCount + 1";

        pstmt = databaseConnection->prepareStatement(query);
        pstmt->setInt(1, userId);
        pstmt->setInt(2, foodItemId);

        pstmt->executeUpdate();
        delete pstmt;
        return true;
    } catch (sql::SQLException &e) {
        std::cerr << "SQL Error: " << e.what() << std::endl;
        delete pstmt;
        return false;
    }
}

int DatabaseManager::getFoodItemId(const std::string &foodItem) {
    if (!databaseConnection) {
        std::cerr << "Not connected to database." << std::endl;
        return -1;
    }

    sql::PreparedStatement *pstmt = nullptr;
    sql::ResultSet *res = nullptr;

    try {
        std::string query = "SELECT FoodItemID FROM FoodItems WHERE FoodItemName = ?";
        pstmt = databaseConnection->prepareStatement(query);
        pstmt->setString(1, foodItem);

        res = pstmt->executeQuery();

        if (res->next()) {
            int foodItemId = res->getInt("FoodItemID");
            delete res;
            delete pstmt;
            return foodItemId;
        } else {
            delete res;
            delete pstmt;
            return -1;
        }
    } catch (sql::SQLException &e) {
        std::cerr << "SQL Error: " << e.what() << std::endl;
        delete res;
        delete pstmt;
        return -1;
    }
}

int DatabaseManager::getTotalVotesForFoodItem(int foodItemId) {
    if (!databaseConnection) {
        std::cerr << "Not connected to database." << std::endl;
        return -1;
    }

    sql::PreparedStatement *pstmt = nullptr;
    sql::ResultSet *res = nullptr;
    int totalVotes = 0;

    try {
        std::string query = "SELECT SUM(VoteCount) AS TotalVotes FROM Votes WHERE FoodItemID = ?";
        pstmt = databaseConnection->prepareStatement(query);
        pstmt->setInt(1, foodItemId);

        res = pstmt->executeQuery();

        if (res->next()) {
            totalVotes = res->getInt("TotalVotes");
        }

        delete res;
        delete pstmt;
    } catch (sql::SQLException &e) {
        std::cerr << "SQL Error: " << e.what() << std::endl;
        delete res;
        delete pstmt;
        return -1;
    }
    return totalVotes;
}

std::string DatabaseManager::getMenuItemName(int foodItemId) {
    if (!databaseConnection) {
        std::cerr << "Not connected to database." << std::endl;
        return "";
    }

    std::string menuItemName;
    sql::PreparedStatement *pstmt = nullptr;
    sql::ResultSet *res = nullptr;

    try {
        std::string query = "SELECT FoodItemName FROM FoodItems WHERE FoodItemID = ?";
        pstmt = databaseConnection->prepareStatement(query);
        pstmt->setInt(1, foodItemId);

        res = pstmt->executeQuery();
        if (res->next()) {
            menuItemName = res->getString("FoodItemName");
        }

        delete res;
        delete pstmt;
    } catch (sql::SQLException &e) {
        std::cerr << "SQL Error: " << e.what() << std::endl;
        delete res;
        delete pstmt;
    }

    return menuItemName;
}