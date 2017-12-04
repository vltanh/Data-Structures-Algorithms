#include <iostream>
#include <cstring>
#include <string>
#include <algorithm>
using namespace std;

#define N 1000

void computeTable(char* P, int* pi, int m) {
	int k;
	pi[1] = k = 0;
	for (int q = 2; q <= m; q++) {
		while (k > 0 && P[k] != P[q - 1]) k = pi[k];
		if (P[k] == P[q - 1]) k++;
		pi[q] = k;
	}
}

void kmp(char* T, char* P) {
	int m = strlen(P);
	int *pi = new int[m + 1];
	computeTable(P, pi, m);

	int n = strlen(T);
	int k = 0;
	cout << "-- Result --" << endl;
	for (int i = 0; i < n; i++) {
		while (k > 0 && P[k] != T[i]) k = pi[k];
		if (P[k] == T[i]) k++;
		if (k == m) {
			cout << "Found at " << i - m + 1 << endl;
			k = pi[k];
		}
	}

	delete[] pi;
}

void BadCharacter(char* P, int *&D) {
	int m = strlen(P);
	D = new int[256];

	for (int i = 0; i < 256; i++) D[i] = m;
	for (int i = 0; i < m - 1; i++) D[P[i]] = m - 1 - i;
}

void horspool(char* T, char *P) {
	int n = strlen(T);
	int m = strlen(P);
	int k;

	int *D;
	BadCharacter(P, D);

	int i = m - 1;
	while (i < n) {
		k = 0;
		while (k < m && (T[i - k] == P[m - 1 - k] || P[m - 1 - k] == '?')) k++;
		if (k == m) cout << "Found at " << i - m + 1 << endl;
		i += min(D[T[i]], D['?']);
	}
}

void main() {
	char *T = new char[N];
	cout << "Input Text: ";
	cin.getline(T, N);

	char *P = new char[N];
	cout << "Input Pattern: ";
	cin.getline(P, N);

	//kmp(T, P);
	horspool(T, P);
}