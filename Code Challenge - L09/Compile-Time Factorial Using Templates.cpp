#include <iostream>

template <unsigned N>
struct Factorial {
    static constexpr unsigned value = N * Factorial<N - 1>::value;
};

template <>
struct Factorial<0> {
    static constexpr unsigned value = 1;
};

constexpr unsigned factorial(unsigned n) {
    return n == 0 ? 1 : n * factorial(n - 1);
}

int main() {
   
    std::cout <<"\nCompile-Time Factorial Using Templates\n";
    constexpr unsigned result1 = Factorial<5>::value;
    std::cout << "\n5! (template) = " << result1 << std::endl;

    // constexpr function
    constexpr unsigned result2 = factorial(5);
    std::cout << "5! (constexpr) = " << result2 << "\n" <<std::endl;

    
    return 0;
}