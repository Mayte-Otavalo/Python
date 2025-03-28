#include <iostream>

template <unsigned N>
struct Fibonacci {
    static constexpr unsigned value = Fibonacci<N-1>::value + Fibonacci<N-2>::value;
};

template <>
struct Fibonacci<0> {
    static constexpr unsigned value = 0;
};

template <>
struct Fibonacci<1> {
    static constexpr unsigned value = 1;
};

constexpr unsigned fibonacci(unsigned n) {
    return n <= 1 ? n : fibonacci(n-1) + fibonacci(n-2);
}

int main() {

     std::cout << "\n__Fibonacci Series Using Template Metaprogramming ___\n";
    // Calculation using template
    constexpr unsigned fib10 = Fibonacci<10>::value;
    std::cout << "\nF(10) (template) = " << fib10 << std::endl;

    // Calculation using constexpr function
    constexpr unsigned fib15 = fibonacci(15);
    std::cout << "F(15) (constexpr) = " << fib15 << std::endl;

    // Compile-time verification
    static_assert(Fibonacci<10>::value == 55, "Fibonacci template error");
    static_assert(fibonacci(15) == 610, "Fibonacci function error");

    // Runtime usage demonstration
    std::cout << "F(20) = " << Fibonacci<20>::value <<"\n" << std::endl;

    return 0;
}