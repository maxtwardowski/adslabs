#include <iostream>
#include <conio.h>
#include <math.h>

using namespace std;

struct Clusters{
	char symbol;
	int quantity;
};

Clusters sym[1000];
int symbolindex;
int checked[1000][1000];

int cords (string str, int x, int y) {
	int length, i, position, lines = 0, x_max, y_max;
	char symbol;
	length = str.length();
	for (i = 0; i < length; i++) {
		symbol = str[i];
		if (symbol == '\n')
			lines++;
	}
	length -= lines;
	x_max = length / lines;
	y_max = length / x_max;
	position = x - 1 + (y - 1) * x_max + y - 1;
	if (x <= x_max && y <= y_max) {
		return position;
	} else {
		return 0;
	}
}

void CharMiner (string str, int i, int j, int length_row, int rows) {
	if (j + 1 < length_row && checked[i][j + 1] == 0 && str[i * length_row + j + 1] == sym[symbolindex].symbol) {
		sym[symbolindex].quantity += 1;
		checked[i][j + 1] = 1;
		CharMiner(str, i, j + 1, length_row, rows);
	}
	if (j - 1 >= 0 && checked[i][j - 1] == 0 && str[i * length_row + j - 1] == sym[symbolindex].symbol) {
		sym[symbolindex].quantity += 1;
		checked[i][j - 1] = 1;
		CharMiner(str, i, j - 1, length_row, rows);
	}
	if (i + 1 < rows && checked[i + 1][j] == 0 && str[(i + 1) * length_row + j] == sym[symbolindex].symbol) {
		sym[symbolindex].quantity += 1;
		checked[i + 1][j] = 1;
		CharMiner(str, i + 1, j, length_row, rows);
	}
	if (i - 1 >= 0 && checked[i - 1][j] == 0 && str[(i - 1) * length_row + j] == sym[symbolindex].symbol) {
		sym[symbolindex].quantity += 1;
		checked[i - 1][j] = 1;
		CharMiner(str, i - 1, j, length_row, rows);
	}
}

void resultsprint() {
	for(int i = 0; i < symbolindex; i++){
		printf("%c: %d\n", sym[i].symbol,  sym[i].quantity);
	}
}

int main() {
	int length_row, rows;
	int i, j;
	string text = // 32 elements per line (without newline symbols)
	"#################aa##a###c######\n" // 32
	"####bbbbaaaabbbbbaaaaa###ccc##cc\n" // 64
	"#o##bbbbaaaabbbbbaaaaa###c#c##cc\n" // 96
	"#oo#bbbbaeeabbbbbbbbaa##cc#ccccc\n" // 128
	"#o##bbbbaeeabbbbbaaaaaa#cc#####c\n" // 160 
	"#o##bbbbaaaabbbbbaaaaaa#cc#####c\n"; // 192
	
	char currentsymbol;
	int length_text = text.length();
	for (i = 0; i < length_text; i++) {
		currentsymbol = text[i];
		if (currentsymbol == '\n') {
			rows++;
		}
	}
	
	length_row = length_text / rows;

	for (i = 0; i < rows; i++) {
		for (j = 0; j < length_row - 1; j++) {
			if (checked[i][j] == 0) {
				checked[i][j] = 1; // fixing +1 area difference
				sym[symbolindex].symbol = text[i * length_row + j];
				sym[symbolindex].quantity++;
				CharMiner(text, i, j, length_row, rows);
				symbolindex++;
			}	
		}
	}
	
	// displaying the results
	resultsprint();
	
	return 0;
}



