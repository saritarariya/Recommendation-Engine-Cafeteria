#ifndef FEEDBACK_H
#define FEEDBACK_H

#include <string>

class Feedback {

private:
    int feedbackId;
    int userId;
    int foodItemId;
    int rating;
    std::string comment;
    std::string createdAt;

public:
    Feedback(int feedbackId, int userId, int foodItemId, int rating, const std::string& comment, const std::string& createdAt);
    int getFeedbackId() const;
    int getUserId() const;
    int getFoodItemId() const;
    int getRating() const;
    std::string getComment() const;
    std::string getCreatedAt() const;
    int calculateSentimentScore() const;
    bool checkIsItemCanBeDiscarded() const;
};

#endif // FEEDBACK_H
