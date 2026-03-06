#ifndef CUSTOM_VECTOR_HPP
#define CUSTOM_VECTOR_HPP

#include <string>

/**
 * @brief A custom dynamic array implementation to avoid standard STL libraries.
 */
template <typename T>
class CustomVector {
private:
    T* data;
    int capacity;
    int currentSize;

    void resize() {
        capacity = (capacity == 0) ? 1 : capacity * 2;
        T* newData = new T[capacity];
        for (int i = 0; i < currentSize; i++) {
            newData[i] = data[i];
        }
        if (data != nullptr) delete[] data;
        data = newData;
    }

public:
    CustomVector() : data(nullptr), capacity(0), currentSize(0) {}
    
    CustomVector(const CustomVector& other) {
        currentSize = other.currentSize;
        capacity = other.capacity;
        data = new T[capacity];
        for (int i = 0; i < currentSize; i++) data[i] = other.data[i];
    }
    
    CustomVector& operator=(const CustomVector& other) {
        if (this != &other) {
            if (data != nullptr) delete[] data;
            currentSize = other.currentSize;
            capacity = other.capacity;
            data = new T[capacity];
            for (int i = 0; i < currentSize; i++) data[i] = other.data[i];
        }
        return *this;
    }

    ~CustomVector() {
        if (data != nullptr) delete[] data;
    }

    void push_back(T value) {
        if (currentSize == capacity) resize();
        data[currentSize++] = value;
    }

    T& operator[](int index) { return data[index]; }
    const T& operator[](int index) const { return data[index]; }
    
    int size() const { return currentSize; }
    void clear() { currentSize = 0; }
};

// Utility function for safe string to integer conversion
inline int parseInt(const std::string& s) {
    if (s.empty()) return 0;
    try {
        return std::stoi(s);
    } catch (...) {
        return 0;
    }
}

#endif