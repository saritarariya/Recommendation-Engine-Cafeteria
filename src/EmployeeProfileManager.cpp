#include "EmployeeProfileManager.h"

EmployeeProfileManager::EmployeeProfileManager(Client *client) {
    this->client = client;
}


void EmployeeProfileManager::createProfile(int userId) {
    std::string role = this->client->getRole();
    if (role != "employee") {
        std::cout << "Profile creation is only for employees." << std::endl;
        return;
    }
    if (isProfileCreated(userId)) {
        std::cout << "Profile already created. Skipping profile creation." << std::endl;
        return;
    }

    std::string preferenceType, preferenceValue;

    std::cout << "Please answer these questions to know your preferences" << std::endl;
    std::cout << "1) Please select one-\n- Vegetarian\n- Non Vegetarian\n- Eggetarian" << std::endl;
    std::cin >> preferenceValue;
    preferenceType = "Diet";
    savePreference(userId, preferenceType, preferenceValue);

    std::cout << "2) Please select your spice level\n- High\n- Medium\n- Low" << std::endl;
    std::cin >> preferenceValue;
    preferenceType = "Spice Level";
    savePreference(userId, preferenceType, preferenceValue);

    std::cout << "3) What do you prefer most?\n- North Indian\n- South Indian\n- Other" << std::endl;
    std::cin >> preferenceValue;
    preferenceType = "Cuisine";
    savePreference(userId, preferenceType, preferenceValue);

    std::cout << "4) Do you have a sweet tooth?\n- Yes\n- No" << std::endl;
    std::cin >> preferenceValue;
    preferenceType = "Sweet Tooth";
    savePreference(userId, preferenceType, preferenceValue);

    // work of data base markProfileAsCreated(userId);
}

bool EmployeeProfileManager::isProfileCreated(int userId) {
   //fetch from data base 
}

void EmployeeProfileManager::savePreference(int userId, const std::string& preferenceType, const std::string& preferenceValue) {
   // request from data base
}



