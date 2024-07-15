#include "Admin.h"

void Admin::showOptions()
{
    std::cout << "\nAdmin Menu:" << std::endl;
    std::cout << "1. Add a menu item" << std::endl;
    std::cout << "2. Delete a menu item" << std::endl;
    std::cout << "3. Update a menu item" << std::endl;
    std::cout << "4. View all menu items" << std::endl;
    std::cout << "5. Exit" << std::endl;
    std::cout << "Enter your choice: ";
}

void Admin::clearInputBuffer()
{
    while (std::cin.peek() != '\n' && std::cin.peek() != EOF)
    {
        std::cin.ignore(1);
    }
}

void Admin::addMenuItem()
{
    std::string name, description, category, type, spiceLevel, cuisine;
    double price;
    bool availability, isSweet;

    std::cout << "Enter the name of the menu item: ";
    while (true)
    {
        std::cin.ignore(1, '\n');
        std::getline(std::cin, name);

        if (!name.empty())
        {
            break;
        }
        std::cout << "Name cannot be blank. Enter the name of the menu item: ";
    }

    std::cout << "Enter the description of the menu item: ";
    while (true)
    {
        std::getline(std::cin, description);

        if (!description.empty())
        {
            break;
        }
        std::cout << "Description cannot be blank. Enter the description of the menu item: ";
    }

    std::cout << "Enter the price of the menu item: ";
    while (!(std::cin >> price))
    {
        std::cin.clear();
        std::cout << "Invalid input. Enter a valid price: ";
        clearInputBuffer();
    }
    clearInputBuffer();

    std::cout << "Enter the category of the menu item (Breakfast, Lunch, Dinner): ";
    while (true)
    {
        std::cin.ignore(1, '\n');
        std::getline(std::cin, category);

        if (!category.empty())
        {
            break;
        }
        std::cout << "Category cannot be blank. Enter the category of the menu item: ";
    }

    std::cout << "Is the menu item available? (1 for Yes, 0 for No): ";
    while (!(std::cin >> availability) || (availability != 0 && availability != 1))
    {
        std::cin.clear();
        std::cout << "Invalid input. Enter 1 for Yes or 0 for No: ";
        clearInputBuffer();
    }
    clearInputBuffer();

    std::cout << "Enter the type of the menu item (Vegetarian, Non Vegetarian, Eggetarian): ";
    while (true)
    {
        std::cin.ignore(1, '\n');
        std::getline(std::cin, type);

        if (!type.empty())
        {
            break;
        }
        std::cout << "Type cannot be blank. Enter the type of the menu item: ";
    }

    std::cout << "Enter the spice level of the menu item (High, Medium, Low): ";
    while (true)
    {
        std::getline(std::cin, spiceLevel);

        if (!spiceLevel.empty())
        {
            break;
        }
        std::cout << "Spice level cannot be blank. Enter the spice level of the menu item: ";
    }

    std::cout << "Enter the cuisine of the menu item (North Indian, South Indian, Other): ";
    while (true)
    {
        std::getline(std::cin, cuisine);

        if (!cuisine.empty())
        {
            break;
        }
        std::cout << "Cuisine cannot be blank. Enter the cuisine of the menu item: ";
    }

    std::cout << "Is the menu item sweet? (1 for Yes, 0 for No): ";
    while (!(std::cin >> isSweet) || (isSweet != 0 && isSweet != 1))
    {
        std::cin.clear();
        std::cout << "Invalid input. Enter 1 for Yes or 0 for No: ";
        clearInputBuffer();
    }
    clearInputBuffer();

    std::string request = "addMenuItem:" + name + "\n" + description + "\n" + std::to_string(price) + "\n" + category + "\n" + std::to_string(availability) + "\n" + type + "\n" + spiceLevel + "\n" + cuisine + "\n" + std::to_string(isSweet) + '\0';

    sendRequest(request);

    std::string response = receiveResponse();
    if (response  == "Menu item added successfully")
    {
        std::cout << "Menu item " << name << " added successfully!" << std::endl;
    }
    else
    {
        std::cerr << "Failed to add menu item '" << name << "'. Please try again." << std::endl;
    }
}

