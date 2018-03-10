// SORTING_STEP1.C 

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "maxheap.h"


void print(int* a, int n)
// Print contents of array
{
	int i;
	for (i = 0; i < n; i++)	printf("%d ", a[i]);
	printf("\n");
}//print()


void swap(int *a, int *b)
// Swap two integers.  Parameters are pointers to integers, so integers
// can be anywhere.
{
	int t = *a;    *a = *b;    *b = t;
}//swap()


 //*******************Insertion Sort**************************
long insertionSort(int *array, int n) {
	int i, j;
	int ctr = 0;
	for (i = 1; i < n; i++) {
		for (j = i; j > 0 && (array[j - 1] > array[j]); j--) {
			swap(&array[j], &array[j - 1]);
			ctr++;
		}
	}
	return ctr;
}


long insertionSortQ(int *array, int left, int right) {
	int i, j;
	int ctr = 0;
	for (i = left + 1; i < right + 1; i++) {
		for (j = i; j > 0 && (array[j - 1] < array[j]); j--) {
			swap(&array[j], &array[j - 1]);
			ctr++;
		}
	}
	return ctr;
}


//*******************Bubble Sort**************************
long bubbleSort(int* array, int n) {
	int i, j, swapped;
	long ctr = 0;

	for (i = 0; i < n; ++i) {
		swapped = 0;
		for (j = n - 1; j > i; --j) {
			if (array[j] > array[j - 1]) {
				swapped = 1;
				swap(&array[j], &array[j - 1]);
				ctr++;
			}
		}
		if (swapped == 0) break;
	}
	return ctr;
}


//*******************Quick Sort**************************

int partition(int* a, int left, int right, long* swaps) {
	int i = left;
	int j = right - 1;
	int pivot_index = left + (right - left) / 2;
	int pivot = a[pivot_index];
	swap(&a[right], &a[pivot_index]);
	*swaps = *swaps + 1;
	while (i < j) {
		while (a[i] > pivot) i++;
		while (a[j] < pivot) j--;
		if (i <= j) {
			swap(&a[i], &a[j]);
			*swaps = *swaps + 1;
			i++;
			j--;
		}
	}
	a[right] = a[i];
	a[i] = pivot;
	*swaps = *swaps + 1;
	return i;
}


long quickSort(int* a, int left, int right) {
	long swaps = 0;
	if (right - left > 2) {
		int pivot = partition(a, left, right, &swaps);
		swaps += quickSort(a, left, pivot - 1);
		swaps += quickSort(a, pivot + 1, right);
	}
	else {
		swaps += insertionSortQ(a, left, right);
	}
	return swaps;
}
//*******************Heap Sort**************************

long heapSort(int* a, int n) {
	Heap* h = heapify2(a, n);
	long swaps = 0;
	int i;
	for (i = n - 1; i > 0; i--) {
		swap(&h->a[0], &h->a[i]);
		swaps++;
		h->last--;
		swaps += reheapDown(h, 0);
	}
	return swaps;
}
//*******************Merge Sort**************************

void merge(int*a, int start, int middle, int end, int*b, long *swaps) {
	int i;
	int j = start;
	int k = middle + 1;
	for (i = start; j <= middle && k <= end; i++) {
		if (a[j] > a[k]) {
			b[i] = a[j];
			j++;
			*swaps += 1;
		}
		else {
			b[i] = a[k];
			k++;
			*swaps += 1;
		}
	}
	while (j <= middle) {
		b[i++] = a[j++];
		*swaps += 1;
	}
	while (k <= end) {
		b[i++] = a[k++];
		*swaps += 1;
	}
	for (i = start; i <= end; i++)
		a[i] = b[i];
}

//*******************Merge Sort**************************

void mergeSortR(int* a, int start, int end, int* b, long* swaps) {
	int		middle;
	if (start >= end) return;

	middle = start + (end - start) / 2;
	mergeSortR(a, start, middle, b, swaps);
	mergeSortR(a, middle + 1, end, b, swaps);
	merge(a, start, middle, end, b, swaps);
}

long mergeSort(int* a, int n) {
	int* b = malloc(sizeof(int) * n);
	int i;
	long swaps = 0;
	for (i = 0; i < n; i++) {
		b[i] = a[i];
	}
	mergeSortR(a, 0, n - 1, b, &swaps);
	return swaps;
}
//*******************Bucket Sort**************************

void bucketSort(int *a, int n, int b) {
	int* buckets = malloc(sizeof(int) * b);
	int i, j, k;
	for (i = 0; i < b; i++) // initialize the buckets array
		buckets[i] = 0;
	for (i = 0; i < n; i++) // count number of  repeated data in each bucket
		buckets[a[i]]++;
	i = 0;
	for (j = 0; j < b; j++) { // loop for every bucket
		for (k = 0; k < buckets[j]; k++) {
			a[i] = j;
			i++;
		}
	}
}

//*******************Radix Sort**************************

long radixSort(int *a, int n, int p) {
	int i, j, k;
	for (k = 0; k < p; k++) {
		int count[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
		int tmp[7] = {NULL};
		int offset[10];
		for (i = 0; i < n; i++)
			count[(a[i] / (int)pow(10, k)) % 10]++;
		//---------------------------------------------------
		offset[9] = 0;
		for (i = 8; i >= 0; i--) {
			offset[i] = 0;
			for (j = i; j < 10; j++) {
				offset[i] += count[j];
			}
		}
		for (i = 0; i < n; i++) {
			int temp_1 = (a[i] / (int)pow(10, k)) % 10 + 1;
			if (temp_1 == 10)
				temp_1 = 9;
			int temp_2 = offset[temp_1];
			while (tmp[temp_2] != NULL && temp_2 <= 6)
				temp_2++;
			tmp[temp_2] = a[i];
		}
		for (i = 0; i < n; i++) {
			a[i] = tmp[i];
		}
	}
	return 0;
}


void initArray(int* a) {
	a[0] = 10;
	a[1] = 24;
	a[2] = 5;
	a[3] = 32;
	a[4] = 1;
	a[5] = 84;
	a[6] = 19;
}


int main() {
	int a[] = { 10, 24, 5, 32, 1, 84, 19 };
	int n = 7;
	long swaps = 0;
	printf("Before   Sorting:\t\t");
	print(a, n);
	printf("*****\n");

	swaps = insertionSortQ(a, 0, n - 1);
	printf("After Insertion Sort:\t\t");
	print(a, n);
	printf("Number of swaps: %ld\n*****\n", swaps);

	initArray(a);
	swaps = bubbleSort(a, n);
	printf("After Bubble Sort:\t\t");
	print(a, n);
	printf("Number of swaps: %ld\n*****\n", swaps);

	initArray(a);
	swaps = quickSort(a, 0, n - 1);
	printf("After Quick Sort:\t\t");
	print(a, n);
	printf("Number of swaps: %ld\n*****\n", swaps);


	initArray(a);
	swaps = heapSort(a, n);
	printf("After Heap  Sort:\t\t");
	print(a, n);
	printf("Number of swaps: %ld\n*****\n", swaps);


	initArray(a);
	swaps = mergeSort(a, n);
	printf("After Merge Sort:\t\t");
	print(a, n);
	printf("Number of swaps: %ld\n*****\n", swaps);


	initArray(a);
	swaps = radixSort(a, n, 3);
	printf("After Radix Sort:\t\t");
	print(a, n);
	printf("Number of swaps: %ld\n", swaps);

	system("pause");

	return 0;
}
