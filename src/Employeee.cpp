#include "Employee.h"

Employee::Employee(Client*client) {
  this->client = client;
}

void Employee::performRoleFunctions() {
    std::cout << "Please choose an operation:" << std::endl;
    std::cout << "1. Provide Feedback" << std::endl;
    std::cout << "2. Choose Food Items for Next Day" << std::endl;
    std::cout << "3. Provide Rating" << std::endl;
    std::cout << "4. Get Food Items for Next Day" << std::endl;
    std::cout << "Enter your choice: ";
}
