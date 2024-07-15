#include "ChefDatabaseManager.h"

ChefDatabaseManager::ChefDatabaseManager(DatabaseConnection *connection)
{
    dbConnection = connection;
}

bool ChefDatabaseManager::connect()
{
    return dbConnection->connect();
}

bool ChefDatabaseManager::storeRolledOutFoodItems(const std::vector<std::string> &foodItems , int id)
{
    Connection *conn = dbConnection->getConnection();
    PreparedStatement *pstmt = nullptr;

    try
    {
        string query = "INSERT INTO Notifications (Message, SenderID) VALUES (?, ?)";
        pstmt = conn->prepareStatement(query);
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

int ChefDatabaseManager::getTotalVotesForFoodItem(int foodItemId) {
    Connection *conn = dbConnection->getConnection();
    sql::PreparedStatement *pstmt = nullptr;
    sql::ResultSet *res = nullptr;
    int totalVotes = 0;

    try {
        std::string query = "SELECT VoteCount AS TotalVotes FROM Votes WHERE FoodItemID = ?";
        pstmt = conn->prepareStatement(query);
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

bool ChefDatabaseManager::storeDiscardMenuItemList(const std::vector<int>& discardedMenuItems) {



    sql::Connection* conn = dbConnection->getConnection();
    sql::PreparedStatement* pstmt = nullptr;

    try {
        std::string query = "INSERT INTO DiscardMenuItemList (foodItemID) VALUES (?)";
        pstmt = conn->prepareStatement(query);

        for (const auto& itemId : discardedMenuItems) {
            pstmt->setInt(1, itemId);
            pstmt->executeUpdate();
        }
        delete pstmt;
        return true;
    } catch (sql::SQLException& e) {
        std::cerr << "SQL Error: " << e.what() << std::endl;
        if (pstmt) delete pstmt;
        return false;
    }
}