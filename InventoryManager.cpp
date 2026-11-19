#include "InventoryManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <stdexcept>

InventoryManager::InventoryManager(const std::string& file) : filename(file) {}

void InventoryManager::addItem(const InventoryItem& item) {
    if (items.count(item.getId()))
        throw std::runtime_error("An item with this ID already exists.");
    items.emplace(item.getId(), item);
}

void InventoryManager::displayAll() const {
    if (items.empty()) {
        std::cout << "Inventory is empty.\n";
        return;
    }
    std::cout << std::left << std::setw(8) << "ID"
              << std::setw(24) << "Item Name"
              << std::setw(12) << "Quantity" << "Price\n";
    std::cout << std::string(58, '-') << '\n';
    for (const auto& entry : items) entry.second.display();
}

void InventoryManager::searchItem(int id) const {
    auto it = items.find(id);
    if (it == items.end()) throw std::runtime_error("Item ID not found.");
    std::cout << std::left << std::setw(8) << "ID"
              << std::setw(24) << "Item Name"
              << std::setw(12) << "Quantity" << "Price\n";
    it->second.display();
}

void InventoryManager::updateItem(int id, const std::string& newName, double newPrice) {
    auto it = items.find(id);
    if (it == items.end()) throw std::runtime_error("Item ID not found.");
    it->second.setName(newName);
    it->second.setPrice(newPrice);
}

void InventoryManager::stockIn(int id, int amount) {
    auto it = items.find(id);
    if (it == items.end()) throw std::runtime_error("Item ID not found.");
    it->second.addStock(amount);
}

void InventoryManager::stockOut(int id, int amount) {
    auto it = items.find(id);
    if (it == items.end()) throw std::runtime_error("Item ID not found.");
    it->second.removeStock(amount);
}

void InventoryManager::deleteItem(int id) {
    if (items.erase(id) == 0) throw std::runtime_error("Item ID not found.");
}

void InventoryManager::saveToFile() const {
    std::ofstream out(filename);
    if (!out) throw std::runtime_error("Could not open inventory file for writing.");
    for (const auto& entry : items) out << entry.second.toCSV() << '\n';
    if (!out) throw std::runtime_error("Error while writing inventory file.");
}

void InventoryManager::loadFromFile() {
    std::ifstream in(filename);
    if (!in) return; // First run: file does not exist yet.

    std::map<int, InventoryItem> loaded;
    std::string line;
    int lineNumber = 0;

    while (std::getline(in, line)) {
        ++lineNumber;
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string idText, name, quantityText, priceText, extra;
        if (!std::getline(ss, idText, ',') ||
            !std::getline(ss, name, ',') ||
            !std::getline(ss, quantityText, ',') ||
            !std::getline(ss, priceText, ',') ||
            std::getline(ss, extra, ',')) {
            throw std::runtime_error("Malformed CSV record on line " + std::to_string(lineNumber));
        }

        try {
            int id = std::stoi(idText);
            int quantity = std::stoi(quantityText);
            double price = std::stod(priceText);
            InventoryItem item(id, name, quantity, price);
            if (loaded.count(id)) throw std::runtime_error("Duplicate ID");
            loaded.emplace(id, item);
        } catch (const std::exception&) {
            throw std::runtime_error("Invalid CSV record on line " + std::to_string(lineNumber));
        }
    }
    items.swap(loaded);
}
