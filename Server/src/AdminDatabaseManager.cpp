#include "AdminDatabaseManager.h"

AdminDatabaseManager::AdminDatabaseManager(DatabaseConnection *connection) : dbConnection(connection) {}

bool AdminDatabaseManager::connect()
{
    return dbConnection->connect();
}

bool AdminDatabaseManager::addMenuItem(const string &name, const string &description, double price, const string &category, bool availability, const string &type, const string &spiceLevel, const string &cuisine, bool isSweet)
{
    try
    {
        Connection *conn = dbConnection->getConnection();
        PreparedStatement *pstmt = conn->prepareStatement("INSERT INTO FoodItems (FoodItemName, Description, Price, Category, Availability, type, spiceLevel, cuisine, isSweet) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)");
        pstmt->setString(1, name);
        pstmt->setString(2, description);
        pstmt->setDouble(3, price);
        pstmt->setString(4, category);
        pstmt->setBoolean(5, availability);
        pstmt->setString(6, type);
        pstmt->setString(7, spiceLevel);
        pstmt->setString(8, cuisine);
        pstmt->setBoolean(9, isSweet);
        pstmt->execute();
        delete pstmt;
        return true;
    }
    catch (SQLException &e)
    {
        cerr << "Error adding menu item: " << e.what() << endl;
        return false;
    }
}

bool AdminDatabaseManager::deleteMenuItem(const string &name)
{
    try
    {
        Connection *conn = dbConnection->getConnection();
        PreparedStatement *pstmt = conn->prepareStatement("DELETE FROM FoodItems WHERE FoodItemName = ?");
        pstmt->setString(1, name);
        pstmt->execute();
        delete pstmt;
        return true;
    }
    catch (SQLException &e)
    {
        cerr << "Error deleting menu item: " << e.what() << endl;
        return false;
    }
}

bool AdminDatabaseManager::updateMenuItem(const string &name, double price, bool availability, const string &description, const string &category, const string &type, const string &spiceLevel, const string &cuisine, bool isSweet)
{
    try
    {
        Connection *conn = dbConnection->getConnection();
        PreparedStatement *pstmt = conn->prepareStatement("UPDATE FoodItems SET Price = ?, Availability = ?, Description = ?, Category = ?, Type = ?, SpiceLevel = ?, Cuisine = ?, IsSweet = ? WHERE FoodItemName = ?");
        pstmt->setDouble(1, price);
        pstmt->setBoolean(2, availability);
        pstmt->setString(3, description);
        pstmt->setString(4, category);
        pstmt->setString(5, type);
        pstmt->setString(6, spiceLevel);
        pstmt->setString(7, cuisine);
        pstmt->setBoolean(8, isSweet);
        pstmt->setString(9, name);
        pstmt->execute();
        delete pstmt;
        return true;
    }
    catch (SQLException &e)
    {
        cerr << "Error updating menu item: " << e.what() << endl;
        return false;
    }
}

std::string AdminDatabaseManager::showAllMenuItems()
{
    stringstream response;
    if (!dbConnection)
    {
        cerr << "Not connected to database." << endl;
        return response.str();
    }

    Statement *stmt = nullptr;
    ResultSet *res = nullptr;
    try
    {
        string query = "SELECT * FROM FoodItems";
        Connection *conn = dbConnection->getConnection();
        stmt = conn->createStatement();
        res = stmt->executeQuery(query);

        response << "\nMenu Items:\n";
        response << "--------------------------------------------------------------------------------------------------------------------------\n";
        response << setw(20) << left << "FoodItemName" << setw(50) << left << "Description" << setw(10) << left << "Price" << setw(15) << left << "Category" << setw(15) << left << "Availability" << setw(15) << left << "Type" << setw(15) << left << "Spice Level" << setw(15) << left << "Cuisine" << setw(15) << left << "Is Sweet" << "\n";
        response << "--------------------------------------------------------------------------------------------------------------------------\n";
        while (res->next())
        {
            string name = res->getString("FoodItemName");
            string description = res->getString("Description");
            double price = res->getDouble("Price");
            string category = res->getString("Category");
            bool availability = res->getBoolean("Availability");
            string type = res->getString("type");
            string spiceLevel = res->getString("spiceLevel");
            string cuisine = res->getString("cuisine");
            bool isSweet = res->getBoolean("isSweet");

            response << setw(20) << left << name << setw(50) << left << description << setw(10) << left << price << setw(15) << left << category << setw(15) << left << (availability ? "Yes" : "No") << setw(15) << left << type << setw(15) << left << spiceLevel << setw(15) << left << cuisine << setw(15) << left << (isSweet ? "Yes" : "No") << "\n";
        }
        response << "--------------------------------------------------------------------------------------------------------------------------\n";

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

std::vector<std::tuple<int, int, int, int, std::string, std::string>> AdminDatabaseManager::getAllFeedbacks() {
    Connection *conn = dbConnection->getConnection();
    std::vector<std::tuple<int, int, int, int, std::string, std::string>> feedbacks;
    PreparedStatement *pstmt = nullptr;
    ResultSet *res = nullptr;

    try {
        string query = "SELECT * FROM Feedback";
        pstmt = conn->prepareStatement(query);

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


