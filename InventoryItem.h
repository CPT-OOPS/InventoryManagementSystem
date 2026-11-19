#ifndef INVENTORY_ITEM_H
#define INVENTORY_ITEM_H

#include <string>

class InventoryItem {
private:
    int id;
    std::string name;
    int quantity;
    double price;

public:
    InventoryItem();
    InventoryItem(int id, const std::string& name, int quantity, double price);

    int getId() const;
    const std::string& getName() const;
    int getQuantity() const;
    double getPrice() const;

    void setName(const std::string& newName);
    void setPrice(double newPrice);
    void addStock(int amount);
    void removeStock(int amount);
    void display() const;
    std::string toCSV() const;
};

#endif