void Admin::performRoleFunctions()
{
    int choice;
    while (true)
    {
        showOptions();
        while (!( std::cin >> choice) || (choice < 1 || choice > 5)) {
             std::cin.clear();
             while (std::cin.get() != '\n'); 
             std::cout << "Invalid input. Enter a valid choice: ";
        }
        switch (choice) {
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
            return;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }
}

void Admin::deleteMenuItem()
{
    std::string name;
    std::cout << "Enter the name of the menu item to delete: ";
    std::cin.ignore();
    std::getline(std::cin, name);
    std::string request = "deleteMenuItem:" + name;
    sendRequest(request);
    std::string response = receiveResponse();
    if (response == "Menu item deleted successfully") {
        std::cout << "Menu item '" << name << "' deleted successfully!" << std::endl;
    } else {
        std::cerr << "Failed to delete menu item '" << name << "'. Please try again." << std::endl;
    }
}

void Admin::updateMenuItem()
{
    std::string name, description, category, type, spiceLevel, cuisine;
    double price;
    bool availability, isSweet;

    std::cout << "Enter the name of the menu item to update: ";
    std::cin.ignore(); 
    std::getline(std::cin, name);

    std::cout << "Enter the new price of the menu item: ";
    while (!(std::cin >> price))
    {
        std::cin.clear();
        std::cout << "Invalid input. Enter a valid price: ";
        clearInputBuffer();
    }
    clearInputBuffer();

    std::cout << "Is the menu item available? (1 for Yes, 0 for No): ";
    while (!(std::cin >> availability) || (availability != 0 && availability != 1))
    {
        std::cin.clear();
        std::cout << "Invalid input. Enter 1 for Yes or 0 for No: ";
        clearInputBuffer();
    }
    clearInputBuffer();

    std::cout << "Enter the new description of the menu item: ";
    while (true)
    {
        std::cin.ignore(1, '\n');
        std::getline(std::cin, description);
        if (!description.empty())
        {
            break;
        }
        std::cout << "Description cannot be blank. Enter the description of the menu item: ";
    }

    std::cout << "Enter the new category of the menu item (Breakfast, Lunch, Dinner): ";
    while (true)
    {
        std::getline(std::cin, category);

        if (!category.empty())
        {
            break;
        }
        std::cout << "Category cannot be blank. Enter the category of the menu item: ";
    }

    std::cout << "Enter the new type of the menu item (Vegetarian, Non Vegetarian, Eggetarian): ";
    while (true)
    {
        std::getline(std::cin, type);

        if (!type.empty())
        {
            break;
        }
        std::cout << "Type cannot be blank. Enter the type of the menu item: ";
    }

    std::cout << "Enter the new spice level of the menu item (High, Medium, Low): ";
    while (true)
    {
        std::getline(std::cin, spiceLevel);

        if (!spiceLevel.empty())
        {
            break;
        }
        std::cout << "Spice level cannot be blank. Enter the spice level of the menu item: ";
    }

    std::cout << "Enter the new cuisine of the menu item (North Indian, South Indian, Other): ";
    while (true)
    {
        std::getline(std::cin, cuisine);

        if (!cuisine.empty())
        {
            break;
        }
        std::cout << "Cuisine cannot be blank. Enter the cuisine of the menu item: ";
    }

    std::cout << "Is the menu item sweet? (1 for Yes, 0 for No): ";
    while (!(std::cin >> isSweet) || (isSweet != 0 && isSweet != 1))
    {
        std::cin.clear();
        std::cout << "Invalid input. Enter 1 for Yes or 0 for No: ";
        clearInputBuffer();
    }
    clearInputBuffer();

    std::string request = "updateMenuItem:" + name + "\n" + std::to_string(price) + "\n" + (availability ? "1" : "0") + "\n" + description + "\n" + category + "\n" + type + "\n" + spiceLevel + "\n" + cuisine + "\n" + std::to_string(isSweet);

    if (this->client->clientSocket == INVALID_SOCKET)
    {
        std::cout << "Connection not valid\n";
        return;
    }

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

