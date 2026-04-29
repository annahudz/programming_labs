#pragma once
#include <iostream>
#include <algorithm>
#include <ctime>

struct Node23 {
    int keys[3];
    int count;
    Node23* children[4];
    Node23* parent;

    Node23(Point val) : count(1), parent(nullptr) {
        keys[0] = val;
        for (int i = 0; i < 4; i++) children[i] = nullptr;
    }

    bool isLeaf() { return children[0] == nullptr; }
};

class Tree23 {
private:
    Node23* root;

    void sortNode(Node23* n) {
        if (n->count == 2 && n->keys[0] > n->keys[1]) std::swap(n->keys[0], n->keys[1]);
        if (n->count == 3) {
            std::sort(n->keys, n->keys + 3);
        }
    }
    void split(Node23* n) {
        Node23* left = new Node23(n->keys[0]);
        Node23* right = new Node23(n->keys[2]);
        int midKey = n->keys[1];

        if (!n->isLeaf()) {
            left->children[0] = n->children[0];
            left->children[1] = n->children[1];
            right->children[0] = n->children[2];
            right->children[1] = n->children[3];
            for (int i = 0; i < 2; i++) {
                if (left->children[i]) left->children[i]->parent = left;
                if (right->children[i]) right->children[i]->parent = right;
            }
        }

        if (!n->parent) {
            root = new Node23(midKey);
            root->children[0] = left;
            root->children[1] = right;
            left->parent = root;
            right->parent = root;
            delete n;
        }
        else {
            Node23* p = n->parent;
            p->keys[p->count++] = midKey;
            sortNode(p);


            int i = 0;
            while (p->children[i] != n) i++;
            for (int j = p->count; j > i; j--) p->children[j] = p->children[j - 1];

            p->children[i] = left;
            p->children[i + 1] = right;
            left->parent = p;
            right->parent = p;

            delete n;
            if (p->count > 2) split(p);
        }
    }

    void inorder(Node23* n, void (*action)(Point&)) {
        if (!n) return;
        inorder(n->children[0], action);
        if (action) action(n->keys[0]); else std::cout << n->keys[0] << " ";
        inorder(n->children[1], action);
        if (n->count > 1) {
            if (action) action(n->keys[1]); else std::cout << n->keys[1] << " ";
            inorder(n->children[2], action);
        }
    }

    void rangeSearch(Node23* n, Point min, Point max) {
        if (!n) return;
        if (min < n->keys[0]) rangeSearch(n->children[0], min, max);
        if (!(n->keys[0] < min) && !(max < n->keys[0] )) std::cout << n->keys[0] << " ";

        if (n->count == 1) {
            if (max > n->keys[0]) rangeSearch(n->children[1], min, max);
        }
        else {
            if (min < n->keys[1] && max > n->keys[0]) rangeSearch(n->children[1], min, max);
            if (!(n->keys[1] <min) && !(max<n->keys[1] )) std::cout << n->keys[1] << " ";
            if (max > n->keys[1]) rangeSearch(n->children[2], min, max);
        }
    }

    void clear(Node23* n) {
        if (!n) return;
        for (int i = 0; i <= n->count; i++) clear(n->children[i]);
        delete n;
    }

public:
    Tree23() : root(nullptr) {}
    ~Tree23() { clear(root); }

    void add(Point val) {
        if (!root) { root = new Node23(val); return; }
        Node23* curr = root;
        while (!curr->isLeaf()) {
            if (val < curr->keys[0]) curr = curr->children[0];
            else if (curr->count == 1 || val < curr->keys[1]) curr = curr->children[1];
            else curr = curr->children[2];
        }
        curr->keys[curr->count++] = val;
        sortNode(curr);
        if (curr->count > 2) split(curr);
    }

    void display() { inorder(root, nullptr); std::cout << std::endl; }

    void printRange(int min, int max) { rangeSearch(root, min, max); std::cout << std::endl; }

    void forEach(void (*action)(int&)) { inorder(root, action); }
    Node23* removeFromNode(Node23* node, Point value) {
        if (!node) return nullptr;
        for (int i = 0; i < node->count; i++) {
            if (node->keys[i] == value) {
                for (int j = i; j < node->count - 1; j++) node->keys[j] = node->keys[j + 1];
                node->count--;
                return node;
            }
        }
        for (int i = 0; i <= node->count; i++)
            node->children[i] = removeFromNode(node->children[i], value);
        return node;
    }
    void remove(Point value) {
        if (!root) return;
        root = removeFromNode(root, value);
        if (root && root->count == 0) {
            Node23* temp = root;
            if (!root->isLeaf()) {
                root = root->children[0];
            }
            else {
                root = nullptr;
            }
            delete temp;
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
};
