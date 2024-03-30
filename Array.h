#pragma once
#include <iostream>
using namespace std;
template<typename T>
class DynamicArray {
    T* array;
    int capacity;
    int size;

public:
    DynamicArray() : array(nullptr), capacity(0), size(0) {}
    ~DynamicArray() { delete[] array; }
    void addElement(const T& element) {
        if (size >= capacity) {
            int newCapacity = (capacity == 0) ? 1 : capacity * 2;
            T* newArray = new T[newCapacity];
            for (int i = 0; i < size; ++i) {
                newArray[i] = array[i];
            }
            delete[] array;
            array = newArray;
            capacity = newCapacity;
        }
        array[size++] = element;
    }

    void removeElement(int index) {
        if (index < 0 || index >= size) {
            cout << "Invalid index" << std::endl;
            return;
        }
        for (int i = index; i < size - 1; ++i) {
            array[i] = array[i + 1];
        }
        --size;
    }

    T& getElement(int index) const {
        if (index < 0 || index >= size) {
            cout<<"Index out of range";
        }
        return array[index];
    }
    int getSize() const {
        return size;
    }
};

