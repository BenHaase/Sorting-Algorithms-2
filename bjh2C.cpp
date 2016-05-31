// Ben Haase
// 11/2/15
// CS3130 project 2 part C
// implementation of heap sort on array of random ints
// run time of heap sort (bottom up) 

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <time.h>

using namespace std;

double heapSort(int *, int);
void maxHeapify(int *, int, int);
void buildMaxHeap(int *, int);
int floor(int);
int * randomArrGen(int);
void viewArray(int *, int);
int * copyArray(int *, int s);
void run100();
void avgRunTime();
int main(int argc, char * argv[])
{
	srand(time(NULL));
	run100();
	avgRunTime();

	return 0;
}

//Heap Sort function
double heapSort(int * a, int n){
	clock_t s;
	clock_t e;
	double elap;
	//float elap;
	s = clock();
	buildMaxHeap(a, n);
	e = clock();
	elap= double(e - s) / CLOCKS_PER_SEC;
	//elap = float(e - s) / CLOCKS_PER_SEC;
	for (int i = n; i > -1; i--){
		int t = a[0];
		a[0] = a[i];
		a[i] = t;
		n--;
		maxHeapify(a, 0, n);
	}
	return elap;
}

//Max-Heapify function
void maxHeapify(int * a, int i, int n){
	int largest = i;
	int l = 2 * i;
	int r = (2 * i) + 1;

	if (l <= n && a[l] > a[i]){
		largest = l;
	}
	else{
		largest = i;
	}
	if (r <= n && a[r] > a[largest]){
		largest = r;
	}
	if (largest != i){
		int t = a[i];
		a[i] = a[largest];
		a[largest] = t;
		maxHeapify(a, largest, n);
	}
}

//Build-Max-Heap function
void buildMaxHeap(int * a, int n){
	for (int i = floor(n); i > -1; i--) maxHeapify(a, i, n);
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
void viewArray(int * a, int n){
	for (int i = 0; i < n; i++){
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

//function to run sorting algorithm for an array of random ints
void run100(){
	int n = 50;
	int * a = randomArrGen(n);
	cout << "Original Array" << endl;
	viewArray(a, n);
	heapSort(a, n - 1);
	cout << "Heap Sort" << endl;
	viewArray(a, n);
	cout << endl;
}

//function to measure the runtime of sorting algorithm for various input sizes
void avgRunTime(){
	clock_t start;
	clock_t end;
	double elapsed;
	int n[] = { 1000, 10000, 100000, 1000000 };
	double at[4];
	double atbh[4];
	int * a[4][10];
	for (int i = 0; i < 4; i++){
		at[i] = 0;
		atbh[i] = 0;
		for (int j = 0; j < 10; j++){
			a[i][j] = randomArrGen(n[i]);
		}
	}

	//heapsort timing
	for (int i = 0; i < 4; i++){
			for (int k = 0; k < 10; k++){
				start = clock();
				for(int x = 0; x < 10; x++) atbh[i] += heapSort(a[i][k], n[i] - 1);
				end = clock();
				elapsed = double(end - start) / CLOCKS_PER_SEC;
				at[i] = at[i] + elapsed;
			}
			at[i] = at[i] / 100;
			atbh[i] = atbh[i] / 100;
	}
	cout << "Heap Sort Timings" << endl;
	for (int i = 0; i < 4; i++){
		cout << "N = ";
		for (int j = i; j < 4; j++) cout << " ";
		cout << n[i] << ":" << endl;
		cout << "  Build Heap: " << atbh[i] << endl;
		cout << "  Total     : " << at[i] << endl;
	}
	cout << endl;
}
