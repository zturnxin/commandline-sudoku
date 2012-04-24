#include <stdlib.h>
#include "zone.h"
#include "generate.h"
#include "backtracksolve.h"
#include "disp.h"
#include "check.h"

inline void swap(int *a, int *b)
{
	int c = *a;
	*a = *b;
	*b = c;
}

inline void randindex(int index[])
{
	int i;

	for(i=0; i<81; i++)
		index[i] = i;
	for(i=0; i<81; i++)
		swap(index+i, index+rand()%81);
}


/*
 * generate_full: generate a full sudoku board[9][9] randomly
 * and save as puzzle[][9]
 */
void generate_full(int puzzle[][9])
{
	int r, c;

	do {
		for (r=0; r<9; r++) {
			for (c=0; c<9; c++) 
				puzzle[r][c] = 0;
			puzzle[r][rand()%9] = r+1;
		}
	} while (!sudoku_solve(puzzle, 1));
	sudoku_copy(puzzle, board_solution);
}

/*
 * generate: generate a sudoku board b[9][9] with unique 
 * solution. return the number of filled grid in b[9][9].
 * Parameters:
 * b[][9]: a sudoku board[9][9] with unique solution
 * max_filled: the maximal number of filled grid in b[9][9]
 * full[][9]: a full sudoku board[9][9]
 */
int generate(int b[][9], int max_filled, int full[][9])
{
	int r, c, t, rid[81];
	int filled = 81;
	int flag = 0;
	int current = 0;

	if (!is_finished(full))
		return -1;

	sudoku_copy(b, full);
	randindex(rid);
	for (flag=-1, current=0; current!=flag; current=(current+1)%81) {
		r = rid[current]/9;
		c = rid[current]%9;
		if (rid[current] != -1) {
			t = b[r][c];
			b[r][c] = 0;
			if (sudoku_solve(b, 2) == 2)
				b[r][c] = t;
			else {
				flag = current;
				rid[flag] = -1;
				filled--;
				if (filled <= max_filled)
					break;
			}
		}
	}
	return filled;
}
