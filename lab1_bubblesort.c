#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
int main() {
	//srand(time(NULL));
	int size, i, j, swapper;
	long swaps_total, swaps_iteration;
	size = pow(2, 16);
	int array[size];
	swaps_total = 0;
	
	//random array
	/*for (i = 0; i < size; i++) {
		array[i] = rand();
	}*/
	
	//asceding array
	/*for (i = 0; i < size; i++) {
		array[i] = i;
	}*/
	
	//descending array 
	for (i = size, j = 0; i > 0; --i, j++) {
		array[j] = i;
	}
	
	/*printf("Array before sorting:\n");
	for (i = 0; i < size; i++) {
		printf("%d\n", array[i]);
	}*/
 
  	for (i = 0 ; i < size; i++) {
  		swaps_iteration = 0;
    	for (j = 0 ; j < size - i - 1; j++) {
      		if (array[j] > array[j + 1]) {
			    swapper = array[j];
        		array[j] = array[j + 1];
        		array[j + 1] = swapper;
				swaps_total++; // number of swaps in the whole run
				swaps_iteration++; // number of swaps in a single iteration
      		}
    	}
    	if (swaps_iteration == 0)
    		break;
  	}
 
	/*printf("Array after sorting:\n");
  	for ( i = 0 ; i < size ; i++ )
		printf("%d\t", array[i]);
	*/

	printf("There have been %ld swaps performed while bubble sorting", swaps_total);
	return 0;
}
