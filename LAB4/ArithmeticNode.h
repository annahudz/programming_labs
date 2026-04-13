#ifndef H_ArithmeticNode_CPP
#define H_Arithmetic_CPP
#include <iostream>
#include <cmath>
using namespace std;

/// PART 6 (task 22)

enum NodeType {
	CONST, VAR, OP
};
struct Arithm_Node {
	NodeType type;
	char op = 0;
	double value = 0;
	string var = "";
	Arithm_Node* left = nullptr;
	Arithm_Node* right = nullptr;
};
struct Arithm_tree {
	Arithm_Node* root = nullptr;
};
double calculating(char op, double a, double b) {
	switch (op) {
	case'+': return a + b;
	case'-': return a - b;
	case'*': return a * b;
	case'/':
		if (b == 0) throw runtime_error("Division by zero");
		return a / b;
	default:
		throw
			runtime_error("Error! Unknown operation!");
	}
}
bool equal(Arithm_Node* a, Arithm_Node* b) {
	if (!a || !b) return a == b;
	if (a->type == CONST)
		return a->value == b->value;
	if (a->type == VAR)
		return a->var == b->var;
	if (a->type == OP) {
		if (a->op != b->op)
			return false;
		return equal(a->left, b->left) && equal(a->right, b->right);
	}
	return false;
}
Arithm_Node* simpl(Arithm_Node* node) {
	if (!node) return nullptr;
	if (node->type != OP)
		return node;
	if (node->left == nullptr || node->right == nullptr) {
		throw
			runtime_error("Error! No value");
	}
	node->left = simpl(node->left);
	node->right = simpl(node->right);
	if (node->left->type == CONST && node->right->type == CONST) {
		double res = calculating(node->op, node->left->value, node->right->value);
		delete node->left;
		delete node->right;
		node->left = node->right = nullptr;
		node->type = CONST;
		node->value = res;
		return node;
	}
	if (node->op == '+' && node->left->type == CONST && node->left->value == 0) {
		Arithm_Node* res = node->right;
		delete node->left;
		delete node;
		return res;
	}
	if (node->op == '+' && node->right->type == CONST && node->right->value == 0) {
		Arithm_Node* res = node->left;
		delete node->right;
		delete node;
		return res;
	}
	if (node->op == '+' && equal(node->left, node->right)) {
		node->op = '*';
		node->left->type = CONST;
		node->left->value = 2;
		return node;
	}
	if (node->op == '-' && node->right->type == CONST && node->right->value == 0) {
		Arithm_Node* res = node->left;
		delete node->right;
		delete node;
		return res;
	}
	if (node->op == '-' && equal(node->left, node->right)) {
		delete node->left;
		delete node->right;
		node->left = node->right = nullptr;
		node->type = CONST;
		node->value = 0;
		return node;
	}
	if (node->op == '*' && ((node->left->type == CONST && node->left->value == 0) || (node->right->type == CONST && node->right->value == 0))){
		delete node->left;
		delete node->right;
		node->left = node->right = nullptr;
		node->type = CONST;
		node->value = 0;
		return node;
	}
	if (node->op == '*' && node->right->type == CONST && node->right->value == 1) {
		Arithm_Node* res = node->left;
		delete node->right;
		delete node;
		return res;
	}
	if (node->op == '*' && node->left->type == CONST && node->left->value == 1) {
		Arithm_Node* res = node->right;
		delete node->left;
		delete node;
		return res;
	}
	if (node->op == '/' && node->left->type == CONST && node->left->value == 0) {
		delete node->left;
		delete node->right;
		node->left = node->right = nullptr;
		node->type = CONST;
		node->value = 0;
		return node;
	}
	if (node->op == '/' && node->right->type == CONST && node->right->value == 1) {
		Arithm_Node* res = node->left;
		delete node->right;
		delete node;
		return res;
	}
	if (node->op == '/' && node->right->type == CONST && node->right->value == 0) {
		throw
			runtime_error("Division by zero");
	}
	if (node->op == '/' && equal(node->right, node->left)) {
		delete node->left;
		delete node->right;
		node->left = node->right = nullptr;
		node->type = CONST;
		node->value = 1;
		return node;
	}
	if (node->op == '^' && node->right->type == CONST && node->right) {
		Arithm_Node* res = node->left;
		delete node->right;
		delete node;
		return res;
	}
	if (node->op == '^' && node->right->type == CONST && node->right->value == 0) {
		delete node->left;
		delete node;
		node->left = node->right = nullptr;
		node->type = CONST;
		node->value = 1;
		return node;
	}
	if (node->op == '*' && equal(node->left, node->right)) {
		node->op = '^';
		delete node->right;
		node->right = new Arithm_Node();
		node->right->type = CONST;
		node->right->value = 2;
		return node;
	}
	return node;
	}
	void print_Tree(Arithm_Node* node, std::string st = "") {
		if (node == nullptr) return;
		cout << st << node->value << endl;
		print_Tree(node->left, st + " ");
		print_Tree(node->right, st + " ");
	}


#endif
