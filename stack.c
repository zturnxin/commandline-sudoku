#include <stdio.h>
#include "stack.h"
#include "zone.h"
#include "disp.h"
#define N 100

static int top = 0;

static int sudoku_buf[N][9][9];


void push(void)
{
	sudoku_copy(sudoku_buf[top++], sudoku);
}

void pop(void)
{
	sudoku_copy(sudoku, sudoku_buf[--top-1]);
}

int empty(void)
{
	return top-1 == 0;
}

int full(void)
{
	return top >= N;
}
