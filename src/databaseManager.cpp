#include "DatabaseManager.h"
#include "AccessManager.h"
bool DatabaseManager::connect() {
    try {
        mysql::MySQL_Driver* driver = mysql::get_mysql_driver_instance();
        con = driver->connect(server, username, password);
        if (con) {
            con->setSchema(database);
            return true;
        } else {
            cerr << "Failed to connect to database." << endl;
            return false;
        }
    } catch (SQLException &e) {
        cerr << "SQL Error: " << e.what() << endl;
        return false;
    }
}

bool DatabaseManager::loginUser(const string& email) {
    if (!con) {
        cerr << "Not connected to database." << endl;
        return false;
    }

    PreparedStatement* pstmt = nullptr;
    ResultSet* res = nullptr;

    try {
        string query = "SELECT * FROM users WHERE email = ?";
        pstmt = con->prepareStatement(query);
        pstmt->setString(1, email);
        
        res = pstmt->executeQuery();
        
        if (res->next()) {
            delete res;
            delete pstmt;
            AccessManager a1;
            a1.grantAccess(email);
            return true;  // Email exists in the database

        } else {
            delete res;
            delete pstmt;
            return false; // Email does not exist in the database
        }
    } catch (SQLException &e) {
        cerr << "SQL Error: " << e.what() << endl;
        delete res;
        delete pstmt;
        return false;
    }
}



  
