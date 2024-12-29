#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#define BUFSIZE 256
#define DIV_TRIES 1000000

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
		exit(EXIT_FAILURE);

	}
	if (n >= BUFSIZE) {
		fprintf(stderr, "answer truncated");
	}
}	

void swap(int* a, int* b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

int main(int argc, char* argv[]) {

	int a_digits, b_digits;
	if (argc == 1) {
		a_digits = 3;
		b_digits = 2;
	}
	else if (argc == 2) {
		a_digits = atoi(argv[1]);
		b_digits = atoi(argv[1]);
	}
	else if (argc == 3) {
		a_digits = atoi(argv[1]);
		b_digits = atoi(argv[2]);
	}
	else {
		fprintf(stderr, "Usage: maths [a][b]\n");
		exit(EXIT_FAILURE);	
	}

	if (a_digits < 1 || b_digits < 1) {
		fprintf(stderr, "Arguments must be integers greater than 0\n");
		exit(EXIT_FAILURE);	
	}
	
	srand(time(NULL));
	char* pattern = "%i %c %i = ";

	char answer[BUFSIZE];
	char symbol;

	int a, b, operation;

	while (1) {
		operation = rand() % 4;
		a = rand_int(a_digits); 
		b = rand_int(b_digits); 
	
		switch(operation) {
			case ADD:
				symbol = '+';
				set_answer(answer, "%i", a+b);
				break;	
			case SUBTRACT:
			        if (b > a) {
					swap(&a, &b);
				}	
				symbol = '-';
				set_answer(answer, "%i", a-b);
				break;	
			case MULTIPLY:
				symbol = '*';
				set_answer(answer, "%i", a*b);
				break;	
			case DIVIDE:
				symbol = '/';
				int i = 0;
				while (a % b != 0) { 
					a = rand_int(a_digits); 
					b = rand_int(b_digits); 
					if (b > a) {
						swap(&a, &b);
					}

					if (++i >= DIV_TRIES) {
						fprintf(stderr, "Division problem generation error\n");
						exit(EXIT_FAILURE);	
					}	
				} 
				set_answer(answer, "%i", a/b);
				break;	
		}	
		printf(pattern, a, symbol, b);
		wait();
		printf("%s\n", answer);
		wait();
	}
}
