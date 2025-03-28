#include <iostream>
#include <string>
#include <algorithm> // std::max

template <typename T>  
T maxValue(T a, T b) {
    return std::max(a, b); 
}

//__________Overload a Template Function_______________

template <typename T>  
T maxValue(T a, T b, T c) {
    return maxValue(a, maxValue(b, c));  
}

int main() {
    std::cout << "___________Maximum value_________\n";

    // Comparación de enteros
    int num1 = 10, num2 = 20, num3 = 200;
    std::cout << "\nMaximum value (int) between " << num1 << ", " << num2 
              << " and " << num3 << " is: " << maxValue(num1, num2, num3) << std::endl;

    // Comparación de doubles
    double d1 = 0.23, d2 = 0.0023, d3 = 0.00233;
    std::cout << "Maximum value (double) between " << d1 << ", " << d2 
              << " and " << d3 << " is: " << maxValue(d1, d2, d3) << std::endl;

    // Comparación de strings
    std::string c1 = "Xkdk", c2 = "kdkdk", c3 = "kdkdkkjj";
    std::cout << "Maximum value (string) between '" << c1 << "', '" << c2 
              << "' and '" << c3 << "' is: '" << maxValue(c1, c2, c3) << "'\n" << std::endl;

    return 0;
}