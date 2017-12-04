#include <iostream>
using namespace std;

struct Node {
	int key;
	Node* next;
};

// Utils

Node* getNode(int k) {
	Node *p = new Node;
	p->key = k;
	p->next = NULL;
	return p;
}

// Quicksort

void quick_sort(Node *&h, Node *&t) {
	if (h == NULL || h->next == NULL) return;

	// Seperate the first element, make it the pivot
	Node *p = h;
	Node *q = h->next;
	p->next = NULL;

	// Split the list into lists of higher and lower than p
	Node *lt = getNode(-1);
	Node *rt = getNode(-1);
	Node *lh = lt, *rh = rt;
	while (q) {
		if (q->key < p->key) {
			lt->next = q;
			lt = lt->next;
		}
		else {
			rt->next = q;
			rt = rt->next;
		}
		q = q->next;
	}
	lt->next = rt->next = NULL;

	quick_sort(lh->next, lt);
	quick_sort(rh->next, rt);

	if (lh->next) {
		lt->next = p;
		h = lh->next;
	}
	else
		h = p;

	if (rh->next) {
		p->next = rh->next;
		t = rt;
	}
	else
		t = p;

	delete lh;
	delete rh;
}

// Selection sort

void selection_sort(Node*& h, Node*& t) {
	Node *nh = getNode(-1);
	Node *nt = nh;

	Node *k = getNode(-1);
	k->next = h;
	h = k;

	int step = 100000;
	while (step--) {
		Node *p = h->next;
		Node *prev = h;

		Node *p_max = h->next;
		Node *prev_max = h;

		while (p) {
			if (p->key > p_max->key) {
				prev_max = prev;
				p_max = p;
			}
			prev = p;
			p = p->next;
		}

		prev_max->next = p_max->next;

		nt->next = p_max;
		nt = p_max;
	}

	h = nh->next;
	t = nt;
	delete nh;
	delete k;
}

// Insertion sort

void insertion_sort(Node*& h, Node*& t) {
	Node *k = new Node;
	k->key = -1;
	k->next = h;
	h = k;

	Node *p = h;
	while (p) {
		Node *next = p->next;

		p->next = NULL;

		Node *np = h->next;
		Node *prev = h;

		while (np && p->key > np->key) {
			prev = np;
			np = np->next;
		}

		prev->next = p;
		p->next = np;

		p = next;
	}
}

// Radix Sort

int nDigits(int n) {
	int s = 0;
	while (n) {
		s++;
		n /= 10;
	}
	return s;
}

void radix_sort(Node *&h, Node *&t) {
	if (h == NULL || h->next == NULL) return;

	Node *bh[10], *bt[10];
	for (int i = 0; i < 10; i++) {
		bh[i] = getNode(-1);
		bt[i] = bh[i];
	}
	int exp = 1;

	Node *p = h;
	int k = -1;
	while (p) {
		int d = nDigits(p->key);
		if (d > k) k = d;
		p = p->next;
	}

	Node *bp[10];
	while (k) {
		p = h;
		for (int i = 0; i < 10; i++)
			bp[i] = bh[i];

		int d;
		while (p) {
			d = (p->key / exp) % 10;
			bp[d]->next = p;
			bp[d] = bp[d]->next;
			p = p->next;
		}

		for (int i = 0; i < 10; i++) {
			bt[i] = bp[i];
			bt[i]->next = NULL;
		}

		int i, j;

		i = 0;
		while (i < 10) {
			j = i + 1;
			while (bh[j]->next == NULL) j++;
			if (j < 10) bt[i]->next = bh[j]->next;
			i = j;
		}

		i = 0;
		while (bh[i]->next == NULL) i++;
		h = bh[i]->next;

		j = 9;
		while (bh[j]->next == NULL) j--;
		t = bt[j];

		exp *= 10;
		k--;
	}

	for (int i = 0; i < 10; i++)
		delete bh[i];
}

// Merge Sort

void splitList(Node *head, Node *&left, Node *&right) {
	if (head == NULL || head->next == NULL) {
		left = head;
		right = NULL;
	}
	else {
		Node *fast, *slow;
		slow = head;
		fast = head->next;
		while (fast) {
			fast = fast->next;
			if (fast) {
				slow = slow->next;
				fast = fast->next;
			}
		}
		left = head;
		right = slow->next;
		slow->next = NULL;
	}
}

Node* merge(Node *left, Node *right) {
	Node *nHead = new Node;
	Node *merged = nHead;

	while (left && right) {
		if (left->key < right->key) {
			merged->next = left;
			left = left->next;
		}
		else {
			merged->next = right;
			right = right->next;
		}
		merged = merged->next;
	}

	merged->next = (left) ? left : right;
	return nHead->next;
}

void merge_sort(Node*& head) {
	if (head == NULL || head->next == NULL)
		return;

	Node *left, *right;
	splitList(head, left, right);

	merge_sort(left);
	merge_sort(right);
	head = merge(left, right);
}