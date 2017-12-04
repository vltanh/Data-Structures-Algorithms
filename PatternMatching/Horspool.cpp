#include <iostream>
#include <cstring>
#include <string>
#include <algorithm>
using namespace std;

#define N 1000

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

	horspool(T, P);
}