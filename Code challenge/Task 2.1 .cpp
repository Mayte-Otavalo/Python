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
    // _____________Copy constructor_______________

    Buffer(const Buffer& other) : size(other.size), data(new int[other.size]) {
        std::copy(other.data, other.data + other.size, data);
        std::cout << "Copy constructor called\n";
    }

    // ______________Copy assignment operator__________________

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

    //___________________ Move constructor____________________
    Buffer(Buffer&& other) noexcept : data(other.data), size(other.size) {
        other.data = nullptr;
        other.size = 0;
        std::cout << "Move constructor called\n";
    }

    // __________________Move assignment operator______________________
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