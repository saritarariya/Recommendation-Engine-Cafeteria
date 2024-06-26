#include <iostream>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include "AccessManager.h"  // Assuming this is where AccessManager is defined

DatabaseManager::DatabaseManager(Client *) {
   this->client = client;
}

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

bool DatabaseManager::addMenuItem(const string& name, const string& description, double price, const string& category, bool availability) {
    if (!con) {
        cerr << "Not connected to database." << endl;
        return false;
    }

    PreparedStatement* pstmt = nullptr;

    try {
        string query = "INSERT INTO menu_items (name, description, price, category, availability) VALUES (?, ?, ?, ?, ?)";
        pstmt = con->prepareStatement(query);
        pstmt->setString(1, name);
        pstmt->setString(2, description);
        pstmt->setDouble(3, price);
        pstmt->setString(4, category);
        pstmt->setBoolean(5, availability);

        int updateCount = pstmt->executeUpdate();
        delete pstmt;
        return updateCount > 0;  // Return true if insertion was successful
    } catch (SQLException &e) {
        cerr << "SQL Error: " << e.what() << endl;
        delete pstmt;
        return false;
    }
}

bool DatabaseManager::deleteMenuItem(const string& name) {
    if (!con) {
        cerr << "Not connected to database." << endl;
        return false;
    }

    PreparedStatement* pstmt = nullptr;

    try {
        string query = "DELETE FROM menu_items WHERE name = ?";
        pstmt = con->prepareStatement(query);
        pstmt->setString(1, name);

        int updateCount = pstmt->executeUpdate();
        delete pstmt;
        return updateCount > 0;  // Return true if deletion was successful
    } catch (SQLException &e) {
        cerr << "SQL Error: " << e.what() << endl;
        delete pstmt;
        return false;
    }
}

bool DatabaseManager::updateMenuItem(const string& name, double price, bool availability) {
    if (!con) {
        cerr << "Not connected to database." << endl;
        return false;
    }

    PreparedStatement* pstmt = nullptr;

    try {
        string query = "UPDATE menu_items SET price = ?, availability = ? WHERE name = ?";
        pstmt = con->prepareStatement(query);
        pstmt->setDouble(1, price);
        pstmt->setBoolean(2, availability);
        pstmt->setString(3, name);

        int updateCount = pstmt->executeUpdate();
        delete pstmt;
        return updateCount > 0;  // Return true if update was successful
    } catch (SQLException &e) {
        cerr << "SQL Error: " << e.what() << endl;
        delete pstmt;
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
            AccessManager acsessManger;
            acsessManger.dbManager = this;
            acsessManger.grantAccess(email);
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

void DatabaseManager::showAllMenuItems() {
    if (!con) {
        cerr << "Not connected to database." << endl;
        return;
    }

    Statement* stmt = nullptr;
    ResultSet* res = nullptr;

    try {
        string query = "SELECT * FROM menu_items";
        stmt = con->createStatement();
        res = stmt->executeQuery(query);

        cout << "\nMenu Items:" << endl;
        cout << "-------------------------------------------------" << endl;
        cout << setw(20) << left << "Name" << setw(50) << left << "Description" << setw(10) << left << "Price" << setw(15) << left << "Category" << setw(15) << left << "Availability" << endl;
        cout << "-------------------------------------------------" << endl;

        while (res->next()) {
            string name = res->getString("name");
            string description = res->getString("description");
            double price = res->getDouble("price");
            string category = res->getString("category");
            bool availability = res->getBoolean("availability");

            cout << setw(20) << left << name << setw(50) << left << description << setw(10) << left << price << setw(15) << left << category << setw(15) << left << (availability ? "Yes" : "No") << endl;
        }
        cout << "-------------------------------------------------" << endl;

        delete res;
        delete stmt;
    } catch (SQLException &e) {
        cerr << "SQL Error: " << e.what() << endl;
        delete res;
        delete stmt;
    }
}
