#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <curses.h>

#define BUFSIZE 256
#define DIV_TRIES 1000000

#define	ADD 0
#define	SUBTRACT 1
#define	MULTIPLY 2
#define	DIVIDE 3

#define ESC_KEY 27

int die(const char* s) {
	endwin();
	fprintf(stderr, s);
	exit(EXIT_FAILURE);	

}
void wait() {
	char c;
	do {
		c = getch();
		if (c == ESC_KEY) {
			endwin();
			exit(EXIT_SUCCESS);
		}
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
		die("snprintf error\n");
	}
	if (n >= BUFSIZE) {
		fprintf(stderr, "answer truncated\n");
	}
}	

void swap(int* a, int* b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}


int main(int argc, char* argv[]) {
	initscr(); 
	cbreak(); 
	noecho();

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
		die("Usage: maths [a][b]\n");
	}

	if (a_digits < 1 || b_digits < 1) {
		die("Arguments must be integers greater than 0\n");
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
						die("Division problem generation error\n");
					}	
				} 
				set_answer(answer, "%i", a/b);
				break;	
		}	
		move(0,0);
		printw("Press ENTER for the solution or a new problem, ESC to exit.\n");	
		printw(pattern, a, symbol, b);
		refresh();
		wait();
		printw("%s\n", answer);
		refresh();
		wait();
		erase();
	}
}
