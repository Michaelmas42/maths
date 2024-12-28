#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#define BUFSIZE 256

#define	ADD 0
#define	SUBTRACT 1
#define	MULTIPLY 2
#define	DIVIDE 3

void wait() {
	char c;
	do {
		c = getchar();
	} while (c != '\n');
}	

int rand_int(int digits) {
	int lo = pow(10, digits-1);
	int hi = pow(10, digits) - lo;
	return rand() % hi + lo;
}

void set_answer(char* buffer, const char* fmt, int value) {
	int n = snprintf(buffer, BUFSIZE, fmt, value);
	if (n < 0) {
		fprintf(stderr, "snprintf error");
		exit(1);
	}
	if (n >= BUFSIZE) {
		fprintf(stderr, "answer truncated");
	}
}	

void swap(int* a, int* b) {
	int* tmp = a;
	a = b;
	b = tmp;
}

int main(void) {

	srand(time(NULL));
	char* pattern = "%i %c %i = ";

	char answer[BUFSIZE];
	char symbol;

	int a, b, operation;

	while (1) {
		operation = rand() % 4;
	
		switch(operation) {
			case ADD:
				a = rand_int(3); 
				b = rand_int(3); 
				symbol = '+';
				set_answer(answer, "%i", a+b);
				break;	
			case SUBTRACT:
				a = rand_int(3); 
				b = rand_int(3);
			        if (b > a) {
					swap(&a, &b);
				}	
				symbol = '-';
				set_answer(answer, "%i", a-b);
				break;	
			case MULTIPLY:
				a = rand_int(3); 
				b = rand_int(2); 
				symbol = '*';
				set_answer(answer, "%i", a*b);
				break;	
			case DIVIDE:
				symbol = '/';
				do { 
					a = rand_int(3); 
					b = rand_int(2); 
				} while (a % b != 0);
				set_answer(answer, "%i", a/b);
				break;	
		}	
		printf(pattern, a, symbol, b);
		wait();
		printf("%s\n", answer);
		wait();
	}
}
