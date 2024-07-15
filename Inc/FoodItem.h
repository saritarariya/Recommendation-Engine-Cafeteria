#include <string>

class FoodItem {
private:
    int foodItemId;
    std::string foodItemName;
    std::string description;
    double price;
    std::string category;
    bool availability;
    std::string type;
    std::string spiceLevel;
    std::string cuisine;
    bool isSweet;
public:
    FoodItem(const std::string& name, const std::string& desc, double price,
         const std::string& category, bool avail, const std::string& type,
         const std::string& spice, const std::string& cuisine, bool isSweet);

    int getFoodItemId() const;
    std::string getFoodItemName() const;
    std::string getDescription() const;
    double getPrice() const;
    std::string getCategory() const;
    bool isAvailable() const;
    std::string getType() const;
    std::string getSpiceLevel() const;
    std::string isFoodSweet() const;
    std::string getCuisine() const;
};
