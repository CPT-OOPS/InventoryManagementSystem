#include "InventoryItem.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <stdexcept>

InventoryItem::InventoryItem() : id(0), name(""), quantity(0), price(0.0) {}

InventoryItem::InventoryItem(int itemId, const std::string& itemName,
                             int itemQuantity, double itemPrice)
    : id(itemId), name(itemName), quantity(itemQuantity), price(itemPrice) {
    if (id <= 0) throw std::invalid_argument("ID must be positive.");
    if (name.empty()) throw std::invalid_argument("Name cannot be empty.");
    if (quantity < 0) throw std::invalid_argument("Quantity cannot be negative.");
    if (price < 0) throw std::invalid_argument("Price cannot be negative.");
}

int InventoryItem::getId() const { return id; }
const std::string& InventoryItem::getName() const { return name; }
int InventoryItem::getQuantity() const { return quantity; }
double InventoryItem::getPrice() const { return price; }

void InventoryItem::setName(const std::string& newName) {
    if (newName.empty()) throw std::invalid_argument("Name cannot be empty.");
    name = newName;
}

void InventoryItem::setPrice(double newPrice) {
    if (newPrice < 0) throw std::invalid_argument("Price cannot be negative.");
    price = newPrice;
}

void InventoryItem::addStock(int amount) {
    if (amount <= 0) throw std::invalid_argument("Stock-in amount must be positive.");
    quantity += amount;
}

void InventoryItem::removeStock(int amount) {
    if (amount <= 0) throw std::invalid_argument("Stock-out amount must be positive.");
    if (amount > quantity) throw std::runtime_error("Insufficient stock.");
    quantity -= amount;
}

void InventoryItem::display() const {
    std::cout << std::left << std::setw(8) << id
              << std::setw(24) << name
              << std::setw(12) << quantity
              << "Rs. " << std::fixed << std::setprecision(2) << price << '\n';
}

std::string InventoryItem::toCSV() const {
    std::ostringstream out;
    out << id << ',' << name << ',' << quantity << ',' << price;
    return out.str();
}
