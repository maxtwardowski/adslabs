#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <math.h>
#include <windows.h>
#include <cstdio>
#include <cmath>
using namespace std;

//DJB2 HASHING FUNCTION
/*unsigned long hash(string str){
    unsigned long hash = 5381;
    int c;
    for (int i = 0; i < str.length(); ++i) {
        c = (int) str[i];
        hash = ((hash << 5) + hash) + c; 
    }
    return hash;
}*/

//SDBM HASHING FUNCTION
/*unsigned long hash(string str) {
    unsigned long hash = 0;
    int c;
    for (int i = 0; i < str.length(); ++i) {
    	c = (int) str[i];
        hash = c + (hash << 6) + (hash << 16) - hash;
    }
    return hash;
}*/

unsigned long hash(string s) {
	int size, hashvalue;
	size = s.length();
	if (size == 1) {
		hashvalue = 37 * int(s[0]);
	} else if (size == 2) {
		hashvalue = 37 * int(s[0]) + pow(37, 2) * int(s[1]);
	} else if (size == 3) {
		hashvalue = 37 * int(s[0]) + pow(37, 2) * int(s[1]) + pow(37, 3) * int(s[2]);
	} else {
		hashvalue = 37 * int(s[0]) + pow(37, 2) * int(s[1]) + pow(37, 3) * int(s[2]) + pow(37, 4) * int(s[3]);
	}
	return hashvalue;
}

long average(int array[], int size) {
	int sum = 0, avg;
	for (int i = 0; i < size; i++)
		sum += array[i];
	avg = sum / size;
	return avg;
}

long minimum(int array[], int size) {
	int min;
	min = array[0];
	for (int i = 0; i < size; i++) {
		if (array[i] < min)
			min = array[i];
	}
	return min;
}

long maximum(int array[], int size) {
	int max;
	max = array[0];
	for (int i = 0; i < size; i++) {
		if (array[i] > max)
			max = array[i];
	}
	return max;
}

double average_precise(double array[], int size) {
	double sum = 0, avg;
	for (int i = 0; i < size; i++)
		sum += array[i];
	avg = sum / size;
	return avg;
}

int main(int argc, char** argv) {
	LARGE_INTEGER ticksPerSecond;
	LARGE_INTEGER tick1;   
	LARGE_INTEGER tick2;   
	LARGE_INTEGER time1;   
	LARGE_INTEGER time2;  
	
	ifstream input("words20k.txt");
	int i, j;
	int size = 20000;
	string A[size], H[24000];
	string line;
	if(input.is_open()) {
		while(getline(input, line)) {
			A[i++] = line;
		}
	}
	
	for (i = 0; i < 24000; i++)
		H[i] = "";

	//time measurement initialization
	QueryPerformanceFrequency(&ticksPerSecond);
	QueryPerformanceCounter(&tick1);
	double start = double(tick1.QuadPart)/ticksPerSecond.QuadPart;
	
	for (i = 0; i < 20000; i++) {
		j = 0;
		while (1) {
			if ((hash(A[i]) % 24000) + j < 24000) {
				if (H[(hash(A[i]) % 24000) + j].empty() == 1) {
					H[(hash(A[i]) % 24000) + j] = A[i];
					break;
				} else {
					j++;
				}
			} else if ((hash(A[i]) % 24000) + j >= 24000) {
				j = j - 24000;
			}
		}
		//timestamps printing
		if (i % 500 == 499) {
			QueryPerformanceCounter(&tick2);
			double end = double(tick2.QuadPart)/ticksPerSecond.QuadPart;
			double diff = end - start;  
			cout << diff << "s" << endl;
		}
	}
	
	string word;
	double times[1000];
	int collisions[1000];
	int perfectindex, collisionscounter;
	/*for (i = 12000; i < 12999; i++) {
		QueryPerformanceFrequency(&ticksPerSecond);
		QueryPerformanceCounter(&tick1);
		double start = double(tick1.QuadPart)/ticksPerSecond.QuadPart;
		word = A[i];
		perfectindex = hash(A[i]) % 24000;
		j = 0, collisionscounter = 0;
		while (1) {
			if (perfectindex + j < 24000) {
				if (H[perfectindex + j].compare(word) == 0) {
					H[perfectindex + j] = "";
					break;
				} else {
					j++;
					collisionscounter++;
				}
			} else if (perfectindex + j >= 24000) {
				j = j - 24000;
			}
		}
		QueryPerformanceCounter(&tick2);
		double end = double(tick2.QuadPart)/ticksPerSecond.QuadPart;
		double diff = end - start;
		times[i - 12000] = diff;
		collisions[i - 12000] = collisionscounter;
	}*/
	
	
	cout << endl << "COLLISIONS:" << endl;
	cout << "   Minimum: " << minimum(collisions, 1000) << endl;
	cout << "   Average: " << average(collisions, 1000) << endl;
	cout << "   Maximum: " << maximum(collisions, 1000) << endl;
	cout << endl;
	cout << "TIMES:" << endl;
	cout << "   Average: " << average_precise(times, 1000) << " seconds";
	
	cout << endl << endl;

	//searching for the user-defined word
	string input_word;
	int input_word_hash, loopcounter = 0;
	cout << "What word are we looking for?" << endl;
	cin >> input_word;
	input_word_hash = hash(input_word) % 24000;
	collisionscounter = 0, j = 0;
	cout << endl << "LOOKING FOR " << input_word << " with hash " << input_word_hash << endl << endl;
	while (1) {
		if (loopcounter > 24000) {
			cout << endl << "There's no " << input_word << " word in the textfile";
			break;
		}
		if (input_word_hash + j < 24000) {
			if (H[input_word_hash + j].compare(input_word) == 0) {
				cout << endl << "I found your word!" << endl;
				cout << "Number of collisions occured: " << collisionscounter;
				break;
			} else {
				cout << H[input_word_hash + j] << "\t\tHASH: " << hash(H[input_word_hash + j]) % 24000 << "\tINDEX: " << input_word_hash + j << endl;
				collisionscounter++;
				j++;
			}
		} else if (input_word_hash + j >= 24000) {
			j = j - 24000;
		}
		loopcounter++;
	}
	
	return 0;
}
