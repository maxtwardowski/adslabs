#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
int main() {
	srand(time(NULL));
	int i, j, swapper, position, size;
	size = pow(2, 10);
	int array[size];

	for (i = 0; i < size; i++)
		array[i] = rand();

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
	
	// printing the sorted array
    /*for(i = 0; i < size; i++)
        printf("%d\t", array[i]);*/
    return 0;
}
