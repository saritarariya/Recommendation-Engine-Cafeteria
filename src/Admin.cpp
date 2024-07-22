#include "Admin.h"

bool Admin::isValidType(const std::string &type)
{
    static const std::vector<std::string> validTypes = {"Vegetarian", "Non Vegetarian", "Eggetarian"};
    return std::find(validTypes.begin(), validTypes.end(), type) != validTypes.end();
}

bool Admin::isValidSpiceLevel(const std::string &spiceLevel)
{
    static const std::vector<std::string> validSpiceLevels = {"High", "Medium", "Low"};
    return std::find(validSpiceLevels.begin(), validSpiceLevels.end(), spiceLevel) != validSpiceLevels.end();
}

bool Admin::isValidCuisine(const std::string &cuisine)
{
    static const std::vector<std::string> validCuisines = {"North Indian", "South Indian", "Other"};
    return std::find(validCuisines.begin(), validCuisines.end(), cuisine) != validCuisines.end();
}


std::string Admin::getValidatedInput(const std::string &prompt, const std::string &errorMessage, bool (*isValid)(const std::string &))
{
    std::string input;
    while (true)
    {
        std::cout << prompt;
        std::getline(std::cin, input);
        if (!input.empty() && isValid(input))
        {
            return input;
        }
        std::cout << errorMessage << std::endl;
    }
}

bool Admin::isValidCategory(const std::string &category)
{
    static const std::vector<std::string> validCategories = {"Breakfast", "Lunch", "Dinner"};
    return std::find(validCategories.begin(), validCategories.end(), category) != validCategories.end();
}

void Admin::addMenuItem()
{
    std::string name = Utility::getNonEmptyInput("Enter the name of the menu item: ", "Name cannot be blank.");
    std::string description = Utility::getNonEmptyInput("Enter the description of the menu item: ", "Description cannot be blank.");
    std::string price = Utility::getNumericInput("Enter the price of the menu item: ", "Invalid input. Enter a numeric value for the price.");
    std::string category = getValidatedInput("Enter the category of the menu item (Breakfast, Lunch, Dinner): ", "Not a valid input.", Admin::isValidCategory);
    std::string availability = Utility::getBinaryInput("Is the menu item available? (1 for Yes, 0 for No): ", "Invalid input. Enter 1 for Yes or 0 for No.");
    std::string type = getValidatedInput("Enter the type of the menu item (Vegetarian, Non Vegetarian, Eggetarian): ", "Not a valid input.", Admin::isValidType);
    std::string spiceLevel = getValidatedInput("Enter the spice level of the menu item (High, Medium, Low): ", "Not a valid input.", Admin::isValidSpiceLevel);
    std::string cuisine = getValidatedInput("Enter the cuisine of the menu item (North Indian, South Indian, Other): ", "Not a valid input.", Admin::isValidCuisine);
    std::string isSweet = Utility::getBinaryInput("Is the menu item sweet? (1 for Yes, 0 for No): ", "Invalid input. Enter 1 for Yes or 0 for No.");

    std::string request = "addMenuItem:" + name + "\n" + description + "\n" + price + "\n" + category + "\n" + availability + "\n" + type + "\n" + spiceLevel + "\n" + cuisine + "\n" + isSweet + '\0';

    sendRequest(request);

    std::string response = receiveResponse();
    if (response == "Menu item added successfully")
    {
        std::cout << "Menu item " << name << " added successfully!" << std::endl;
    }
    else
    {
        std::cerr << "Failed to add menu item '" << name << "'. Please try again." << std::endl;
    }
}

void Admin::showOptions()
{
    std::cout << "\nAdmin Menu:" << std::endl;
    std::cout << "1. Add a menu item" << std::endl;
    std::cout << "2. Delete a menu item" << std::endl;
    std::cout << "3. Update a menu item" << std::endl;
    std::cout << "4. View all menu items" << std::endl;
    std::cout << "5. Exit" << std::endl;
}

void Admin::performRoleFunctions()
{
    while (true)
    {
        showOptions();
        std::string choiceStr = Utility::getNumericInput("Enter your choice: ", "Invalid input.");
        int choice = stoi(choiceStr);
        switch (choice)
        {
        case 1:
            addMenuItem();
            break;
        case 2:
            deleteMenuItem();
            break;
        case 3:
            updateMenuItem();
            break;
        case 4:
            viewAllMenuItems();
            break;
        case 5:
            std::cout << "Exiting..." << std::endl;
            return;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }
}

void Admin::deleteMenuItem()
{
    std::string name = Utility::getNonEmptyInput("Enter the name of the menu item to delete: ", "name cannot be blank.");
    std::string request = "deleteMenuItem:" + name;
    sendRequest(request);
    std::string response = receiveResponse();
    if (response == "Menu item deleted successfully")
    {
        std::cout << "Menu item '" << name << "' deleted successfully!" << std::endl;
    }
    else
    {
        std::cerr << "Failed to delete menu item '" << name << "'. Please try again." << std::endl;
    }
}

void Admin::updateMenuItem()
{
    std::string name = Utility::getNonEmptyInput("Enter the name of the menu item to update: ", "Name cannot be blank.");
    std::string description = Utility::getNonEmptyInput("Enter the new description of the menu item: ", "Description cannot be blank.");
    std::string price = Utility::getNumericInput("Enter the new price of the menu item: ", "Invalid input. Enter a numeric value for the price.");
    std::string category = getValidatedInput("Enter the new category of the menu item (Breakfast, Lunch, Dinner): ", "Not a valid input.", isValidCategory);
    std::string availability = Utility::getBinaryInput("Is the menu item available now? (1 for Yes, 0 for No): ", "Invalid input. Enter 1 for Yes or 0 for No.");
    std::string type = getValidatedInput("Enter the new type of the menu item (Vegetarian, Non Vegetarian, Eggetarian): ", "Not a valid input.", isValidType);
    std::string spiceLevel = getValidatedInput("Enter the new spice level of the menu item (High, Medium, Low): ", "Not a valid input.", isValidSpiceLevel);
    std::string cuisine = getValidatedInput("Enter the new cuisine of the menu item (North Indian, South Indian, Other): ", "Not a valid input.", isValidCuisine);
    std::string isSweet = Utility::getBinaryInput("Is the menu item sweet? (1 for Yes, 0 for No): ", "Invalid input. Enter 1 for Yes or 0 for No.");

    std::string request = "updateMenuItem:" + name + "\n" + price + "\n" + availability + "\n" + description + "\n" + category + "\n" + type + "\n" + spiceLevel + "\n" + cuisine + "\n" + isSweet + "\0";

    sendRequest(request);

    std::string response = receiveResponse();
    std::cout << "Server response: " << response << std::endl;
}

void Admin::viewAllMenuItems()
{
    std::string request = "showAllMenuItems";
    sendRequest(request);
    std::string response = receiveResponse();
    std::cout << "Server response:" << std::endl;
    std::cout << response << std::endl;
}
