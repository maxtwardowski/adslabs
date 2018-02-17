#include <iostream>
#include <fstream>
#include <windows.h>
#include <time.h>
using namespace std;

//SDBM HASHING FUNCTION
unsigned long hash(string str) {
    unsigned long hash = 0;
    int c;
    for (int i = 0; i < str.length(); ++i) {
    	c = (int) str[i];
        hash = c + (hash << 6) + (hash << 16) - hash;
    }
    return hash;
}

int levenshtein(string word1, string word2) {
	int size1, size2;
	size1 = word1.length();
	size2 = word2.length();
	
	int i = 0, distance = 0;
	while(1) {
		if (i > size1 && i > size2) {
			break;
		} else if (i > size1 && i <= size2) {
			distance = distance + size2 - i;
			break;
		} else if (i > size2 && i <= size1) {
			distance = distance + size1 - i;
			break;
		} else {
			if (word1[i] != word2[i]) {
				distance++;
			}
		}
		i++;
	}
	return distance;
}

int search(string input_word, string dictionary_hash[]) {
	int input_word_hash, loopcounter = 0, message;
	input_word_hash = hash(input_word) % 30000;
	int collisionscounter = 0, j = 0;
	while (1) {
		if (loopcounter > 30000) {
			message = 0;
			break;
		}
		if (input_word_hash + j < 30000) {
			if (dictionary_hash[input_word_hash + j].compare(input_word) == 0) {
				message = 1;
				break;
			} else {
				collisionscounter++;
				j++;
			}
		} else if (input_word_hash + j >= 30000) {
			j = j - 30000;
		}
		loopcounter++;
	}
	return message;
}

double average_precise(double array[], int size) {
	double sum = 0, avg;
	for (int i = 0; i < size; i++)
		sum += array[i];
	avg = sum / size;
	return avg;
}

int main() {
	
	LARGE_INTEGER ticksPerSecond;
	LARGE_INTEGER tick1;   
	LARGE_INTEGER tick2;   
	LARGE_INTEGER time1;   
	LARGE_INTEGER time2;  
	
	int i, j;
	int size = 325;
	int finalsize = 283;
	string rawinput[size], words[finalsize];
	
    ifstream file("ocr_output.txt");
    if(file.is_open()) {
        for (i = 0, j = 0; i < size; i++) {
            file >> rawinput[i];
            if (rawinput[i].length() > 1) {
            	words[j] = rawinput[i];
            	j++;
            }
        }
    }
    
	ifstream input("wrt.dic");
	string dictionary_input[24000];
	if(input.is_open()) {
        for (i = 0, j = 0; i < 24000; i++) {
            input >> dictionary_input[i];
        }
    }
    
    string dictionary_hash[30000];
    for (i = 0; i < 24000; i++) {
		j = 0;
		while (1) {
			if ((hash(dictionary_input[i]) % 30000) + j < 30000) {
				if (dictionary_hash[(hash(dictionary_input[i]) % 30000) + j].empty() == 1) {
					dictionary_hash[(hash(dictionary_input[i]) % 30000) + j] = dictionary_input[i];
					break;
				} else {
					j++;
				}
			} else if ((hash(dictionary_input[i]) % 30000) + j >= 30000) {
				j = j - 30000;
			}
		}
	}
	
	int distancegoal = 1, unknown_counter = 0, suggestions_counter, dist, k = 0, measure = 1;
	double times[24000];
	
	for (i = 0; i < finalsize; i++) {
		if (search(words[i], dictionary_hash) == 0) {
			cout << endl << "Suggestions for '" << words[i] << "':" << endl;
			for (j = 0; j < 24000; j++) {
				
				//time measurement initialization
				QueryPerformanceFrequency(&ticksPerSecond);
				QueryPerformanceCounter(&tick1);
				double start = double(tick1.QuadPart)/ticksPerSecond.QuadPart;

				
				dist = levenshtein(words[i], dictionary_input[j]);
				
				QueryPerformanceCounter(&tick2);
				double end = double(tick2.QuadPart)/ticksPerSecond.QuadPart;
				double diff = end - start; 
				
				if (measure == 1) {
					times[k] = diff;
					k++;
				}
				
				if (dist == distancegoal) {
					cout << "\t" << dictionary_input[j] << endl;
					suggestions_counter++;
				}
			}
			measure = 0;
			unknown_counter++;
		}
	}
	
	double time = average_precise(times, 24000);
	
	cout << endl << "Unknown words: " << unknown_counter * 100 / finalsize << " %";
	cout << endl << "Average suggestion list length: " << suggestions_counter / unknown_counter;
	cout << endl << "Average Levenshtein distance calculation time: " << time;

	return 0;
}
