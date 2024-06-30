#ifndef FEEDBACK_H
#define FEEDBACK_H

#include <string>

class Feedback {
private:
    int feedbackId;
    std::string menuItemName;
    std::string feedback_date;
    int rating;
    std::string comments;
    std::string email;

public:
    Feedback(int id, const std::string& name, const std::string& date, int rate, const std::string& com, const std::string& mail);

    int getFeedbackId() const;
    std::string getMenuItemName() const;
    std::string getFeedbackDate() const;
    int getRating() const;
    std::string getComments() const;
    std::string getEmail() const;

    int calculateSentimentScore() const;
};

#endif 