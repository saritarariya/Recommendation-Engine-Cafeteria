#include <iostream>
#include <string>
#include "Client.h"

class EmployeeProfileManager {

private:
    Client *client;
    EmployeeProfileManager(Client *);
public:
    void createProfile(int userId);
    bool isProfileCreated(int userId);
    void savePreference(int userId, const std::string& preferenceType, const std::string& preferenceValue);
};
