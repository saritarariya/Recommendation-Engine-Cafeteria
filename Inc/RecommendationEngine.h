#ifndef RECOMMENDATION_ENGINE_H
#define RECOMMENDATION_ENGINE_H

#include "Feedback.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <unordered_map>

class RecommendationEngine {
private:
    std::vector<Feedback> feedbacks;

public:
    void addFeedback(int id, const std::string& name, const std::string& date, int rate, const std::string& com, const std::string& mail);
    std::vector<std::string> getTopFoodItems() const;
    void parseAndAddFeedbacks(const std::string& feedbackData);
};

#endif
