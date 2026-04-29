#pragma once
#include <iostream>
#include <chrono>
#include <cstdlib>
#include <ctime>
using namespace std;

struct Node {
    Point data;
    Node* next;
Node (Point val, Node* n = nullptr): data(val), next(n){
}
};

class LinkedList {
private:
    Node* head;

public:
    LinkedList() : head(nullptr) {}

    void add(Point value) {
        Node* newNode = new Node{ value, nullptr };
        if (!head) {
            head = newNode;
            return;
        }
        Node* temp = head;
        while (temp->next) temp = temp->next;
        temp->next = newNode;

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

    void remove(Point value) {
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


    void printRange(Point min, Point max) {
        Node* temp = head;
        bool found = false;
        while (temp) {
            if (!(temp->data < min) && !(max < temp->data)) {
                std::cout << temp->data << " ";
                found = true;
            }
            temp = temp->next;
        }
        if (!found) std::cout << "Elements not found";
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


    void forEach(void (*action)(Point&)) {
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
