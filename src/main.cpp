#include <iostream>
#include "Client.h"
#include "AccessManager.h"

int main()
{
    Client client;
    if (client.connectToServer() == 1)
    {
        std::cout << "********** Recommendation-Engine-Cafeteria **********" << std::endl;
        std::cout << "======================= Login Panel =======================" << std::endl;
        std::string email,password;
        std::cout << "Enter email:-";
        getline(std::cin, email);
        std::cout << "Enter password:-";
        getline(std::cin, password);
        client.setEmail(email);
        client.setPassword(password);
        if (client.verifyUser())
        {
            std::cout << "user login success full\n";
            AccessManager *accessManager = new AccessManager(&client);
            accessManager->grantAccess(email);
        }
        else
        {
            std::cout << "user does not exist\n";
        }
    }
    else
    {
        std::cout << "Unable to connect to server\n";
    }
    return 0;
}
