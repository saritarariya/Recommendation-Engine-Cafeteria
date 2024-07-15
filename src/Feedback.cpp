#include "Feedback.h"
#include <sstream>
#include <unordered_set>

std::unordered_set<std::string> positive_words = {
    "delicious", "tasty", "flavorful", "perfect", "excellent", "good"
};

std::unordered_set<std::string> negative_words = {
    "bland", "soggy", "oily", "overcooked", "dry", "bitter"
};

Feedback::Feedback(int feedbackId, int userId, int foodItemId, int rating, const std::string& comment, const std::string& createdAt)
    : feedbackId(feedbackId), userId(userId), foodItemId(foodItemId), rating(rating), comment(comment), createdAt(createdAt) {}

int Feedback::getFeedbackId() const {
    return feedbackId;
}

int Feedback::getUserId() const {
    return userId;
}

int Feedback::getFoodItemId() const {
    return foodItemId;
}

int Feedback::getRating() const {
    return rating;
}

std::string Feedback::getComment() const {
    return comment;
}

std::string Feedback::getCreatedAt() const {
    return createdAt;
}

int Feedback::calculateSentimentScore() const {
    int sentiment_score = 0;
    std::istringstream iss(comment);
    std::string word;
    while (iss >> word) {
        if (positive_words.count(word)) {
            sentiment_score++;
        } else if (negative_words.count(word)) {
            sentiment_score--;
        }
    }
    return sentiment_score;
}
