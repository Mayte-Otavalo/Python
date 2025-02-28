#include <iostream>
#include <map>

//________________________ DISPLAY ALL PRODUCTS_________________________________

void displayInventory(const std::map<std::string, int>& inventory) {
    std::cout << "\nCurrent Inventory:\n";
    for (const auto& item : inventory) {
        std::cout << item.first << ": " << item.second << " in stock\n";
    }
    std::cout << std::endl;
}


// ______________________ NEW PRODUCT FUNCTION __________________________________


void newproduct(std::map<std::string, int>& inventory) {
    std::string product;
    int volume;

    std::cout << "\nProduct name: ";
    std::cin >> product;
    
    if (inventory.find(product) != inventory.end()) {
        std::cout << "Go to Update product\n";
        return;
    }

    std::cout << "Volume: ";
    std::cin >> volume;


    inventory[product] = volume;
    std::cout << "\n_AGGREGATE_\n\nProduct name: " << product << "\nVolume: " << volume << ".\n";
}

//__________________________UPDATE THE QUANTITY OF A PRODUCT ____________________________


void updateProduct(std::map<std::string, int>& inventory) {
    std::string product;
    int volume;

    std::cout << "Product to update (name): ";
    std::cin >> product;

    if (inventory.find(product) == inventory.end()) {
        std::cout << "Go to Add a new product\n";
        return;
    }

    std::cout << "Volume: ";
    std::cin >> volume;

    inventory[product] = volume;
    std::cout << "Product " << product << "  " << volume<< ".\n";
}

int main() {
    std::map<std::string, int> inventory;

    inventory["Laptop"] = 5;
    inventory["Mouse"] = 20;
    inventory["Keyboard"] = 10;

    int choice;
    do {
        std::cout << "\n______INVENTORY MANAGEMENT______\n\n";
        std::cout << "1. Add a new product\n";
        std::cout << "2. Update quantity of a product\n";
        std::cout << "3. Show inventory\n";
        std::cout << "4. Exit\n";
        std::cout << "\nEnter the number of the option you require: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                newproduct(inventory);
                break;
            case 2:
                updateProduct(inventory);
                break;
            case 3:
                displayInventory(inventory);
                break;
            case 4:
                std::cout << "Exit.\n";
                break;
            default:
                std::cout << "Error\n";
        }
    } while (choice != 4);

    return 0;
}
