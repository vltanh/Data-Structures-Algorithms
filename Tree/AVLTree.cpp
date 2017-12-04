#include <iostream>
#include <ctime>
#include <random>
#include <algorithm>
using namespace std;

struct Node {
	int key;
	int height;
	Node* left;
	Node* right;
};

Node* getNode(int k) {
	return new Node{ k, 1, NULL, NULL };
}

void preOrder(Node* root) {
	if (root) {
		cout << root->key << " ";
		preOrder(root->left);
		preOrder(root->right);
	}
}

int level = 0;

void inOrder(Node* root) {
	level++;
	if (root) {
		inOrder(root->right);

		int n = level;
		while (n--) cout << "   |   ";
		cout << root->key << "-" << root->height << endl;

		inOrder(root->left);
	}
	level--;
}

void postOrder(Node* root) {
	if (root) {
		postOrder(root->left);
		postOrder(root->right);
		cout << root->key << " ";
	}
}

int height(Node* p) { return p ? p->height : 0; }
int updateHeight(Node* p) { return 1 + max(height(p->left), height(p->right)); }

void insert(Node*& r, int k) {
	// --- Step 1: Find the node to insert
	// Base case: NULL -> new node
	if (r == NULL) r = getNode(k);
	else {
		// Smaller go to left <> larger go to right
		if (k < r->key) insert(r->left, k);
		else if (k > r->key) insert(r->right, k);

		// Update the height
		r->height = updateHeight(r);
	}

	// --- Step 2: Balance (recursively going up to the root)
	// Unbalanced on the left
	if (height(r->left) > height(r->right) + 1) {
		Node *q = r->left;
		
		// Left - Left case
		if (height(q->left) > height(q->right)) {
			r->left = q->right;
			q->right = r;

			r->height = updateHeight(r);
			q->height = updateHeight(q);

			r = q;
		}
		// Left - Right case
		else if (height(q->left) < height(q->right)) {
			Node* t = q->right;

			q->right = t->left;
			t->left = q;
			r->left = t->right;
			t->right = r;

			r->height = updateHeight(r);
			q->height = updateHeight(q);
			t->height = updateHeight(t);

			r = t;
		}
	}
	// Unbalanced on the right
	else if (height(r->left) + 1 < height(r->right)) {
		Node *q = r->right;

		// Right-Right case
		if (height(q->right) > height(q->left)) {
			r->right = q->left;
			q->left = r;
			
			r->height = updateHeight(r);
			q->height = updateHeight(q);

			r = q;
		}

		// Right-Left case
		else if (height(q->right) < height(q->left)) {
			Node* t = q->left;

			q->left = t->right;
			t->right = q;
			r->right = t->left;
			t->left = r;

			r->height = updateHeight(r);
			q->height = updateHeight(q);
			t->height = updateHeight(t);

			r = t;
		}
	}
}

void removeUtils(Node*& q, Node*& r) {
	if (r->right) { removeUtils(q, r->right); }
	else {
		q->key = r->key;
		q = r;
		r = r->left;
	}

	if (r) r->height = updateHeight(r);
}

void remove(Node*& r, int k) {
	// --- Step 1: Find and remove
	if (r) {
		if (k < r->key) remove(r->left, k);
		else if (k > r->key) remove(r->right, k);
		else {
			Node *q = r;
			if (r->left == NULL) {
				r = r->right;
			}
			else if (r->right == NULL) {
				r = r->left;
			}
			else {
				removeUtils(q, r->left);
			}
			delete q;
		}
	}

	if (r == NULL) return;

	// Update Height recursively
	r->height = updateHeight(r);

	// --- Step 2: Balance (recursively going up to the root)
	// Unbalanced on the left
	if (height(r->left) > height(r->right) + 1) {
		Node *q = r->left;

		// Left - Left case
		if (height(q->left) >= height(q->right)) {
			cout << "L-L at " << r->key << endl;
			r->left = q->right;
			q->right = r;

			r->height = updateHeight(r);
			q->height = updateHeight(q);

			r = q;
		}
		// Left - Right case
		else if (height(q->left) < height(q->right)) {
			cout << "L-R at " << r->key << endl;
			Node* t = q->right;

			q->right = t->left;
			t->left = q;
			r->left = t->right;
			t->right = r;

			r->height = updateHeight(r);
			q->height = updateHeight(q);
			t->height = updateHeight(t);

			r = t;
		}
	}
	// Unbalanced on the right
	else if (height(r->left) + 1 < height(r->right)) {
		Node *q = r->right;

		// Right-Right case
		if (height(q->right) >= height(q->left)) {
			cout << "R-R at " << r->key << endl;
			r->right = q->left;
			q->left = r;

			r->height = updateHeight(r);
			q->height = updateHeight(q);

			r = q;
		}

		// Right-Left case
		else if (height(q->right) < height(q->left)) {
			cout << "R-L at " << r->key << endl;
			Node* t = q->left;

			q->left = t->right;
			t->right = q;
			r->right = t->left;
			t->left = r;

			r->height = updateHeight(r);
			q->height = updateHeight(q);
			t->height = updateHeight(t);

			r = t;
		}
	}
}

void main() {
	srand(time(NULL));
	default_random_engine generator(time(NULL));
	uniform_int_distribution<int> distribution(0, 100);

	Node* root = NULL;
	int n;

	vector<int> data;

	cout << "Inserting... " << endl;
	cout << "Number of node(s): ";
	cin >> n;

	for (int i = 0; i < n; i++) {
		int x = distribution(generator);
		data.push_back(x);
		//cin >> x;
		cout << "Insert " << x << endl;
		insert(root, x);
		
		cout << endl;
		inOrder(root);
		cout << endl;
	}

	cout << "Removing... " << endl;
	cout << "Number of node(s): ";
	cin >> n;
	for (int i = 0; i < n; i++) {
		int x;
		auto it = data.begin() + uniform_int_distribution<int>(0, data.size() - 1)(generator);
		x = *it;

		//cin >> x;
		cout << "Remove " << x << endl;
		remove(root, x);

		cout << endl;
		inOrder(root);
		cout << endl;

		data.erase(it);
	}
}