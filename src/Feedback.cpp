#include "Feedback.h"
#include <sstream>
#include <unordered_set>


std::unordered_set<std::string> positive_words = {
    "delicious", "tasty", "flavorful", "perfect", "excellent", "good"
};

std::unordered_set<std::string> negative_words = {
    "bland", "soggy", "oily", "overcooked", "dry", "bitter"
};

Feedback::Feedback(int id, const std::string& name, const std::string& date, int rate, const std::string& com, const std::string& mail)
    : feedbackId(id), menuItemName(name), feedback_date(date), rating(rate), comments(com), email(mail) {}

int Feedback::getFeedbackId() const {
    return feedbackId;
}

std::string Feedback::getMenuItemName() const {
    return menuItemName;
}

std::string Feedback::getFeedbackDate() const {
    return feedback_date;
}

int Feedback::getRating() const {
    return rating;
}

std::string Feedback::getComments() const {
    return comments;
}

std::string Feedback::getEmail() const {
    return email;
}

int Feedback::calculateSentimentScore() const {
    int sentiment_score = 0;
    std::istringstream iss(comments);
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
