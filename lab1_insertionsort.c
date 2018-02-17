#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
int main() {
	srand(time(NULL));
	int size, value2insert, i, j;
	size = pow(2, 10);
	int array[size];

	//building array
	for (i = 0; i < size; i++) {
		array[i] = rand();
	}
	
	for(i = 1; i < size; i++) {
		value2insert = array[i];
		j = i - 1;
		while(value2insert < array[j] && j >= 0) {
			array[j + 1] = array[j];
			--j;
		}
		array[j + 1] = value2insert;
	}
	/*printf("Sorted array:");
	for(i = 0; i < size; i++)
		printf("%d\t", array[i]);*/
	return 0;
}

