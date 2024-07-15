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
    void addFeedback(int feedbackId, int userId, int foodItemId, int rating, const std::string& comment, const std::string& createdAt);
    std::vector<int> getTopFoodItems() const;
    void parseAndAddFeedbacks(const std::string& feedbackData);
};
#endif
