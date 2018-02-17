#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

int main () {
	int n, size, i, j;
	size = pow(2, 13);
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
	
	//printf("Original: \n");
	//for( n = 0 ; n < size; n++ ) 
	//	printf("%d ", array[n]);
	
	
	qsort(array, size, sizeof(int), cmpfunc);
	
	//printf("\nSorted: \n");
	//for( n = 0 ; n < size; n++ ) 
		//printf("%d ", array[n]);
  
   return(0);
}
