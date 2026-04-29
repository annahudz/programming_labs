#include <iostream>
#include <chrono>
#include <iomanip>
#include <string>
#include <vector>
#include <ctime>
#include "ArrayList.h"
#include "LinkedList.h"
#include "BinaryTree.h" 
#include "AVL.h"        
#include "B23Tree.h"    
// Task 5
using namespace std;
#include <iostream>
#include <iomanip>

struct Point {
    double x, y, z;

    bool operator<(const Point& other) const {
        if (x != other.x) return x < other.x;
        if (y != other.y) return y < other.y;
        return z < other.z;
    }

    bool operator>(const Point& other) const { return other < *this; }
    
    bool operator==(const Point& other) const {
        return x == other.x && y == other.y && z == other.z;
    }

    bool operator!=(const Point& other) const { return !(*this == other); }
};

std::ostream& operator<<(std::ostream& os, const Point& p) {
    os << "(" << std::fixed << std::setprecision(1) << p.x 
       << ", " << p.y << ", " << p.z << ")";
    return os;
}

template <typename T>
void handleInteraction(T& structure,string name) {
    int choice;
    Point p,p1,p2;
    while (true) {
        cout << "\n--- [" << name << "] SETTINGS ---" << endl;
        cout << "1. Add Point\n2. Remove Point\n3. Range Search\n4. Display Structure\n5. Random Fill\n0. Back\n>> ";
        if (!(cin >> choice)) { cin.clear(); cin.ignore(1000, '\n'); continue; }
        if (choice == 0) break;

        switch (choice) {
        case 1: cout << "X Y Z: "; cin >> p.x>>p.y>>p.z; structure.add(p); break;
        case 2: cout << "Enter X Y Z  to remove: "; cin >>p.x>>p.y>>p.z ; structure.remove(p); break;
        case 3:cout << "Enter Max (X Y Z): "; cin >> p1.x>>p1.y>>p1.z; structure.printRange(p1 ); break;
            cout << "Enter Min (X Y Z): "; cin >>p2.x>>p2.y>>p2.z; structure.printRange(p2); break;
        case 4: structure.display(); break;
        case 5: cout << "Enter count: "; cin >> n; structure.fillRandom(n); break;
        }
        if (choice == 1 || choice == 2 || choice == 5) {
            cout << "Current structure state: "; structure.display();
        }
    }
}
template <typename T>
void runDemo(string name) {
    T obj;
    cout << "\n>>> DEMONSTRATION FOR " << name << " <<<\n";
    int vals[] = { {10,1,1}, {5,2,2}, {20,3,3}};

    cout << "Step 1: Adding elements sequentially:\n";
    for (int v : vals) {
        cout << "Adding " << v << " -> ";
        obj.add(v);
        obj.display();
    }

    cout << "\nStep 2: Removing element "<<vals[1]<<":\n";
    obj.remove(vals[1]);
    obj.display();
    cout << "--------------------------------\n";
}

template <typename T>
void benchmark(string name, int n) {
    T obj;
    clock_t start = clock();
    obj.fillRandom(n, 1, 100000);
    clock_t end = clock();
    double timeTaken = double(end - start) / CLOCKS_PER_SEC;
    cout << left << setw(20) << name << "| Time: " << fixed << setprecision(5) << timeTaken << " sec." << endl;
}

void runInteractiveMode() {
    int s;
    cout << "\nChoose a structure:\n1. ArrayList\n2. LinkedList\n3. BST\n4. AVL\n5. 2-3 Tree\nChoice: ";
    cin >> s;

    switch (s) {
    case 1: { ArrayList a; handleInteraction(a, "ArrayList"); break; }
    case 2: { LinkedList l; handleInteraction(l, "LinkedList"); break; }
    case 3: { BinarySearchTree b; handleInteraction(b, "BST"); break; }
    case 4: { AVLTree avl; handleInteraction(avl, "AVL"); break; }
    case 5: { Tree23 t; handleInteraction(t, "2-3 Tree"); break; }
    default: cout << "Invalid selection.\n";
    }
}

int main() {
    srand(static_cast<unsigned>(time(0)));
    int mode;

    while (true) {
        cout << "\n=== MAIN MENU ===\n";
        cout << "1. Interactive Mode\n";
        cout << "2. Demonstration Mode\n";
        cout << "3. Performance Benchmark\n";
        cout << "0. Exit\n";
        cout << "Choice: ";

        if (!(cin >> mode)) { cin.clear(); cin.ignore(1000, '\n'); continue; }
        if (mode == 0) break;

        if (mode == 1) runInteractiveMode();
        else if (mode == 2) {
            runDemo<ArrayList>("ArrayList");
            runDemo<LinkedList>("LinkedList");
            runDemo<BinarySearchTree>("BST");
            runDemo<AVLTree>("AVL");
            runDemo<Tree23>("2-3 Tree");
        }
        else if (mode == 3) {
            int n = 20000;
            cout << "\n--- Performance Test (N=" << n << ") ---\n";
            benchmark<ArrayList>("ArrayList", n);
            benchmark<LinkedList>("LinkedList", n);
            benchmark<BinarySearchTree>("BST", n);
            benchmark<AVLTree>("AVL", n);
            benchmark<Tree23>("2-3 Tree", n);
        }
    }
    return 0;
}
