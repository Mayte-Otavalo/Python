#include <iostream>
#include <stack>
#include <string>
#include <limits>

// ______________________ ADD RESTOCK FUNCTION __________________________________


void addRestock(std::stack<std::pair<std::string, int>>& restocks) {
    std::string item;
    int quantity;

    std::cout << "Enter product name: ";
    std::cin >> item;
    
    std::cout << "Enter quantity: ";
    while (!(std::cin >> quantity)) { 
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Enter a valid integer for quantity: ";
    }

    restocks.push({item, quantity});
    std::cout << "Restock batch added: " << item << " (" << quantity << " units)\n";
}

// ______________________ PROCESS RESTOCK FUNCTION __________________________________

void processRestock(std::stack<std::pair<std::string, int>>& restocks) {
    if (restocks.empty()) {
        std::cout << "No restock batches to process.\n";
        return;
    }

    auto item = restocks.top();
    std::cout << "Restocking " << item.second << " units of " << item.first << std::endl;
    restocks.pop();
}

int main() {
    std::stack<std::pair<std::string, int>> restocks;

    restocks.push({"Mouse", 10});
    restocks.push({"Laptop", 2});
    restocks.push({"Keyboard", 5});

    int choice;
    do {
        std::cout << "\n_____ RESTOCK MANAGEMENT _____\n";
        std::cout << "1. Add Restock Batch\n";
        std::cout << "2. Process Restock Batch\n";
        std::cout << "3. Exit\n";
        std::cout << "Enter option: ";
        std::cin >> choice;

        if (std::cin.fail()) { 
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Try again.\n";
            continue;
        }

        switch (choice) {
            case 1:
                addRestock(restocks);
                break;
            case 2:
                processRestock(restocks);
                break;
            case 3:
                std::cout << "Exiting\n";
                break;
            default:
                std::cout << "Invalid, try again.\n";
        }
    } while (choice != 3);

    return 0;
}
