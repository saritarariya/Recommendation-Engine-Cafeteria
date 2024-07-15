#include "EmployeeDatabaseManager.h"

EmployeeDatabaseManager::EmployeeDatabaseManager(DatabaseConnection *connection)
{
    dbConnection = connection;
}

bool EmployeeDatabaseManager::connect()
{
    return dbConnection->connect();
}

bool EmployeeDatabaseManager::sendFeedback(int userID, int foodItemID, int rating, const string &comments)
{
    std::cout << userID << foodItemID << rating << comments << std::endl;
    try
    {
        Connection *conn = dbConnection->getConnection();
        PreparedStatement *pstmt = conn->prepareStatement("INSERT INTO feedback (UserID, FoodItemID, Rating, Comment) VALUES (?, ?, ?, ?)");
        pstmt->setInt(1, userID);
        pstmt->setInt(2, foodItemID);
        pstmt->setInt(3, rating);
        pstmt->setString(4, comments);
        pstmt->execute();
        delete pstmt;
        return true;
    }
    catch (SQLException &e)
    {
        cerr << "Error sending feedback: " << e.what() << endl;
        return false;
    }
}

std::vector<std::string> EmployeeDatabaseManager::getNotifications() {
    std::vector<std::string> notifications;
    Connection *conn = dbConnection->getConnection();

    PreparedStatement *pstmt = nullptr;
    ResultSet *res = nullptr;

    try {
        std::string query = "SELECT Message FROM Notifications";
        pstmt = conn->prepareStatement(query);

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

bool EmployeeDatabaseManager::storeFeedback(int userId, int foodItemId, int rating, const std::string &comment)
{
    try
    {
        Connection *conn = dbConnection->getConnection();
        PreparedStatement *pstmt = conn->prepareStatement("INSERT INTO Feedbacks (userId, foodItemId, rating, comment) VALUES (?, ?, ?, ?)");
        pstmt->setInt(1, userId);
        pstmt->setInt(2, foodItemId);
        pstmt->setInt(3, rating);
        pstmt->setString(4, comment);
        pstmt->execute();
        delete pstmt;
        return true;
    }
    catch (SQLException &e)
    {
        cerr << "Error storing feedback: " << e.what() << endl;
        return false;
    }
}

bool EmployeeDatabaseManager::storeVote(int userId, int foodItemId) {
    Connection *conn = dbConnection->getConnection();
    try {
        std::string query = "INSERT INTO Votes (UserID, FoodItemID, VoteCount) VALUES (?, ?, 1) "
                            "ON DUPLICATE KEY UPDATE VoteCount = VoteCount + 1";

        PreparedStatement *pstmt = conn->prepareStatement(query);
        pstmt->setInt(1, userId);
        pstmt->setInt(2, foodItemId);

        pstmt->executeUpdate();
        delete pstmt;
        return true;
    } catch (sql::SQLException &e) {
        std::cerr << "SQL Error: " << e.what() << std::endl;
        return false;
    }
}

int EmployeeDatabaseManager::getFoodItemId(const std::string &foodItem)
{
    try
    {
        sql::Connection *conn = dbConnection->getConnection();
        std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement("SELECT FoodItemID FROM foodItems WHERE FoodItemName = ?"));
        pstmt->setString(1, foodItem);
        std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());
        if (res->next())
        {
            int foodItemId = res->getInt("FoodItemID"); // Ensure this matches your database schema
            return foodItemId;
        }
        return -1;
    }
    catch (sql::SQLException &e)
    {
        std::cerr << "Error getting food item ID: " << e.what() << std::endl;
        return -1;
    }
}

std::string EmployeeDatabaseManager::getMenuItemName(int foodItemId)
{
    try
    {
        Connection *conn = dbConnection->getConnection();
        PreparedStatement *pstmt = conn->prepareStatement("SELECT FoodItemName FROM fooditems WHERE FoodItemID = ?");
        pstmt->setInt(1, foodItemId);
        ResultSet *res = pstmt->executeQuery();
        if (res->next())
        {
            std::string name = res->getString("FoodItemName");
            delete res;
            delete pstmt;
            return name;
        }
        delete res;
        delete pstmt;
        return "";
    }
    catch (SQLException &e)
    {
        cerr << "Error getting menu item name: " << e.what() << endl;
        return "";
    }
}

