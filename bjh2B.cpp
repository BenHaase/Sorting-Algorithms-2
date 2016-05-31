// Ben Haase
// 10/24/15
// CS3130 project 2 part B
// implementation of sorting algorithms on array of 50 random ints
// run time of sorting algorithms
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <time.h>

using namespace std;

void quicksort(int *, int, int);
void quicksortB(int *, int, int);
void quicksortC(int *, int, int);
int partition(int *, int, int);
int medianThree(int *, int, int, int);
int medianFive(int *, int *);
void swap(int *, int *);
int floor(int);
int * randomArrGen(int);
void viewArray(int *, int);
int * copyArray(int *, int s);
void resetArr(int ****, int ****, int *);
void run100();
void avgRunTime();
int main(int argc, char * argv[])
{
	srand(time(NULL));
	run100();
	avgRunTime();

	return 0;
}

//quick sort function
void quicksort(int * A, int p, int r){
	if (p < r){
		int q = partition(A, p, r);
		quicksort(A, p, q - 1);
		quicksort(A, q + 1, r);
	}
} 

//quick sort median of three
void quicksortB(int * A, int p, int r){
	if (p < r){
		int q;
		if ((r - p) > 1){
			q = floor(p + r);
			q = medianThree(A, q, p, r);
			swap(A[q], A[r]);
		}
		q = partition(A, p, r);
		quicksortB(A, p, q - 1);
		quicksortB(A, q + 1, r);
	}
}

//quick sort 
void quicksortC(int * A, int p, int r){
	if (p < r){
		int q;
		if ((r - p) > 15){
			int b[5], c[5];
			for (int i = 0; i < 5; i++){
				c[i] = rand() % (r - p) + p;
				b[i] = A[c[i]];
			}
			q = medianFive(b, c);
			swap(A[q], A[r]);
		}
		q = partition(A, p, r);
		quicksortC(A, p, q - 1);
		quicksortC(A, q + 1, r);
	}
}

//partition function
int partition(int * A, int p, int r){
	int t = 0;
	int x = A[r];
	int y = p - 1;
	for (int i = p; i < r; i++){
		if (A[i] <= x){
			y = y + 1;
			t = A[y];
			A[y] = A[i];
			A[i] = t;
		}
	}
	t = A[y + 1];
	A[y + 1] = A[r];
	A[r] = t;
	return y + 1;
}

//function to find the median of three values
int medianThree(int a[], int q, int p, int r){
	if (a[q] <= a[p]){
		if (a[q] >= a[r]) return q;
		else if (a[p] <= a[r]) return p;
		else return r;
	}
	else if (a[q] <= a[r]) return q;
	else if (a[p] >= a[r]) return p;
	else return r;
}

//function to find the median of five values
int medianFive(int * a, int * b){
	int t;
	for (int i = -1; i < 2; i++){
		for (int j = 4; j > i; j--){
			if (a[i] < a[i - 1]){
				t = a[i];
				a[i] = a[i - 1];
				a[i - 1] = t;
				t = b[i];
				b[i] = b[i - 1];
				b[i - 1] = t;
			}
		}
	}
	return b[2];
}

void swap(int * a, int * b){
	int t = *a;
	*b = *a;
	*a = t;
}

//floor function
int floor(int a){
	if (a % 2 == 0) return a / 2;
	else return (a - 1) / 2;
}

//function to generate an array of random numbers
int * randomArrGen(int s){
	int * a = new int[s];
	for (int i = 0; i < s; i++){
		a[i] = rand() % 9000 + 1000;
	}
	return a;
}

//function to print an array
void viewArray(int * a, int s){
	for (int i = 0; i < s; i++){
		if (i % 10 == 0 && i>0) cout << endl;
		cout << a[i] << " ";
	}
	cout << endl << endl;
}

//function to copy an array
int * copyArray(int * a, int s){
	int * b = new int[s];
	for (int i = 0; i < s; i++) b[i] = a[i];
	return b;
}

//function to reset sorted array to original unsorted array
void resetArr(int **** a, int **** b, int * s){
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 10; j++){
			for (int l = 0; l < 10; l++){
				delete[](b[i][j][l]);
				b[i][j][l] = copyArray(a[i][j][l], s[i]);
			}
		}
	}
}

//function to run sorting algorithms for an array of 50 random ints
void run100(){
	int n = 50;
	int p = 0;
	int r = n - 1;
	int * a = randomArrGen(n);
	int * b = copyArray(a, n);
	cout << "Original Array" << endl;
	viewArray(a, n);
	quicksort(b, p, r);
	cout << "Quick Sort" << endl;
	viewArray(b, n);
	delete[] b;
	b = copyArray(a, n);
	quicksortB(b, p, r);
	cout << "Quick Sort B" << endl;
	viewArray(b, n);
	delete[] b;
	b = copyArray(a, n);
	quicksortC(b, p, r);
	cout << "Quick Sort C" << endl;
	viewArray(b, n);
	cout << endl;
	delete[] a;
	delete[] b;
}

//function to measure the runtime of sorting algorithm for various input sizes
void avgRunTime(){
	clock_t start;
	clock_t end;
	double elapsed;
	int p = 0;
	int n[] = { 100, 1000, 10000 };
	int **** a = new int ***[3];
	int **** b = new int ***[3];
	double ** at = new double *[3];
	for (int i = 0; i < 3; i++){
		at[i] = new double[3];
		for (int k = 0; k < 3; k++) at[i][k] = 0;
		a[i] = new int **[10];
		b[i] = new int **[10];
		for (int l = 0; l < 10; l++){
			a[i][l] = new int *[10];
			b[i][l] = new int *[10];
			for (int j = 0; j < 10; j++){
				a[i][l][j] = randomArrGen(n[i]);
				b[i][l][j] = copyArray(a[i][l][j], n[i]);
			}
		}
	}

	//quicksort
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 10; j++){
			start = clock();
			for (int w = 0; w < 10; w++) quicksort(a[i][j][w], p, n[i] - 1);
			end = clock();
			elapsed = double(end - start) / CLOCKS_PER_SEC;
			at[0][i] = at[0][i] + elapsed;
			}
			at[0][i] = at[0][i] / 100;
	}

	resetArr(a, b, n);

	//quicksortB
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 10; j++){
			start = clock();
			for (int w = 0; w < 10; w++) quicksortB(a[i][j][w], p, n[i] - 1);
			end = clock();
			elapsed = double(end - start) / CLOCKS_PER_SEC;
			at[1][i] = at[1][i] + elapsed;
		}
		at[1][i] = at[1][i] / 100;
	}
	resetArr(a, b, n);

	//quicksortC
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 10; j++){
			start = clock();
			for (int w = 0; w < 10; w++) quicksortC(a[i][j][w], p, n[i] - 1);
			end = clock();
			elapsed = double(end - start) / CLOCKS_PER_SEC;
			at[2][i] = at[2][i] + elapsed;
		}
		at[2][i] = at[2][i] / 100;
	}

	for (int i = 0; i < 3; i++){
		cout << "Quick Sort ";
		if (i == 1) cout << "B";
		if (i == 2) cout << "C";
		cout << endl;
		for (int j = 0; j < 3; j++){
			cout << n[j] << ": ";
			if (n[j] == 100) cout << "  ";
			if (n[j] == 1000) cout << " ";
			cout << at[i][j] << endl;
		}
		cout << endl;
	}
}
