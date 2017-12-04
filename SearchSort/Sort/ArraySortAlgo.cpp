const long long n = 1000;
int *a = new int[n];

void swap(int *a, int *b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

// --- Interchange sort

void interchange_sort() {
	for (int i = 0; i < n - 1; i++)
		for (int j = 1; j < n; j++)
			if (a[i] < a[j])
				swap(&a[i], &a[j]);
}

// --- Selection Sort

void selection_sort() {
	for (int i = 0; i < n - 1; i++) {
		int imin = i, min = a[i];
		for (int j = i + 1; j < n; j++) {
			if (a[j] < min) {
				min = a[j];
				imin = j;
			}
		}
		swap(&a[i], &a[imin]);
	}
}

// --- Bubble Sort

void bubble_sort() {
	for (int i = 0; i < n - 1; i++)
		for (int j = 0; j < n - i - 1; j++)
			if (a[j] < a[j + 1])
				swap(&a[j], &a[j + 1]);
}

// --- Shaker Sort

void shaker_sort() {
	int i = 0;
	while (i < n / 2) {
		for (int j = i; j < n - i - 1; j++) 
			if (a[j] < a[j + 1])
				swap(&a[j], &a[j + 1]);

		for (int j = n - i - 2; j > i; j--) 
			if (a[j] > a[j - 1])
				swap(&a[j], &a[j - 1]);

		i++;
	}
}

// --- Quick sort (random + fixed)

void quick_sort(int left = 0, int right = n - 1) {
	int i = left, j = right;
	//int pivot = a[left + rand() % (right - left)];
	//int pivot = a[right];
	//int pivot = a[left];
	int pivot = a[left + (right - left) / 2];

	while (i <= j) {
		while (a[i] < pivot)
			i++;
		while (a[j] > pivot)
			j--;

		if (i <= j) {
			swap(&a[i], &a[j]);
			i++;
			j--;
		}
	}

	if (j > left) quick_sort(left, j);
	if (i < right) quick_sort(i, right);
}

// --- Radix sort

void radix_sort() {
	int t = 1;
	bool flag = true;

	int **b = new int*[10];
	for (int i = 0; i < 10; i++)
		b[i] = new int[n];

	while (flag) {
		int c[10] = { 0 };

		flag = false;
		for (int i = 0; i < n; i++) {
			int tmp = a[i] / t;
			b[tmp % 10][c[tmp % 10]++] = a[i];
			if (tmp != 0)
				flag = true;
		}

		int k = 0;
		for (int i = 0; i < 10; i++)
			for (int j = 0; j < c[i]; j++)
				a[k++] = b[i][j];

		t *= 10;
	}

	for (int i = 0; i < 10; i++)
		delete[]b[i];
	delete[]b;
}

// --- Binary Radix sort

int getBit(int s, int k) {
	return (s & (1 << k)) >> k;
}

void binary_radix_sort(int l = 0, int r = n - 1, int k = 16) {
	if (k == 0)
		return;

	int i = l, j = r;

	do {
		while (getBit(a[i], k) == 0) i++;
		while (getBit(a[j], k) == 1) j--;
		swap(&a[i], &a[j]);
	} while (i < j);
	swap(&a[i], &a[j]);

	if (j > l) binary_radix_sort(l, j, k - 1);
	if (i < r) binary_radix_sort(i, r, k - 1);
}

// --- Merge sort

void merge(int *arr, int l, int m, int r) {
	int nl = m - l + 1;
	int nr = r - m;

	int *al = new int[nl];
	int *ar = new int[nr];

	for (int i = 0; i < nl; i++)
		al[i] = arr[l + i];
	for (int i = 0; i < nr; i++)
		ar[i] = arr[m + 1 + i];

	int i, j, k;
	i = j = 0;
	k = l;
	while (i < nl && j < nr) {
		if (al[i] > ar[j])
			arr[k++] = al[i++];
		else
			arr[k++] = ar[j++];
	}

	while (i < nl)
		arr[k++] = al[i++];
	while (j < nr)
		arr[k++] = ar[j++];

	delete[]al; delete[]ar;
}

void merge_sort(int *arr = a, int l = 0, int r = n - 1) {
	if (l < r) {
		int m = l + (r - l) / 2;

		merge_sort(arr, l, m);
		merge_sort(arr, m + 1, r);
		merge(arr, l, m, r);
	}
}

// --- Heap sort

void shift(int l, int r) {
	int i = l; int j = i * 2; int x = a[i];
	while (j <= r) {
		if (j < r && a[j] > a[j + 1]) j++;
		if (x <= a[j]) break;
		a[i] = a[j]; i = j; j = i * 2;
	}
	a[i] = x;
}

void heap_sort() {
	int l = (n + 1) / 2 - 1;
	while (l + 1) {
		shift(l, n - 1);
		l--;
	}
	int r = n - 1;
	while (r) {
		swap(&a[0], &a[r]);
		shift(0, r);
		r--;
	}
}

// --- Insertion sort (linear + binary)

int binary_search_sort(int *a, int l, int r, int x) {
	int ans = -1;
	while (l <= r) {
		int m = l + (r - l) / 2;

		if (a[m] == x)
			return m + 1;
		else if (a[m] < x) {
			ans = m;
			l = m + 1;
		}
		else {
			r = m - 1;
		}
	}
	return ans;
}

void insertion_sort(int *arr = a, int size = n) {
	for (int i = 1; i < size; i++) {
		/*int j = i - 1;
		while (j >= 0 && arr[j] < arr[i])
		j--;*/
		int j = binary_search_sort(arr, 0, i - 1, arr[i]);
		int tmp = arr[i];
		for (int k = i; k > j; k--)
			arr[k] = arr[k - 1];
		arr[j + 1] = tmp;
	}
}

// --- Flash sort

void flashsort(int array[], int length)
{
	if (length == 0) return;
	int m = (int)((0.2 * length) + 5);

	int min, max, maxIndex;
	min = max = array[0];
	maxIndex = 0;

	for (int i = 1; i < length - 1; i += 2)
	{
		int small;
		int big;
		int bigIndex;

		if (array[i] < array[i + 1])
		{
			small = array[i];
			big = array[i + 1];
			bigIndex = i + 1;
		}
		else
		{
			big = array[i];
			bigIndex = i;
			small = array[i + 1];
		}

		if (big > max)
		{
			max = big;
			maxIndex = bigIndex;
		}

		if (small < min)
		{
			min = small;
		}
	}
	if (array[length - 1] < min)
	{
		min = array[length - 1];
	}
	else if (array[length - 1] > max)
	{
		max = array[length - 1];
		maxIndex = length - 1;
	}

	if (max == min)
	{
		return;
	}

	int* L = new int[m + 1];

	for (int t = 1; t <= m; t++)
	{
		L[t] = 0;
	}

	double c = (m - 1.0) / (max - min);
	int K;
	for (int h = 0; h < length; h++)
	{
		K = ((int)((array[h] - min) * c)) + 1;
		L[K] += 1;
	}

	for (K = 2; K <= m; K++)
	{
		L[K] = L[K] + L[K - 1];
	}

	int temp = array[maxIndex];
	array[maxIndex] = array[0];
	array[0] = temp;

	int j = 0;

	K = m;

	int numMoves = 0;

	while (numMoves < length)
	{
		while (j >= L[K])
		{
			j++;
			K = ((int)((array[j] - min) * c)) + 1;
		}

		int evicted = array[j];

		while (j < L[K])
		{
			K = ((int)((evicted - min) * c)) + 1;

			int location = L[K] - 1;

			int temp = array[location];
			array[location] = evicted;
			evicted = temp;

			L[K] -= 1;

			numMoves++;
		}
	}

	int threshold = (int)(1.25 * ((length / m) + 1));
	const int minElements = 30;

	for (K = m - 1; K >= 1; K--)
	{

		int classSize = L[K + 1] - L[K];

		if (classSize > threshold && classSize > minElements)
		{
			flashsort(&array[L[K]], classSize);
		}
		else
		{
			if (classSize > 1)
			{
				insertion_sort(&array[L[K]], classSize);
			}
		}
	}

	delete[] L;
}

void bubble_sort_2() {
	int lim = n - 1;
	int lim_tmp;
	while (true) {
		for (int i = 0; i < lim; i++) {
			if (a[i] > a[i + 1]) {
				swap(&a[i], &a[i + 1]);
				lim_tmp = i + 1;
			}
		}
		lim = lim_tmp;
	}
}