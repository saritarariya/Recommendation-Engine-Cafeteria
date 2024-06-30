
#include "Chef.h"

void Chef::performRoleFunctions() 
{
    std::cout << "Please choose an operation:" << std::endl;
    std::cout << "1. Provide Feedback" << std::endl;
    std::cout << "2. Choose Food Items for Next Day" << std::endl;
    std::cout << "3. Provide Rating" << std::endl;
    std::cout << "4. Get Food Items for Next Day" << std::endl;
    std::cout << "Enter your choice: ";
}

std::vector<std::string> Chef::getFoodItemsToRollOut() 
{
    std::vector<std::string> topFoodItems;
    RecommendationEngine engine;
    std::string request = "getAllFeedbacks:";
    sendRequest(request);
    std::string response = receiveResponse();
    engine.parseAndAddFeedbacks(response);
    topFoodItems = engine.getTopFoodItems();
    std::cout << "Top 5 Recommended Food Items:" << std::endl;
    for (size_t i = 0; i < topFoodItems.size() && i < 5; ++i) {
        std::cout << i + 1 << ". " << topFoodItems[i] << std::endl;
    }
    return topFoodItems;
}

