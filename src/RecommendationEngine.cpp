#include "RecommendationEngine.h"
#include <algorithm>

void RecommendationEngine::addFeedback(int feedbackId, int userId, int foodItemId, int rating, const std::string& comment, const std::string& createdAt) {
    feedbacks.emplace_back(feedbackId, userId, foodItemId, rating, comment, createdAt);
}

std::vector<int> RecommendationEngine::getTopFoodItems() const {
    std::unordered_map<int, std::pair<int, int>> food_stats;

    for (const auto& feedback : feedbacks) {
        int foodItemId = feedback.getFoodItemId();

        if (food_stats.find(foodItemId) == food_stats.end()) {
            food_stats[foodItemId] = std::make_pair(0, 0);
        }

        int sentiment_score = feedback.calculateSentimentScore();

        food_stats[foodItemId].first += feedback.getRating() + sentiment_score;
        food_stats[foodItemId].second++;
    }

    std::vector<std::pair<int, double>> sorted_food_items;
    for (const auto& entry : food_stats) {
        double average_score = static_cast<double>(entry.second.first) / entry.second.second;
        sorted_food_items.emplace_back(entry.first, average_score);
    }

    std::sort(sorted_food_items.begin(), sorted_food_items.end(), [](auto &left, auto &right) {
        return left.second > right.second;
    });

    std::vector<int> top_food_items;
    int count = 0;
    for (const auto& item : sorted_food_items) {
        top_food_items.push_back(item.first);
        if (++count >= 5) break;
    }

    return top_food_items;
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