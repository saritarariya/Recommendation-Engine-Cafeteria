#include "Employee.h"

void Employee::viewNotifications() {
    std::string request = "viewNotifications:";
    sendRequest(request);
    std::string response = receiveResponse();
    std::cout << "Server response:" << std::endl;
    std::cout << response << std::endl;
}

void Employee::provideFeedback() {
    int foodItemId, rating;
    std::string comment;

    std::cout << "Enter Food Item ID: ";
    std::cin >> foodItemId;
    std::cout << "Enter Rating (1-5): ";
    std::cin >> rating;
    std::cin.ignore(); 
    std::cout << "Enter Comment: ";
    std::getline(std::cin, comment);

    std::ostringstream oss;
    oss << "provideFeedback:" << foodItemId << "," << rating << "," << comment;
    std::string request = oss.str();
    sendRequest(request);
    std::string response = receiveResponse();
    std::cout << "Server response:" << std::endl;
    std::cout << response << std::endl;
}

void Employee::voteForFoodItems() {
    std::string request = "viewNotifications:";
    sendRequest(request);
    std::string response = receiveResponse();

    std::vector<std::string> notifications;
    std::istringstream iss(response);
    std::string line;
    while (std::getline(iss, line))
    {
        notifications.push_back(line);
    }
    for (const auto &notification : notifications) {
        if (notification.find("Rolled out food items:") != std::string::npos) {
            std::cout << "Rolled out food items: " << notification << std::endl;

            std::istringstream iss(notification.substr(21));
            std::string foodItem;
            std::vector<std::string> foodItems;

            while (std::getline(iss, foodItem, ',')) {
                foodItems.push_back(foodItem);
            }

            for (size_t i = 0; i < foodItems.size(); ++i) {
                std::cout << i + 1 << ". " << foodItems[i] << std::endl;
            }

            std::cout << "Enter the number of the food item to vote for: ";
            int itemChoice;
            std::cin >> itemChoice;

            if (itemChoice >= 1 && itemChoice <= foodItems.size()) {
                 std::string request1 = "getFoodItemId:" + foodItems[itemChoice];
                 sendRequest(request1);
                 std::string foodItemIdStr = receiveResponse();
                 int foodItemId = std::stoi(foodItemIdStr);
                std::ostringstream oss;
                std::string request = "getID:";
                sendRequest(request);
                std::string userID = receiveResponse();
                oss << "submitVote:" << userID << "," << foodItemId << ",1";
                std::string request2 = oss.str();
                sendRequest(request2);
                std::string response = receiveResponse();
                std::cout << "Server response: " << response << std::endl;
            } else {
                std::cout << "Invalid choice." << std::endl;
            }
        }
    }
    std::cout<<"Chef have not rolled out food items\n";
}

void Employee::performRoleFunctions() {
    int choice;
    do {
        std::cout << "Please choose an operation:" << std::endl;
        std::cout << "1. Provide Feedback" << std::endl;
        std::cout << "2. Choose Food Items for Next Day" << std::endl;
        std::cout << "3. View Notifications" << std::endl;
        std::cout << "4. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            provideFeedback();
            break;
        case 2:
            voteForFoodItems();
            break;
        case 3:
            viewNotifications();
            break;
        case 4:
            std::cout << "Exiting..." << std::endl;
            break;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
            break;
        }
    } while (choice != 5);
}

void Employee::viewAllMenuItems()
{
    std::string request = "showAllMenuItems";
    sendRequest(request);
    std::string response = receiveResponse();
    std::cout << "Server response:" << std::endl;
    std::cout << response << std::endl;
}