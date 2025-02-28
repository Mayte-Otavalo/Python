#include <iostream>
#include <set>
#include <limits>

// _________________________ADD NEW CATEGORY_______________________
void addCategory(std::set<std::string>& categories) {
    std::string category;
    std::cout << "New category name: ";
    std::cin >> category;

    auto result = categories.insert(category);
    if (result.second) {
        std::cout << "Category '" << category << "' added successfully.\n";
    } else {
        std::cout << "Category '" << category << "' already exists.\n";
    }
}

// ____________________DISPLAY ALL CATEGORIES______________________
void showCategories(const std::set<std::string>& categories) {
    std::cout << "Product Categories:\n";
    for (const auto& category : categories) {
        std::cout << "- " << category << "\n";
    }
}

int main() {
    std::set<std::string> productCategories;

    // Adding some initial categories
    productCategories.insert("Electronics");
    productCategories.insert("Accessories");
    productCategories.insert("Peripherals");

    int choice;
    do {
        std::cout << "\n____CATEGORY MANAGEMENT_____\n";
        std::cout << "1. Add Category\n";
        std::cout << "2. Show Categories\n";
        std::cout << "3. Exit\n";
        std::cout << "Enter the number of the option you require: ";
        std::cin >> choice;

        if (std::cin.fail()) { // Validating non-numeric input
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a valid number.\n";
            continue;
        }

        switch (choice) {
            case 1:
                addCategory(productCategories);
                break;
            case 2:
                showCategories(productCategories);
                break;
            case 3:
                std::cout << "Exiting the program.\n";
                break;
            default:
                std::cout << "Error: Invalid option. Please try again.\n";
        }
    } while (choice != 3);

    return 0;
}
