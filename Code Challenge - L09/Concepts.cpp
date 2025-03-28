#include <concepts>
#include <iostream>

// _________Concept____________

template <typename T>
concept Numeric = std::integral<T> || std::floating_point<T>;

template <Numeric T>
T add(T a, T b) {
    return a + b;
}

int main() {
     std::cout << "\n___________Use of Concept__________ \n";
    std::cout << "\nInteger addition: " << add(5, 3) << std::endl;
    std::cout << "Double addition: " << add(3.14, 2.71) <<  "\n" << std::endl;
    
    
    return 0;
}