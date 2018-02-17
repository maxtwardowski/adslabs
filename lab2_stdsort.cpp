#include <bits/stdc++.h>
#include <math.h>
#include <time.h>
using namespace std;
 
int main()
{
    int size;
    size = pow(2, 16);
    int array[size];
    int i, j;
    //ascending
	//for (i = 0, i < size; i < size; i++)
	//	array[i] = i;
	//descending
	for (i = 0, j = size; i < size; i++, --j)
		array[i] = j;
	//random
	//for (i = 0; i < size; i++)
	//	array[i] = rand();	
    int n = sizeof(array)/sizeof(array[0]);
 
    sort(array, array + n);
 
    //cout << "Array after sorting using "
         //"default sort is : \n";
    //for (int i = 0; i < n; ++i)
        //cout << array[i] << " ";
 
    return 0;
} 
