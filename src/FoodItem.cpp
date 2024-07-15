#include "FoodItem.h"

FoodItem::FoodItem(const std::string& name, const std::string& desc, double price,
           const std::string& category, bool avail, const std::string& type,
           const std::string& spice, const std::string& cuisine, bool isSweet)
    : foodItemName(name), description(desc), price(price),
      category(category), availability(avail), type(type), spiceLevel(spice), cuisine(cuisine), isSweet(isSweet){
}

int FoodItem::getFoodItemId() const {
    return foodItemId;
}

std::string FoodItem::getFoodItemName() const {
    return foodItemName;
}

std::string FoodItem::getDescription() const {
    return description;
}

double FoodItem::getPrice() const {
    return price;
}

std::string FoodItem::getCategory() const {
    return category;
}

bool FoodItem::isAvailable() const {
    return availability;
}

std::string FoodItem::getType() const {
    return type;
}

std::string FoodItem::getSpiceLevel() const {
    return spiceLevel;
}

std::string FoodItem::isFoodSweet() const {
  std::string result = "No";
  if(isSweet)
  {
    result = "Yes";
  }
  return result;
}

std::string FoodItem::getCuisine() const {
  return cuisine;
}