bool EmployeeDatabaseManager::isProfileCreated(int userId) {
    try {
        sql::Connection *conn = dbConnection->getConnection();
        std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement("SELECT COUNT(*) AS count FROM EmployeePreferences WHERE employeeId = ?"));
        pstmt->setInt(1, userId);
        std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

        if (res->next()) {
            int count = res->getInt("count");
            return count > 0;
        }

        return false;
    } catch (sql::SQLException &e) {
        std::cerr << "Error checking profile creation: " << e.what() << std::endl;
        return false;
    }
}

bool EmployeeDatabaseManager::savePreference(int userId, const std::string& preferenceType, const std::string& preferenceValue) {
    try {
        sql::Connection *conn = dbConnection->getConnection();

        std::unique_ptr<sql::PreparedStatement> checkStmt(conn->prepareStatement("SELECT COUNT(*) FROM users WHERE UserID = ?"));
        checkStmt->setInt(1, userId);
        std::unique_ptr<sql::ResultSet> res(checkStmt->executeQuery());
        res->next();
        int count = res->getInt(1);
        if (count == 0) {
            std::cerr << "Error: userId " << userId << " does not exist in the users table." << std::endl;
            return false;
        }

        std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement("INSERT INTO EmployeePreferences (employeeId, preferenceType, preferenceValue) VALUES (?, ?, ?)"));
        pstmt->setInt(1, userId);
        pstmt->setString(2, preferenceType);
        pstmt->setString(3, preferenceValue);
        pstmt->executeUpdate();
        return true;
    } catch (sql::SQLException &e) {
        std::cerr << "Error saving preference: " << e.what() << std::endl;
        return false;
    }
}

std::string EmployeeDatabaseManager::fetchEmployeePreferences(int employeeId) {
    try {
        sql::Connection *conn = dbConnection->getConnection();
        std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement("SELECT * FROM EmployeePreferences WHERE employeeId = ?"));
        pstmt->setInt(1, employeeId);
        std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

        std::ostringstream resultStream;
        while (res->next()) {
            resultStream << "ID: " << res->getInt("id") << "\n";
            resultStream << "Employee ID: " << res->getInt("employeeId") << "\n";
            resultStream << "Preference Type: " << res->getString("preferenceType") << "\n";
            resultStream << "Preference Value: " << res->getString("preferenceValue") << "\n";
            resultStream << "---------------------------\n";
        }

        return resultStream.str();
    } catch (sql::SQLException &e) {
        std::cerr << "Error fetching employee preferences: " << e.what() << std::endl;
        return "Error executing query.";
    }
}

std::string EmployeeDatabaseManager::showFoodItemDetails(const std::string& foodItemName)
{

    std::stringstream response;
    if (!dbConnection)
    {
        std::cerr << "Not connected to database." << std::endl;
        return response.str();
    }

    sql::Statement *stmt = nullptr;
    sql::ResultSet *res = nullptr;
    try
    {
        std::string query = "SELECT * FROM FoodItems WHERE FoodItemName = ?";
        sql::Connection *conn = dbConnection->getConnection();
        sql::PreparedStatement *pstmt = conn->prepareStatement(query);
        pstmt->setString(1, foodItemName);  
        res = pstmt->executeQuery();
        
        if (res->next())
        {
            std::string name = res->getString("FoodItemName");
            std::string description = res->getString("Description");
            double price = res->getDouble("Price");
            std::string category = res->getString("Category");
            bool availability = res->getBoolean("Availability");
            std::string type = res->getString("type");
            std::string spiceLevel = res->getString("spiceLevel");
            std::string cuisine = res->getString("cuisine");
            bool isSweet = res->getBoolean("isSweet");

            response << name << ":" << description << ":" << price << ":" << category << ":" 
                     << (availability ? "Yes" : "No") << ":" << type << ":" << spiceLevel << ":" 
                     << cuisine << ":" << (isSweet ? "Yes" : "No") << "\n";
        }
        else
        {
            response << "Food item not found." << std::endl;
        }

        delete res;
        delete pstmt;
        delete stmt;
    }
    catch (sql::SQLException &e)
    {
        std::cerr << "SQL Error: " << e.what() << std::endl;
        delete res;
        delete stmt;
        return response.str();
    }
    return response.str();
}
