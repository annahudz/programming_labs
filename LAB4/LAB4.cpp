#include "NTree.h"
#include "ArithmeticNode.h"
#include "BinaryTree.h"
#include <iostream>
#include<vector>


using namespace std;

// DEMO MODE
void runDemoMode() {
    cout << "\n=== DEMO MODE ===\n";

    //  N-ARY TREE
    cout << "\n[Block 0-3] N-ary tree:\n";

    NNode* nroot = new NNode(100);

    addNode(nroot, 10, {});
    addNode(nroot, 20, {});
    addNode(nroot, 11, { 0 });

    printLevelOrder(nroot);

    cout << "Deleting node with value 10...\n";
    removeNode(nroot, 10);

    printLevelOrder(nroot);

    vector<int> path = getPath(nroot, 11);
    cout << "Path to 11: ";
    for (int x : path) cout << x << " ";
    cout << endl;

    // BINARY TREE 
    cout << "\n[Block 4-5] Binary tree:\n";

    BNode* broot = nullptr;
    int arr[] = { 50, 30, 70, 20, 40 };

    for (int x : arr)
        broot = insert(broot, x);

    printLevelOrder(broot);

    vector<int> pre;
    preOrder(broot, pre);

    cout << "Preorder: ";
    for (int x : pre) cout << x << " ";
    cout << endl;

    //  ARITHMETIC TREE
    cout << "\n[Block 6] Arithmetic tree:\n";

    // (10 + 20) * 2
    Arithm_Node* root = new Arithm_Node();
    root->type = OP;
    root->op = '*';

    root->left = new Arithm_Node();
    root->left->type = OP;
    root->left->op = '+';

    root->right = new Arithm_Node();
    root->right->type = CONST;
    root->right->value = 2;

    root->left->left = new Arithm_Node();
    root->left->left->type = CONST;
    root->left->left->value = 10;

    root->left->right = new Arithm_Node();
    root->left->right->type = CONST;
    root->left->right->value = 20;

    cout << "Before simplification:\n";
    print_Tree(root);

    root = simpl(root);

    cout << "After simplification:\n";
    print_Tree(root);

    cout << "\n=============================\n";
}


// INTERACTIVE MODE

void runInteractiveMode() {
    int choice;

    while (true) {
        cout << "\n=== INTERACTIVE MODE ===\n";
        cout << "1 - Binary Tree\n";
        cout << "2 - N-ary Tree\n";
        cout << "3 - Arithmetic Tree\n";
        cout << "0 - Exit\n";
        cout << "Choose: ";
        cin >> choice;

        if (choice == 0) break;

        //  BINARY 
        if (choice == 1) {
            BNode* broot = nullptr;

            while (true) {
                int x;
                cout << "Enter number (-1 stop): ";
                cin >> x;

                if (x == -1) break;

                broot = insert(broot, x);
            }

            cout << "\nTree:\n";
            printLevelOrder(broot);

            vector<int> pre;
            preOrder(broot, pre);

            cout << "Preorder: ";
            for (int x : pre) cout << x << " ";
            cout << endl;
        }

        //  N-ARY
        else if (choice == 2) {
            NNode* root = new NNode(1);

            while (true) {
                int val;
                cout << "Enter value (-1 stop): ";
                cin >> val;

                if (val == -1) break;

                addNode(root, val, {});
            }

            cout << "\nTree:\n";
            printLevelOrder(root);

            int findVal;
            cout << "Enter value to find path: ";
            cin >> findVal;

            vector<int> path = getPath(root, findVal);

            cout << "Path: ";
            for (int x : path) cout << x << " ";
            cout << endl;
        }

        //  ARITHMETIC 
        else if (choice == 3) {
            Arithm_Node* root = new Arithm_Node();

            root->type = OP;
            root->op = '+';

            root->left = new Arithm_Node();
            root->left->type = CONST;
            root->left->value = 2;

            root->right = new Arithm_Node();
            root->right->type = CONST;
            root->right->value = 3;

            cout << "\nBefore:\n";
            print_Tree(root);

            root = simpl(root);

            cout << "After:\n";
            print_Tree(root);
        }
    }
}


// MAIN

int main() {
    int mode;

    cout << "Choose mode:\n";
    cout << "1 - Demo\n";
    cout << "2 - Interactive\n";
    cout << "> ";
    cin >> mode;

    if (mode == 1)
        runDemoMode();
    else if (mode == 2)
        runInteractiveMode();
    else
        cout << "Unknown mode\n";

    return 0;
}