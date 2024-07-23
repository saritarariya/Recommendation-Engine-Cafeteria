#include "RecommendationEngine.h"
#include <algorithm>

void RecommendationEngine::addFeedback(int feedbackId, int userId, int foodItemId, int rating, const std::string& comment, const std::string& createdAt) {
    feedbacks.emplace_back(feedbackId, userId, foodItemId, rating, comment, createdAt);
}

std::vector<int> RecommendationEngine::getTopFoodItems() const {
    std::unordered_map<int, std::pair<int, int>> foodStats;

    for (const auto& feedback : feedbacks) {
        int foodItemId = feedback.getFoodItemId();

        if (foodStats.find(foodItemId) == foodStats.end()) {
            foodStats[foodItemId] = std::make_pair(0, 0);
        }

        int sentimentScore = feedback.calculateSentimentScore();

        foodStats[foodItemId].first += feedback.getRating() + sentimentScore;
        foodStats[foodItemId].second++;
    }

    std::vector<std::pair<int, double>> sortedFoodItems;
    for (const auto& entry : foodStats) {
        double average_score = static_cast<double>(entry.second.first) / entry.second.second;
        sortedFoodItems.emplace_back(entry.first, average_score);
    }

    std::sort(sortedFoodItems.begin(), sortedFoodItems.end(), [](auto &left, auto &right) {
        return left.second > right.second;
    });

    std::vector<int> topFoodItems;
    int count = 0;
    for (const auto& item : sortedFoodItems) {
        topFoodItems.push_back(item.first);
        if (++count >= 5) break;
    }
    return topFoodItems;
}

void RecommendationEngine::parseAndAddFeedbacks(const std::string& feedbackData) {
    std::istringstream iss(feedbackData);
    std::string line;
    int feedbackId, userId, foodItemId, rating;
    std::string comment, createdAt;

    while (std::getline(iss, line)) {
        feedbackId = std::stoi(line); 
        std::getline(iss, line);
        userId = std::stoi(line); 
        std::getline(iss, line);
        foodItemId = std::stoi(line); 
        std::getline(iss, line);
        rating = std::stoi(line);
        std::getline(iss, comment);
        std::getline(iss, createdAt);
        addFeedback(feedbackId, userId, foodItemId, rating, comment, createdAt);
    }
}

std::vector<int> RecommendationEngine::getItemsToDiscard() const
{
    std::vector<int>discardMenuItemsID;
    for (const auto& feedback : feedbacks) 
    {
        if(feedback.checkIsItemCanBeDiscarded())
        {
            int foodItemID = feedback.getFoodItemId();
            discardMenuItemsID.push_back(foodItemID);
        }
    }
    return discardMenuItemsID;
}