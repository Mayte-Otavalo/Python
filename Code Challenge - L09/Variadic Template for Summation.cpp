#include <iostream>
#include <type_traits>

template <typename T = double>
T sum() {
    return T(0);
}

template <typename T>
T sum(T t) {
    return t;
}

template <typename T, typename... Args>
auto sum(T t, Args... args) {
    if constexpr (sizeof...(args) > 0) {
        return t + sum(args...);
    } else {
        return t;
    }
}

template <typename... Args>
auto sum_fold(Args... args) {
    return (args + ...);
}

int main() {
    std::cout<<"\n_______Variadic Template for Summation_________\n";
    std::cout << "\nSum of integers: " << sum(1, 2, 3) << std::endl;
    std::cout << "Sum of doubles: " << sum(1.111, 2.222, 3.333, 4.444) << std::endl;
    std::cout << "Mixed sum: " << sum(1, 2.555, 3, 4.2) << std::endl;
    std::cout << "Empty sum: " << sum() << std::endl;
    std::cout << "Fold sum: " << sum_fold(10, 20.5, 30) << "\n" <<std::endl;
    
    return 0;
}