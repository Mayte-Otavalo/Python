#include <iostream>
#include <queue>
#include <string>
#include <limits>

// ______________________ NEW ORDER FUNCTION __________________________________

void addOrder(std::queue<std::string>& orders) {
    std::string order;
    std::cout << "Enter the order details: ";
    std::cin.ignore(); 
    std::getline(std::cin, order);

    orders.push(order);
    std::cout << "Added: " << order << std::endl;
}


// ______________________ PROCESS ORDER FUNCTION __________________________________

void processOrders(std::queue<std::string>& orders) {
    if (orders.empty()) {
        std::cout << "No orders to process.\n";
        return;
    }

    std::cout << "Processing " << orders.front() << std::endl;
    orders.pop();
}

int main() {
    std::queue<std::string> orders;

    
    orders.push("Order#1: Laptop");
    orders.push("Order#2: Mouse");
    orders.push("Order#3: Keyboard");

    int choice;
    do {
        std::cout << "\n______ORDER MANAGEMENT______\n\n";
        std::cout << "1. Add a new order\n";
        std::cout << "2. Process order\n";
        std::cout << "3. Exit\n";
        std::cout << "\nEnter the number of the option you require: ";
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();  
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  
            std::cout << "Invalid input! Please enter a number.\n";
            continue;
        }

        switch (choice) {
            case 1:
                addOrder(orders);
                break;
            case 2:
                processOrders(orders);
                break;
            case 3:                
                std::cout << "Exit.\n";
                break;
            default:
                std::cout << "Error: Invalid option. Please try again.\n";
        }
    } while (choice != 3);

    return 0;
}
