#include <iostream>

void printAll() {
    std::cout << std::endl;  
}

template <typename T, typename... Args>
void printAll(T first, Args... args) {
    std::cout << first;           
    if constexpr (sizeof...(args) > 0) {
        std::cout << " ";         
        printAll(args...);        
    } else {
        std::cout << std::endl;   
    }
}

int main() {
    std::cout << "\n___________Variadic Templates__________ \n";

    printAll(2, 4, 6);                          // Integers
    printAll(2.22, 2.777, 1.666);               // Doubles
    printAll("adkfl", "jaksjk", "aksk", "jakd");  // Strings
    printAll('X', 42, "mix", 3.14, true) ;       // Mixed types
    
    return 0;
}