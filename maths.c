#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef enum {
	ADD = 0,
	SUBTRACT = 1,
	MULTIPLY = 2,
	DIVIDE = 3
} op;

void wait() {
	char c;
	do {
		c = getchar();
	} while (c != '\n');
}	

int main(void) {

	srand(time(NULL));

	char* pattern = "%i %c %i = ";

	char answer[256];
	char symbol;

	while (1) {
		int operation = rand() % 4;
		int a = rand() % 900 + 100; // 100 - 999 
		int b = rand() % 90 + 10; // 10 - 99 
	
		switch(operation) {
			case ADD:
				symbol = '+';
				sprintf(answer, "%i", a+b);
				break;	
			case SUBTRACT:
				symbol = '-';
				sprintf(answer, "%i", a-b);
				break;	
			case MULTIPLY:
				symbol = '*';
				sprintf(answer, "%i", a*b);
				break;	
			case DIVIDE:
				symbol = '/';
				sprintf(answer, "%.4f", (float)a/b);
				break;	
		}	
		printf(pattern, a, symbol, b);
		wait();
		printf("%s\n", answer);
		wait();
	}
}
