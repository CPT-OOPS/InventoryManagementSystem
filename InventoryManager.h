#ifndef INVENTORY_MANAGER_H
#define INVENTORY_MANAGER_H

#include "InventoryItem.h"
#include <map>
#include <string>

class InventoryManager {
private:
    std::map<int, InventoryItem> items;
    std::string filename;

public:
    explicit InventoryManager(const std::string& file = "inventory.csv");

    void addItem(const InventoryItem& item);
    void displayAll() const;
    void searchItem(int id) const;
    void updateItem(int id, const std::string& newName, double newPrice);
    void stockIn(int id, int amount);
    void stockOut(int id, int amount);
    void deleteItem(int id);
    void saveToFile() const;
    void loadFromFile();
};

#endif
