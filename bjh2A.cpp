// Ben Haase
// 10/24/15
// CS3130 project 2 part A
// implementation of sorting algorithms on array of 100 random ints
// run time of sorting algorithms

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <time.h>

using namespace std;

void mergeSort(int *, int, int);
void merge(int *, int, int, int);
int * mergeArrays(int *, int *, int, int);
int floor(int);
int * randomArrGen(int);
void viewArray(int *, int);
int * copyArray(int *, int s);
void resetArr(int ***, int ***, int *);
int * appendArray(int *, int *, int, int);
void run100();
void avgRunTime();
int main(int argc, char * argv[])
{
	srand(time(NULL));
	run100();
	avgRunTime();

	return 0;
}

//merge sort function
void mergeSort(int * A, int p, int r){
	int q = 0;
	if (p < r){
		q = floor(p + r);
		mergeSort(A, p, q);
		mergeSort(A, q + 1, r);
		merge(A, p, q, r);
	}

}

//merge function
void merge(int * A, int p, int q, int r){
	int n1 = q - p + 1;
	int n2 = r - q;
	int * L = new int[n1 + 1];
	int * R = new int[n2 + 1];
	for (int i = 0; i < n1; i++){
		L[i] = A[p + i];
	}
	for (int i = 0; i < n2; i++){
		R[i] = A[q + i + 1];
	}
	L[n1] = 100000;
	R[n2] = 100000;
	int ir = 0;
	int il = 0;
	for (int i = p; i < r + 1; i++){
		if (L[il] <= R[ir]){
			A[i] = L[il];
			il++;
		}
		else{
			A[i] = R[ir];
			ir++;
		}
	}
	delete[] L, R;
}

//function to take in two arrays and merge them into one
int * mergeArrays(int * L, int * R, int nl, int nr){
	int * A = new int[nl + nr];
	int ir = 0;
	int il = 0;
	for (int i = 0; i < (nl + nr); i++){
		if ((il < nl) && (ir < nr)){
			if (L[il] <= R[ir]){
				A[i] = L[il];
				il++;
			}
			else{
				A[i] = R[ir];
				ir++;
			}
		}
		else if (il < nl){
			A[i] = L[il];
			il++;
		}
		else{
			A[i] = R[ir];
			ir++;
		}
	}
	return A;
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
void resetArr(int *** a, int *** b, int * s){
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 10; j++){
			delete[] b[i][j];
			b[i][j] = copyArray(a[i][j], s[i]);
		}
	}
}

//function to append array b to array a
int * appendArray(int * a, int * b, int na, int nb){
	int * c = new int[na + nb];
	for (int i = 0; i < na; i++) c[i] = a[i];
	for (int i = 0; i < nb; i++) c[i + na] = b[i];
	return c;
}

//function to run sorting algorithm for an array of 100 random ints
void run100(){
	int n = 100;
	int m = 10;
	int p = 0;
	int r = n - 1;
	int mr = m - 1;
	int * a = randomArrGen(n);
	int * b = randomArrGen(m);
	cout << "Original Arrays" << endl;
	viewArray(a, n);
	viewArray(b, m);
	mergeSort(a, p, r);
	cout << "Merge Sort" << endl;
	viewArray(a, n);
	mergeSort(b, p, mr);
	viewArray(b, m);
	int * c = mergeArrays(a, b, n, m);
	cout << "Merged" << endl;
	viewArray(c, n + m);
	cout << endl;
}

//function to measure the runtime of sorting algorithm for various input sizes
void avgRunTime(){
	clock_t start;
	clock_t end;
	double elapsed;
	int p = 0;
	int * t;
	int n[] = { 1000, 10000, 100000};
	int m[] = { 25, 50, 100};
	int *** na = new int **[3];
	int *** ma = new int **[3];
	int *** nb = new int **[3];
	int *** mb = new int **[3];
	double ** at = new double *[3];
	double ** ats = new double *[3];
	for (int i = 0; i < 3; i++){
		at[i] = new double[3];
		ats[i] = new double[3];
		for (int j = 0; j < 3; j++){
			at[i][j] = 0;
			ats[i][j] = 0;
		}
	}
	for (int i = 0; i < 3; i++){
		na[i] = new int *[10];
		ma[i] = new int *[10];
		nb[i] = new int *[10];
		mb[i] = new int *[10];
		for (int j = 0; j < 10; j++){
				na[i][j] = randomArrGen(n[i]);
				ma[i][j] = randomArrGen(m[i]);
				nb[i][j] = copyArray(na[i][j], n[i]);
				mb[i][j] = copyArray(ma[i][j], m[i]);
		}
	}
	
	//merging two arrays
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			for (int k = 0; k < 10; k++){
				start = clock();
				mergeSort(nb[i][k], p, n[i] - 1);
				mergeSort(mb[j][k], p, m[j] - 1);
				t = mergeArrays(nb[i][k], mb[j][k], n[i], m[i]);
				end = clock();
				elapsed = double(end - start) / CLOCKS_PER_SEC;
				at[i][j] = at[i][j] + elapsed;
				delete[] t;
			}
			at[i][j] = at[i][j] / 10;
			resetArr(na, nb, n);
		}
		resetArr(ma, mb, m);
	}

	cout << "MergeSort (merge two arrays)" << endl;
	for (int i = 0; i < 3; i++){
		cout << "N = " << n[i] << ":" << endl;
		for (int j = 0; j < 3; j++){
			cout << "    " << "M = ";
			if (m[j] == 25 || m[j] == 50) cout << " ";
			cout << m[j];
			cout << ": " << at[i][j] << endl;
		}
	}
	cout << endl;

	//resorting
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			for (int k = 0; k < 10; k++){
				start = clock();
				mergeSort(nb[i][k], p, n[i] - 1);
				mergeSort(mb[j][k], p, m[j] - 1);
				t = appendArray(nb[i][k], mb[j][k], n[i], m[j]);
				mergeSort(t, p, n[i] + m[j] - 1);
				end = clock();
				elapsed = double(end - start) / CLOCKS_PER_SEC;
				ats[i][j] = ats[i][j] + elapsed;
				delete[] t;
			}
			ats[i][j] = ats[i][j] / 10;
			resetArr(na, nb, n);
		}
		resetArr(ma, mb, m);
	}

	cout << "MergeSort (resorting)" << endl;
	for (int i = 0; i < 3; i++){
		cout << "N = " << n[i] << ":" << endl;
		for (int j = 0; j < 3; j++){
			cout << "    " << "M = ";
			if (m[j] == 25 || m[j] == 50) cout << " ";
			cout << m[j];
			cout << ": " << ats[i][j] << endl;
		}
	}
}
