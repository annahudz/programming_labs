#ifndef H_NTREE_CPP
#define H_NTREE_CPP
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

/// PART 0 /////
class NNode {
public:
	int value;
	vector<NNode*>children;
	NNode(int val) {
		value = val;
	}
};

///// PART 1 (task 2 and 3)

NNode* getNodeByPath(NNode* nroot, const vector<int>& path) {
	NNode* current = nroot;
	for (int index : path) {
		if (index < 0 || index <current->children.size())
			return nullptr;
		current = current->children[index];
	}
	return current;
}
bool findPath(NNode* nnode, int value, vector<int>& path) {
	if (!nnode) return false;
	if (nnode->value == value)
		return true;
	for (int i = 0; i < nnode->children.size(); i++) {
		path.push_back(i);
		if (findPath(nnode->children[i], value, path))
			return true;
		path.pop_back();
	}
	return false;
}
vector<int> getPath(NNode* nroot, int value) {
	vector<int>path;
	if (findPath(nroot, value, path))
		return path;
}


void addNode(NNode* nroot, int value, const vector<int>& parentPath) {
	NNode* parent = getNodeByPath(nroot, parentPath);
	if (parent) {
		parent->children.push_back(new NNode(value));
	}
	else {
		cout << "Parent not found\n ";
	}
}

//// PART 2 (task 9)

void printLevelOrder(NNode* nroot) {
	if (!nroot) return;
	queue<NNode*> q;
	q.push(nroot);
	while (!q.empty()) {
		int size = q.size();
		for (int i = 0; i < size; i++) {
			NNode* current = q.front();
			q.pop();
			cout << current->value << " ";
			for (NNode* child : current->children)
				q.push(child);
		}
		cout << endl;
	}
}

//// PART 3 (task 14)

NNode* removeNode(NNode* nnode, int value) {
	if (!nnode) return nullptr;
	if (nnode->value == value) {
		NNode* temp = nnode;
		nnode = nullptr;
		return temp;
	}
	for (int i = 0; i < nnode->children.size(); i++) {
		NNode* removed = removeNode(nnode->children[i], value);
		if (removed) {
			nnode->children.erase(nnode->children.begin() + i);
			return removed;
		}
	}
	return nullptr;
}

#endif
