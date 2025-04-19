#include <iostream>
#include <algorithm> // for std::copy
#include <chrono>
class Buffer {
private:
    int* data;
    size_t size;

public:
    Buffer(size_t s) : size(s), data(new int[s]) {
        std::cout << "Constructor called\n";
    }

    ~Buffer() {
        delete[] data;
        std::cout << "Destructor called\n";
    }

    // Copy constructor
    Buffer(const Buffer& other) : size(other.size), data(new int[other.size]) {
        std::copy(other.data, other.data + other.size, data);
        std::cout << "Copy constructor called\n";
    }

    // Copy assignment
    Buffer& operator=(const Buffer& other) {
        if (this != &other) {
            int* newData = new int[other.size];
            std::copy(other.data, other.data + other.size, newData);
            delete[] data;
            data = newData;
            size = other.size;
        }
        std::cout << "Copy assignment called\n";
        return *this;
    }

    // Move constructor
    Buffer(Buffer&& other) noexcept : data(other.data), size(other.size) {
        other.data = nullptr;
        other.size = 0;
        std::cout << "Move constructor called\n";
    }

    // Move assignment
    Buffer& operator=(Buffer&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            size = other.size;
            other.data = nullptr;
            other.size = 0;
        }
        std::cout << "Move assignment called\n";
        return *this;
    }
};

int main() {
    //  std::cout << "________Creating b1_______\n";
    Buffer b1(10);  // Constructor

    //std::cout << "\n\n_______Copy constructing b2 from b1_______\n";
    Buffer b2 = b1; // Copy constructor

    //std::cout << "\n\n______Copy assigning b3 from b1_______\n";
    Buffer b3(5);
    b3 = b1;        // Copy assignment

    //std::cout << "\n\n_____Move constructing b4 from temporary___\n";
    Buffer b4 = Buffer(20); // Move constructor

    //std::cout << "\n\n_____Move assigning b5 from temporary____\n";
    Buffer b5(5);
    b5 = Buffer(30); // Move assignment


    const size_t largeSize = 10'000'000;
    const int iterations = 10;

    std::cout << "\n--- Copy Timing ---\n";
    auto copy_start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < iterations; ++i) {
        Buffer original(largeSize);
        Buffer copy = original; // Copy constructor
    }
    auto copy_end = std::chrono::high_resolution_clock::now();
    auto copy_duration = std::chrono::duration<double>(copy_end - copy_start).count();
    std::cout << "Copying took: " << copy_duration << " seconds\n";

    std::cout << "\n--- Move Timing ---\n";
    auto move_start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < iterations; ++i) {
        Buffer temp(largeSize);
        Buffer moved = std::move(temp); // Move constructor
    }
    auto move_end = std::chrono::high_resolution_clock::now();
    auto move_duration = std::chrono::duration<double>(move_end - move_start).count();
    std::cout << "Moving took: " << move_duration << " seconds\n";

   
    return 0;
}
