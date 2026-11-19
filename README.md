# Inventory Management System — C++

**Student:** Rohan Pawar  
**Practical:** 12 — Mini Project: Console-Based Application

## Features
- Add, display, search, update and delete inventory items
- Stock-in and stock-out operations
- Prevent duplicate IDs, invalid quantities and negative stock
- Persist data in `inventory.csv`
- Input validation and exception handling

## Concepts demonstrated
- OOP: classes, objects, constructors and encapsulation
- STL: `std::map`
- File I/O: `std::ifstream` and `std::ofstream`
- Exception handling: `try`, `catch`, and standard exceptions

## Files
- `main.cpp`: menu and application flow
- `InventoryItem.h/.cpp`: product model and validation
- `InventoryManager.h/.cpp`: inventory operations and CSV storage
- `inventory.csv`: data file created on first save

## Compile (PowerShell / Windows)
```powershell
g++ -std=c++17 -Wall -Wextra main.cpp InventoryItem.cpp InventoryManager.cpp -o inventory.exe
```

## Run
```powershell
.\inventory.exe
```

Keep `inventory.csv` in the same working directory as the program. It is created automatically when you save or exit.
