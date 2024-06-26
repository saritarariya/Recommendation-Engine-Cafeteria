#include "Admin.h"

Admin::Admin(Client*client) {
   this->client = client;
}

void Admin::showOptions() {
        std::cout << "\nAdmin Menu:" <<  std::endl;
        std::cout << "1. Add a menu item" << std::endl;
        std::cout << "2. Delete a menu item" <<  std::endl;
        std::cout << "3. Update a menu item" <<  std::endl;
        std::cout << "4. View all menu items" <<  std::endl;
        std::cout << "5. Exit" <<  std::endl;
        std::cout << "Enter your choice: ";
}




void Admin::clearInputBuffer() {
    // Clear the input buffer until a newline character is found
    while (std::cin.peek() != '\n' && std::cin.peek() != EOF) {
        std::cin.ignore(1);
    }
}
    

void Admin::addMenuItem(DatabaseManager* dbManager) {
    std::string name, description, category;
    double price;
    bool availability;
    std::cout << "Enter the name of the menu item: ";
    // Input for name
    while (true) {
        std::cin.ignore(1, '\n');
        std::getline(std::cin, name);

        if (!name.empty()) {
            break;
        }
        std::cout << "Name cannot be blank. Enter the name of the menu item: ";
    }

    std::cout << "Enter the description of the menu item: ";
     while (true) {
        std::getline(std::cin, description);

        if (!description.empty()) {
            break;
        }

        std::cout << "description cannot be blank. Enter the description of the menu item: ";
    }

    std::cout << "Enter the price of the menu item: ";
    while (!(std::cin >> price)) {
        std::cin.clear(); 
        std::cout << "Invalid input. Enter a valid price: ";
        clearInputBuffer();
    }
    clearInputBuffer();

    std::cout << "Enter the category of the menu item: ";
    while (true) {
        std::cin.ignore(1, '\n');
        std::getline(std::cin, category);
        if (!category.empty()) {
            break;
        }
        std::cout << "Category cannot be blank. Enter the category of the menu item: ";
    }

    std::cout << "Is the menu item available? (1 for Yes, 0 for No): ";
    while (!(std::cin >> availability) || (availability != 0 && availability != 1)) {
        std::cin.clear(); // Clear error flags
        std::cout << "Invalid input. Enter 1 for Yes or 0 for No: ";
        clearInputBuffer(); // Call custom function to clear input buffer
    }
    clearInputBuffer(); // Call again to clear the newline character

    // Add menu item to database
    bool success = dbManager->addMenuItem(name, description, price, category, availability);

    if (success) {
        std::cout << "Menu item '" << name << "' added successfully!" << std::endl;
    } else {
        std::cerr << "Failed to add menu item '" << name << "'. Please try again." << std::endl;
    }
}



void Admin::adminFunctions(DatabaseManager* dbManager) {
    int choice;
    while (true) {
        showOptions();
        while (!( std::cin >> choice) || (choice < 1 || choice > 5)) {
             std::cin.clear();
             while (std::cin.get() != '\n'); 
             std::cout << "Invalid input. Enter a valid choice: ";
        }
        switch (choice) {
            case 1:
                addMenuItem(dbManager);
                break;
            case 2: 
                deleteMenuItem(dbManager);
                break;
            case 3:
                updateMenuItem(dbManager);
                break;
            case 4:
                dbManager->showAllMenuItems();
                break;
            case 5:
                return;
        }
    }
}

void Admin::deleteMenuItem(DatabaseManager* dbManager) {
    std::string name;
    std::cout << "Enter the name of the menu item to delete: ";
    while (std::cin.get() != '\n'); 
    std::getline(std::cin, name);
    bool success = dbManager->deleteMenuItem(name);
    if (success) {
        std::cout << "Menu item '" << name << "' deleted successfully!" << std::endl;
    } else {
        std::cerr << "Failed to delete menu item '" << name << "'. Please try again." << std::endl;
    }
}

void Admin::updateMenuItem(DatabaseManager* dbManager) {
    std::string name;
    double price;
    bool availability;

    std::cout << "Enter the name of the menu item to update: ";
     while (true) {
        std::cin.ignore(1, '\n');
        std::getline(std::cin, name);

        if (!name.empty()) {
            break;
        }
        std::cout << "Name cannot be blank. Enter the name of the menu item: ";
    }

    std::cout << "Enter the new price of the menu item: ";
    while (!(std::cin >> price)) {
        std::cin.clear(); 
        std::cout << "Invalid input. Enter a valid price: ";
        clearInputBuffer();
    }
    clearInputBuffer();

    std::cout << "Is the menu item available? (1 for Yes, 0 for No): ";
    while (!(std::cin >> availability) || (availability != 0 && availability != 1)) {
        std::cin.clear();
        while (!(std::cin >> availability));
        std::cout << "Invalid input. Enter 1 for Yes or 0 for No: ";
    }
    if (dbManager->updateMenuItem(name, price, availability)) {
        std::cout << "Menu item '" << name << "' updated successfully!" << endl;
    } else {
        std::cerr << "Failed to update menu item '" << name << "'. Please try again." << endl;
    }
}