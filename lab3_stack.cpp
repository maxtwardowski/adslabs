#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265

using namespace std;

int stack_index;
float pop(float stack[]) {
	int stack_index_temp = stack_index;
	--stack_index;
	return stack[stack_index_temp];
}

float top(float stack[]) {
	return stack[stack_index];
}

void push(float stack[], float ins) {
	stack[++stack_index] = ins;
}

int main () {
	int size = 6, i, sign_index;
	stack_index = -1; // -1 indicates empty stack
	char input[] = "20 40 + 30 - sin";
	char * storage[size];
	float stack[2];

	char *pch;
	pch = strtok (input, " ");
	while (pch != NULL) {
		storage[i++] = pch;
		pch = strtok (NULL, " ");
	}
	
	sign_index = 1;
	char * sign;
	float result;
	
	while (sign_index < size - 1) {
		sign = storage[sign_index++];
		
		while (1) {
			sign = storage[sign_index];
			if (strcmp(sign, "+") == 0 || strcmp(sign, "-") == 0 || strcmp(sign, "*") == 0 || strcmp(sign, "/") == 0 || strcmp(sign, "cos") == 0 || strcmp(sign, "sin") == 0) {
				break;
			} else {
				sign_index++;
			}
		}
		if (strcmp(sign, "+") == 0) {
			if (stack_index == -1)
				push(stack, atof(storage[sign_index - 2]));
			push(stack, atof(storage[sign_index - 1]));
			result = pop(stack) + pop(stack);
			push(stack, result);
		} else if (strcmp(sign, "-") == 0) {
			if (stack_index == -1)
				push(stack, atof(storage[sign_index - 2]));
			push(stack, atof(storage[sign_index - 1]));
			result = -(pop(stack) - pop(stack));
			push(stack, result);
		} else if (strcmp(sign, "*") == 0) {
			if (stack_index == -1)
				push(stack, atof(storage[sign_index - 2]));
			push(stack, atof(storage[sign_index - 1]));
			result = pop(stack) * pop(stack);
			push(stack, result);
		} else if (strcmp(sign, "/") == 0) {
			if (stack_index == -1)
				push(stack, atof(storage[sign_index - 2]));
			push(stack, atof(storage[sign_index - 1]));
			result = pow(pop(stack) / pop(stack), -1);
			push(stack, result);
		} else if (strcmp(sign, "sin") == 0) {
			if (stack_index == -1)
				push(stack, atof(storage[sign_index - 1]));
			result = sin(pop(stack) * PI / 180.0 );
			push(stack, result);
		} else if (strcmp(sign, "cos") == 0) {
			if (stack_index == -1)
				push(stack, atof(storage[sign_index - 1]));
			result = cos(pop(stack) * PI / 180.0 );
			push(stack, result);
		}
	}
	
	cout << "The result is: " << pop(stack);
	
	return 0;
}
