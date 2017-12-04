#include <iostream>
#include <ctime>
#include <random>
#include <algorithm>
using namespace std;

#define RED 0
#define BLACK 1

struct Node {
	int key;
	int color;
	Node* left;
	Node* right;
	Node* parent;
};

int level = 0;

void inOrder(Node* root, Node* NIL) {
	level++;
	if (root != NIL) {
		inOrder(root->right, NIL);

		int n = level;
		while (n--) cout << "   |   ";
		cout << root->key << "-";
		if (root->color == RED) cout << "R";
		else cout << "B";
		cout << endl;

		inOrder(root->left, NIL);
	}
	level--;
}

Node* getNode(int k, int color, Node* NIL) {
	return new Node{ k, color, NIL, NIL, NIL };
}

void leftRotate(Node*& root, Node* x, Node* NIL) {
	Node *y = x->right;

	x->right = y->left;
	if (y->left != NIL) y->left->parent = x;

	y->parent = x->parent;
	if (x->parent == NIL) root = y;
	else {
		if (x->parent->left == x) x->parent->left = y;
		else x->parent->right = y;
	}
	
	y->left = x;
	x->parent = y;

	cout << "Rotate left at " << x->key << endl;
	inOrder(root, NIL);
	cout << endl;
}

void rightRotate(Node*& root, Node* x, Node* NIL) {
	Node *y = x->left;
	
	x->left = y->right;
	if (y->right != NIL) y->right->parent = x;

	y->parent = x->parent;
	if (x->parent == NIL) root = y;
	else {
		if (x->parent->left == x) x->parent->left = y;
		else x->parent->right = y;
	}

	y->right = x;
	x->parent = y;
	
	cout << "Rotate right at " << x->key << endl;
	inOrder(root, NIL);
	cout << endl;
}

void insertBST(Node*& root, Node* x, Node* NIL) {
	Node *y = NIL, *z = root;
	while (z != NIL) {
		y = z;
		if (x->key < z->key) z = z->left;
		else if (x->key > z->key) z = z->right;
		else return;
	}

	x->parent = y;
	if (y == NIL) root = x;
	else {
		if (x->key < y->key) y->left = x;
		else y->right = x;
	}
}

void fixUp(Node *& root, Node* x, Node* NIL) {
	while (x->parent->color == RED) {
		Node *p = x->parent;
		Node *g = p->parent;

		Node *u;
		if (g->left == p) u = g->right;
		else u = g->left;

		if (u->color == RED) {
			u->color = g->color;
			p->color = g->color;
			g->color = RED;
			x = g;
		}
		else {
			if (g->left == p) {
				if (p->right == x) {
					x = p;
					leftRotate(root, x, NIL);
					p = x->parent;
					g = p->parent;
				}
				p->color = g->color;
				g->color = RED;
				rightRotate(root, g, NIL);
			}
			else if (g->right == p) {
				if (p->left == x) {
					x = p;
					rightRotate(root, x, NIL);
					p = x->parent;
					g = p->parent;
				}
				p->color = g->color;
				g->color = RED;
				leftRotate(root, g, NIL);
			}
		}
	}
	root->color = BLACK;
}

void insert(Node*& root, int k, Node* NIL) {
	Node *x = getNode(k, RED, NIL);
	insertBST(root, x, NIL);
	inOrder(root, NIL);
	cout << endl;
	fixUp(root, x, NIL);
}

void main() {
	srand(time(NULL));
	default_random_engine generator(time(NULL));
	uniform_int_distribution<int> distribution(0, 100);

	Node* NIL = new Node;
	NIL->key = -1;
	NIL->color = BLACK;
	NIL->left = NIL->right = NIL->parent = NIL;

	Node* root = NIL;

	int n;
	cout << "Number of node(s): ";
	cin >> n;
	for (int i = 0; i < n; i++) {
		int x;
		//cin >> x;
		x = distribution(generator);
		cout << "---- Inserting " << x << endl;
		insert(root, x, NIL);
		cout << "Result: " << endl;
		inOrder(root, NIL);
		cout << endl;
	}
}