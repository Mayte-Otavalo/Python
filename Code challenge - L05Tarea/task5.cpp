#include <iostream>
#include <vector>
#include <string>

// ______________________ ADD ITEM FUNCTION __________________________________

void addItem(std::vector<std::string>& cart, const std::string& item) {
    cart.push_back(item);
    std::cout << "Added to cart: " << item << std::endl;
}


// ______________________ DISPLAY CART FUNCTION __________________________________

void displayCart(const std::vector<std::string>& cart) {
    if (cart.empty()) {
        std::cout << "The cart is empty.\n";
        return;
    }

    std::cout << "Items in customer cart:\n";
    for (const auto& item : cart) {
        std::cout << "- " << item << "\n";
    }
}

int main() {
    std::vector<std::string> customerCart;
    int choice;
    std::string item;

    do {
        std::cout << "\n_____ CUSTOMER CART _____\n";
        std::cout << "1. Add Item\n";
        std::cout << "2. View Cart\n";
        std::cout << "3. Exit\n";
        std::cout << "Enter option: ";
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
            case 1:
                std::cout << "Enter item name: ";
                std::getline(std::cin, item);
                addItem(customerCart, item);
                break;
            case 2:
                displayCart(customerCart);
                break;
            case 3:
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 3);

    return 0;
}
