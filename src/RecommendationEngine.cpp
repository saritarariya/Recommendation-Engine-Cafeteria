#include "RecommendationEngine.h"
#include <algorithm>

void RecommendationEngine::addFeedback(int id, const std::string& name, const std::string& date, int rate, const std::string& com, const std::string& mail) {
    feedbacks.emplace_back(id, name, date, rate, com, mail);
}

std::vector<std::string> RecommendationEngine::getTopFoodItems() const {
    std::unordered_map<std::string, std::pair<int, int>> food_stats;

    for (const auto& feedback : feedbacks) {
        if (food_stats.find(feedback.getMenuItemName()) == food_stats.end()) {
            food_stats[feedback.getMenuItemName()] = std::make_pair(0, 0);
        }

        int sentiment_score = feedback.calculateSentimentScore();

        food_stats[feedback.getMenuItemName()].first += feedback.getRating() + sentiment_score;
        food_stats[feedback.getMenuItemName()].second++;
    }

    std::vector<std::pair<std::string, double>> sorted_food_items;
    for (const auto& entry : food_stats) {
        double average_score = static_cast<double>(entry.second.first) / entry.second.second;
        sorted_food_items.emplace_back(entry.first, average_score);
    }
    std::sort(sorted_food_items.begin(), sorted_food_items.end(), [](auto &left, auto &right) {
        return left.second > right.second;
    });

    std::vector<std::string> top_food_items;
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
    int id, rate;
    std::string name, date, com, mail;

    while (std::getline(iss, line)) {
        id = std::stoi(line);  // Convert string to int
        std::getline(iss, name);
        std::getline(iss, date);
        std::getline(iss, line);  // Read the rating line
        rate = std::stoi(line);  // Convert string to int
        std::getline(iss, com);
        std::getline(iss, mail);

        addFeedback(id, name, date, rate, com, mail);
    }
}
