#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void selectionSort(int array[], int size) {
	int i, j, swapper, position;
	for (i = 0; i < size - 1; i++){
        position = i; //first element
        for (j = i + 1; j < size; j++){
            if (array[position] > array[j])
            position = j;
        }
        if (position != i){
            swapper = array[i];
            array[i] = array[position];
            array[position] = swapper;
        }
    }
}

int find_smaller(int x, int y) { 
	if (x < y)
		return x;
	else
		return y;
}

void mergeForTile(int array[], int subarray1[], int subarray2[], int subsize1, int subsize2) {
	int i, j, k;
	for (i = 0, j = 0, k = 0; i < subsize1 && j < subsize2; k++) {
		if (subarray1[i] <= subarray2[j]) {
            array[k] = subarray1[i];
            i++;
        } else {
            array[k] = subarray2[j];
            j++;
        }
	}
	for (i; i < subsize1; i++, k++)
		array[k] = subarray1[i];
		
	for (j; j < subsize2; j++, k++)
		array[k] = subarray2[j];
}

void merge(int array[], int p, int q, int r) {
    int i, j, k;
    int n1 = q - p + 1;
    int n2 =  r - q;
    int subarray1[n1], subarray2[n2];
 
    for (i = 0; i < n1; i++)
        subarray1[i] = array[p + i];
    for (j = 0; j < n2; j++)
        subarray2[j] = array[q + 1 + j];
    
    for (i = 0, j = 0, k = p; i < n1 && j < n2; k++) {
    	if (subarray1[i] <= subarray2[j]) {
            array[k] = subarray1[i];
            i++;
        } else {
            array[k] = subarray2[j];
            j++;
        }
	}
	for (i; i < n1; i++, k++)
		array[k] = subarray1[i];
		
	for (j; j < n2; j++, k++)
		array[k] = subarray2[j];
}
 
void mergeSort(int array[], int p, int r) {
    if (p < r) {
        int q = (p + r) / 2;
        mergeSort(array, p, q);
        mergeSort(array, q + 1, r);
        merge(array, p, q, r);
    }
}


void bottomUpMergeSort(int array[], int size) {
	int subarray_size, index_start; 
	for (subarray_size = 1; subarray_size <= size - 1; subarray_size = subarray_size * 2) {
		for (index_start = 0; index_start < size - 1; index_start = index_start + subarray_size * 2) {
			int index_middle = index_start + subarray_size - 1;
			int index_end = find_smaller(index_start + subarray_size * 2 - 1, size - 1);
			merge(array, index_start, index_middle, index_end);
		}
	}
}

void tiledMergeSort (int array[], int size) {
	int subsize1, subsize2;
	if (size % 2 == 0) {
		subsize1 = size / 2;
		subsize2 = size / 2;
	} else {
		subsize1 = size / 2 + 1;
		subsize2 = size / 2;
	}
	
	int subarray1[subsize1], subarray2[subsize2], i, j;
	for (i = 0; i < subsize1; i++)
		subarray1[i] = array[i];
	for (j = 0, i = subsize1; j < subsize2; i++, j++)
		subarray2[j] = array[i];
		
	selectionSort(subarray1, subsize1);
	selectionSort(subarray2, subsize2);
		
	mergeForTile(array, subarray1, subarray2, subsize1, subsize2);
}

int main() {
	srand(time(NULL));
	int size, i, j;
	size = pow(2, 16);
	int array[size];
	
	//ascending
	//for (i = 0, i < size; i < size; i++)
	//	array[i] = i;
	//descending
	//for (i = 0, j = size; i < size; i++, --j)
	//	array[i] = j;
	//random
	for (i = 0; i < size; i++)
		array[i] = rand();	
	
	/*printf("Original: \n");
    for (i = 0; i < size; i++)
		printf("%d\t", array[i]);*/
 
 	//SORTING METHOD HERE
    //mergeSort(array, 0, size);
	//bottomUpMergeSort(array, size);
	tiledMergeSort(array, size);
 	
    /*printf("\nSorted: \n");
	for (i = 0; i < size; i++)
		printf("%d\t", array[i]);*/
	
    return 0;
}
