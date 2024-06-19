#include <iostream>
#include "DatabaseManager.h"
#include "Client.h"

using namespace std;
int main()
{
    DatabaseManager dbManager;
    if (dbManager.connect())
    {
        cout << "Connected to database." << endl;
    }
    else
    {
        cerr << "Failed to connect to database." << endl;
        return 1;
    }
    string email;
    cout << "********** Recommendation-Engine-Cafeteria **********" << endl;
    cout << "=== Login Panel ===" << endl;
    cout << "Enter email: ";
    cin >> email;
    if (dbManager.loginUser(email))
    {
        cout << "Login successful!" << endl;
        cout << "Welcome, " << email << "!" << endl;

    }
    else
    {
        cout << "Login failed. Invalid email or password." << endl;
    }
    return 0;
}
