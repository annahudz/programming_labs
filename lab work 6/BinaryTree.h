#pragma once
#include <iostream>
#include <cstdlib>

struct TreeNode {
    Point data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(Point val) : data(val), left(nullptr), right(nullptr) {}
};

class BinarySearchTree {
private:
    TreeNode* root;


    TreeNode* insert(TreeNode* node, Point value) {
        if (node == nullptr) return new TreeNode(value);

        if (value < node->data)
            node->left = insert(node->left, value);
        else
            node->right = insert(node->right, value);

        return node;
    }


    TreeNode* findMin(TreeNode* node) {
        while (node && node->left != nullptr) node = node->left;
        return node;
    }


    TreeNode* remove(TreeNode* node, Point value) {
        if (node == nullptr) return nullptr;

        if (value < node->data)
            node->left = remove(node->left, value);
        else if (value > node->data)
            node->right = remove(node->right, value);
        else {

            if (node->left == nullptr) {
                TreeNode* temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr) {
                TreeNode* temp = node->left;
                delete node;
                return temp;
            }
            TreeNode* temp = findMin(node->right);
            node->data = temp->data;
            node->right = remove(node->right, temp->data);
        }
        return node;
    }


    void inorder(TreeNode* node, void (*action)(Point&)) const {
        if (node == nullptr) return;
        inorder(node->left, action);
        if (action) action(node->data);
        else std::cout << node->data << " ";
        inorder(node->right, action);
    }


    void rangeSearch(TreeNode* node, Point min, Point max) const {
        if (node == nullptr) return;
        if (node->data > min) rangeSearch(node->left, min, max);
        if (!(node->data < min) && !(max<node->data)) std::cout << node->data << " ";
        if (node->data < max) rangeSearch(node->right, min, max);
    }

    void clear(TreeNode* node) {
        if (node == nullptr) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }

public:
    BinarySearchTree() : root(nullptr) {}

    void add(Point value) { root = insert(root, value); }

    void remove(Point value) { root = remove(root, value); }

    bool contains(Point value) const {
        TreeNode* curr = root;
        while (curr) {
            if (curr->data == value) return true;
            curr = (value < curr->data) ? curr->left : curr->right;
        }
        return false;
    }

    void display() const {
        if (!root) std::cout << "Tree is empty.";
        inorder(root, nullptr);
        std::cout << std::endl;
    }

    void printRange(Point min, Point max) const {
        rangeSearch(root, min, max);
        std::cout << std::endl;
    }

    void forEach(void (*action)(Point&)) {
        inorder(root, action);
    }

   void fillRandom(int count) {
    for (int i = 0; i < n; i++) {
        Point p;
        p.x = (rand() % 1000) / 10.0; 
        p.y = (rand() % 1000) / 10.0;
        p.z = (rand() % 1000) / 10.0;
        add(p); 
    }
}
    ~BinarySearchTree() { clear(root); }
};
