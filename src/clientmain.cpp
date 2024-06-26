#include <iostream>
#include "DatabaseManager.h"
#include "Client.h"

int main()
{
    Client *client = new Client();
    if (client->connectToServer() == 1)
    {   
        client->sendRole("messege");
        client->messageTransfer();
        DatabaseManager *dbManager = new DatabaseManager(client);
        if (dbManager->connect())
        {
            cout << "********** Recommendation-Engine-Cafeteria **********" << endl;
            cout << "=== Login Panel ===" << endl;
        }
        else
        {
            cerr << "Failed to connect to database." << endl;
            return 1;
        }
        string email;
        std::cout << "Enter email: ";
        std::cin >> email;
        if (dbManager->loginUser(email))
        {
           std::cout << "\nThank you for using our app! We look forward to seeing you soon." << std::endl;
        }
        else
        {
            std::cout << "Login failed. Invalid email or password." << endl;
        }
    }
return 0;
}
