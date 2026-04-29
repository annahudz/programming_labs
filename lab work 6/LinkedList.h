#pragma once
#include <iostream>
#include <chrono>
#include <cstdlib>
#include <ctime>
using namespace std;

struct Node {
    int data;
    Node* next;
};

class LinkedList {
private:
    Node* head;

public:
    LinkedList() : head(nullptr) {}

    void add(int value) {
        Node* newNode = new Node{ value, nullptr };
        if (!head) {
            head = newNode;
            return;
        }
        Node* temp = head;
        while (temp->next) temp = temp->next;
        temp->next = newNode;

    }
    void fillRandom(int count, int minVal = 0, int maxVal = 100) {
        for (int i = 0; i < count; i++) {
            add(rand() % (maxVal - minVal + 1) + minVal);
        }
    }

    void remove(int value) {
        if (!head) return;
        if (head->data == value) {
            Node* temp = head;
            head = head->next;
            delete temp;
            return;
        }
        Node* curr = head;
        while (curr->next && curr->next->data != value) curr = curr->next;
        if (curr->next) {
            Node* temp = curr->next;
            curr->next = curr->next->next;
            delete temp;
        }
    }


    void printRange(int min, int max) {
        Node* temp = head;
        bool found = false;
        while (temp) {
            if (temp->data >= min && temp->data <= max) {
                std::cout << temp->data << " ";
                found = true;
            }
            temp = temp->next;
        }
        if (!found) std::cout << "Елементів не знайдено";
        std::cout << std::endl;
    }


    void display() {
        Node* temp = head;
        while (temp) {
            std::cout << temp->data << " -> ";
            temp = temp->next;
        }
        std::cout << "nullptr" << std::endl;
    }


    void forEach(void (*action)(int&)) {
        Node* temp = head;
        while (temp) {
            action(temp->data);
            temp = temp->next;
        }
    }

    ~LinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};
