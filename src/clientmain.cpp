#include <iostream>
#include "Client.h"
#include "AccessManager.h"

int main()
{
    Client client;
    if (client.connectToServer() == 1)
    {
        std::cout << "********** Recommendation-Engine-Cafeteria **********" << std::endl;
        std::cout << "=== Login Panel ===" << std::endl;
        std::string email;
        std::cout << "Enter email: ";
        std::cin >> email;
        client.setEmail(email);
        if(client.verifyUser()) {
            std::cout<<"user login successfull\n";
            AccessManager *accessManager = new  AccessManager(&client);
            accessManager->grantAccess(email);
        }
        else {
            std::cout<<"user does not exist\n";
        }
    }
    return 0;
}
