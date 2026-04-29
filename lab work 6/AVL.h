#pragma once
#include <iostream>
#include <algorithm>
#include <ctime>

struct AVLNode {
    Point data;
    AVLNode* left, * right;
    int height;

    AVLNode(Point val) : data(val), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree {
private:
    AVLNode* root;

    int getHeight(AVLNode* n) { return n ? n->height : 0; }

    int getBalance(AVLNode* n) {
        return n ? getHeight(n->left) - getHeight(n->right) : 0;
    }

    void updateHeight(AVLNode* n) {
        n->height = 1 + std::max(getHeight(n->left), getHeight(n->right));
    }

    AVLNode* rotateRight(AVLNode* y) {
        AVLNode* x = y->left;
        AVLNode* T2 = x->right;
        x->right = y;
        y->left = T2;
        updateHeight(y);
        updateHeight(x);
        return x;
    }

    AVLNode* rotateLeft(AVLNode* x) {
        AVLNode* y = x->right;
        AVLNode* T2 = y->left;
        y->left = x;
        x->right = T2;
        updateHeight(x);
        updateHeight(y);
        return y;
    }

    AVLNode* balanceNode(AVLNode* node) {
        updateHeight(node);
        int balance = getBalance(node);

        if (balance > 1) {
            if (getBalance(node->left) < 0)
                node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        if (balance < -1) {
            if (getBalance(node->right) > 0)
                node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        return node;
    }

    AVLNode* insert(AVLNode* node, Point value) {
        if (!node) return new AVLNode(value);
        if (value < node->data) node->left = insert(node->left, value);
        else if (value > node->data) node->right = insert(node->right, value);
        else return node;

        return balanceNode(node);
    }

    AVLNode* findMin(AVLNode* node) {
        while (node->left) node = node->left;
        return node;
    }

    AVLNode* remove(AVLNode* node, Point value) {
        if (!node) return nullptr;

        if (value < node->data) node->left = remove(node->left, value);
        else if (value > node->data) node->right = remove(node->right, value);
        else {
            if (!node->left || !node->right) {
                AVLNode* temp = node->left ? node->left : node->right;
                delete node;
                return temp;
            }
            AVLNode* temp = findMin(node->right);
            node->data = temp->data;
            node->right = remove(node->right, temp->data);
        }
        return balanceNode(node);
    }

    void inorder(AVLNode* node, void (*action)(Point&)) {
        if (!node) return;
        inorder(node->left, action);
        if (action) action(node->data);
        else std::cout << node->data << " ";
        inorder(node->right, action);
    }

    void rangeSearch(AVLNode* node, Point min, Point max) {
        if (!node) return;
        if (node->data > min) rangeSearch(node->left, min, max);
        if (!(node->data < min) && !(max<node->data )) std::cout << node->data << " ";
        if (node->data < max) rangeSearch(node->right, min, max);
    }

    void clear(AVLNode* node) {
        if (!node) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }

public:
    AVLTree() : root(nullptr) {}
    ~AVLTree() { clear(root); }

    void add(Point value) { root = insert(root, value); }

    void remove(Point value) { root = remove(root, value); }

    void display() { inorder(root, nullptr); std::cout << std::endl; }

    void printRange(Point min, Point max) { rangeSearch(root, min, max); std::cout << std::endl; }

    void forEach(void (*action)(Point&)) { inorder(root, action); }

void fillRandom(int n) {
    for (int i = 0; i < n; i++) {
        Point p;
        p.x = (rand() % 1000) / 10.0; // випадкове число з крапкою
        p.y = (rand() % 1000) / 10.0;
        p.z = (rand() % 1000) / 10.0;
        add(p); // викликаємо метод додавання вже для Point
    }
}
};
