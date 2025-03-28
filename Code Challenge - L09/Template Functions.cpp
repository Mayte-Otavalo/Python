#include <iostream>
#include <string>
//_____________Simple Template Function_______________
template <typename T>  
T maxValue(T a, T b) {
    return (a > b) ? a : b;  
}

int main() {
std::cout << "___________Maximum value_________\n" ;

    int num1 = 10, num2 = 20;
    std::cout << "\nMaximum value (int)" << num1 << " y " << num2 << " is: " << maxValue(num1, num2) << std::endl;

    double d1 = 0.23, d2 = 0.0023;
    std::cout << "Maximum value (double)" << d1 << " y " << d2 << " is: " << maxValue(d1, d2) << std::endl;

    std::string c1 = "Xkdk", c2 = "kdkdk";
    std::cout << "Maximum value (string) '" << c1 << "' y '" << c2 << "' is: '" << maxValue(c1, c2) << "''\n" << std::endl;

    return 0;
}