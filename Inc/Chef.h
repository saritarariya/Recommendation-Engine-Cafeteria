#ifndef HEADER_H_CHEF
#define HEADER_H_CHEF

#include "Client.h"
#include <string>

class Chef : public Client
{
    public:
    std::string mailID;
    std::string rollOutFoodItems();
    std::string getMonthlyReport(std::string foodItem);
    std::string getLastDayVoting();
    std::string getFoodItemsToRollOut();
    void showOptions();
};

#endif