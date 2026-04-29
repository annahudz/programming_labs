#pragma once
#include <iostream>
#include <cstdlib> 

class ArrayList {
private:
    Point* data;
    int capacity;
    int size;


    void resize() {
        capacity = (capacity == 0) ? 1 : capacity * 2;
        Point* newData = new Point[capacity];
        for (int i = 0; i < size; i++) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
    }

public:

    ArrayList() : data(nullptr), capacity(0), size(0) {}


    void add(Point value) {
        if (size == capacity) {
            resize();
        }
        data[size++] = value;
    }



    bool remove(Point value) {
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


    bool contains(Point value) const {
        for (int i = 0; i < size; i++) {
            if (data[i] == value) return true;
        }
        return false;
    }

    void printRange(Point min, Point max) const {
        bool found = false;
        for (int i = 0; i < size; i++) {
            if (!(data[i] <min) && !(max < data[i] )) {
                std::cout << data[i] << " ";
                found = true;
            }
        }
        if (!found) std::cout << "Elements not found.";
        std::cout << std::endl;
    }


    void display() const {
        if (size == 0) {
            std::cout << "List is empty." << std::endl;
            return;
        }
        for (int i = 0; i < size; i++) {
            std::cout << data[i] << (i == size - 1 ? "" : " ");
        }
        std::cout << " [size: " << size << ", cap: " << capacity << "]" << std::endl;
    }

    void forEach(void (*action)(Point&)) {
        for (int i = 0; i < size; i++) {
            action(data[i]);
        }
    }


  void fillRandom(int n) {
    for (int i = 0; i < n; i++) {
        Point p;
        p.x = (rand() % 1000) / 10.0; 
        p.y = (rand() % 1000) / 10.0;
        p.z = (rand() % 1000) / 10.0;
        add(p); 
    }
}
    ~ArrayList() {
        delete[] data;
    }
};
