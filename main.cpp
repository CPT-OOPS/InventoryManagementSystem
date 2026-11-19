#include "InventoryManager.h"
#include <iostream>
#include <limits>
#include <string>
#include <stdexcept>

void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int readInt(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            clearInput();
            return value;
        }
        std::cout << "Please enter a valid whole number.\n";
        clearInput();
    }
}

double readDouble(const std::string& prompt) {
    double value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            clearInput();
            return value;
        }
        std::cout << "Please enter a valid number.\n";
        clearInput();
    }
}

std::string readText(const std::string& prompt) {
    std::string value;
    std::cout << prompt;
    std::getline(std::cin, value);
    return value;
}

void showMenu() {
    std::cout << "\n========== INVENTORY MANAGEMENT SYSTEM ==========\n"
              << "Developed by: Rohan Pawar\n"
              << "1. Add item\n"
              << "2. Display all items\n"
              << "3. Search item\n"
              << "4. Update item\n"
              << "5. Stock in\n"
              << "6. Stock out\n"
              << "7. Delete item\n"
              << "8. Save inventory\n"
              << "0. Save and exit\n"
              << "=================================================\n";
}

int main() {
    InventoryManager inventory;

    try {
        inventory.loadFromFile();
        std::cout << "Welcome, Rohan Pawar. Inventory data loaded.\n";
    } catch (const std::exception& e) {
        std::cerr << "Could not load data: " << e.what() << '\n';
        return 1;
    }

    bool running = true;
    while (running) {
        showMenu();
        int choice = readInt("Enter your choice: ");

        try {
            switch (choice) {
                case 1: {
                    int id = readInt("Enter item ID: ");
                    std::string name = readText("Enter item name: ");
                    int quantity = readInt("Enter quantity: ");
                    double price = readDouble("Enter price: ");
                    inventory.addItem(InventoryItem(id, name, quantity, price));
                    std::cout << "Item added successfully.\n";
                    break;
                }
                case 2:
                    inventory.displayAll();
                    break;
                case 3:
                    inventory.searchItem(readInt("Enter item ID to search: "));
                    break;
                case 4: {
                    int id = readInt("Enter item ID to update: ");
                    std::string name = readText("Enter new item name: ");
                    double price = readDouble("Enter new price: ");
                    inventory.updateItem(id, name, price);
                    std::cout << "Item updated successfully.\n";
                    break;
                }
                case 5: {
                    int id = readInt("Enter item ID: ");
                    int amount = readInt("Enter quantity to add: ");
                    inventory.stockIn(id, amount);
                    std::cout << "Stock added successfully.\n";
                    break;
                }
                case 6: {
                    int id = readInt("Enter item ID: ");
                    int amount = readInt("Enter quantity to remove: ");
                    inventory.stockOut(id, amount);
                    std::cout << "Stock removed successfully.\n";
                    break;
                }
                case 7:
                    inventory.deleteItem(readInt("Enter item ID to delete: "));
                    std::cout << "Item deleted successfully.\n";
                    break;
                case 8:
                    inventory.saveToFile();
                    std::cout << "Inventory saved successfully.\n";
                    break;
                case 0:
                    inventory.saveToFile();
                    std::cout << "Data saved. Thank you, Rohan Pawar!\n";
                    running = false;
                    break;
                default:
                    std::cout << "Invalid menu choice. Try again.\n";
            }
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << '\n';
        }
    }
    return 0;
}
