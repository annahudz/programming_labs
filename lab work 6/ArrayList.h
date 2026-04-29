#pragma once
#include <iostream>
#include <cstdlib> 

class ArrayList {
private:
    int* data;
    int capacity;
    int size;


    void resize() {
        capacity = (capacity == 0) ? 1 : capacity * 2;
        int* newData = new int[capacity];
        for (int i = 0; i < size; i++) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
    }

public:

    ArrayList() : data(nullptr), capacity(0), size(0) {}


    void add(int value) {
        if (size == capacity) {
            resize();
        }
        data[size++] = value;
    }



    bool remove(int value) {
        for (int i = 0; i < size; i++) {
            if (data[i] == value) {
                for (int j = i; j < size - 1; j++) {
                    data[j] = data[j + 1];
                }
                size--;
                return true;
            }
        }
        return false;
    }


    bool contains(int value) const {
        for (int i = 0; i < size; i++) {
            if (data[i] == value) return true;
        }
        return false;
    }

    void printRange(int min, int max) const {
        bool found = false;
        for (int i = 0; i < size; i++) {
            if (data[i] >= min && data[i] <= max) {
                std::cout << data[i] << " ";
                found = true;
            }
        }
        if (!found) std::cout << "Елементів не знайдено.";
        std::cout << std::endl;
    }


    void display() const {
        if (size == 0) {
            std::cout << "Список порожній." << std::endl;
            return;
        }
        for (int i = 0; i < size; i++) {
            std::cout << data[i] << (i == size - 1 ? "" : " ");
        }
        std::cout << " [size: " << size << ", cap: " << capacity << "]" << std::endl;
    }

    void forEach(void (*action)(int&)) {
        for (int i = 0; i < size; i++) {
            action(data[i]);
        }
    }


    void fillRandom(int count, int minVal = 0, int maxVal = 100) {
        for (int i = 0; i < count; i++) {
            add(minVal + rand() % (maxVal - minVal + 1));
        }
    }

    ~ArrayList() {
        delete[] data;
    }
};
