#ifndef H_BINARYTREE_CPP
#define H_BINARYTREE_CPP
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// PART 4 (task 18)

struct BNode {
	int value;
	BNode* left;
	BNode* right;
	BNode(int val) : value(val), left(nullptr), right(nullptr){}
};
BNode* insert(BNode* broot, int value) {
	if (!broot)
		return new BNode(value);
	if (value < broot->value)
		broot->left = insert(broot->left, value);
	else
		broot->right = insert(broot->right, value);
	return broot;
}

void printLevelOrder(BNode* broot) {
	if (!broot) return;
	queue<BNode*>q;
	q.push(broot);
	while (!q.empty()) {
		int size = q.size();
		for (int i = 0; i < size; i++) {
			BNode* current = q.front();
			q.pop();
			cout << current->value << " ";
			if (current->left)
				q.push(current->left);
			if (current->right)
				q.push(current->right);
		}
		cout << endl;
	}
}

/// PART 5  (task 21)

void preOrder(BNode* broot, vector<int>& result) {
	if (!broot) return;
	result.push_back(broot->value);
	preOrder(broot->left, result);
	preOrder(broot->right, result);
}
vector<int> buildPreOrderSequence(BNode* broot) {
	vector<int> result;
	preOrder(broot, result);
	return result;
}

#endif
