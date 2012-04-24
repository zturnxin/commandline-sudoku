#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fill.h"
#include "zone.h"
#include "stack.h"
#include "disp.h"
#include "check.h"


//fill_grid: fill a empty grid (r,c) with n 
int fill_grid(int puzzle[][9], int r, int c, int n)
{
	if (osudoku[r-1][c-1])
		return 0;

//	printf("Prepare filling grid (%d,%d) with \"%d\"...\n", r, c, n);
	sudoku[r-1][c-1] = n;

	if(is_finished(puzzle)) {
		printf("Finished. Congratulations!\n");
		disp(puzzle);
	//	exit(0);
	}
	return 1;
}

// automatically fill grid by using unique condidates method
void fill_unique(int puzzle[][9])
{
	int r, c, n, cond[9][9][9+1];
	int exist_unique = 0;

	get_condidates(cond, puzzle);
//	dispcond_unique();
	for (r=0; r<9; r++)
		for (c=0; c<9; c++) {
			if (cond[r][c][0] != 1)
				continue;
			exist_unique = 1;
			for (n=0; n<9; n++) 
				if (cond[r][c][n+1] >= 1 && cond[r][c][n+1] <= 9) {
					fill_grid(puzzle, r+1, c+1, cond[r][c][n+1]);
					break;
				}
		}

	/*
	 * if exists unique condidates, they will be filling into the sudoku puzzle and
	 * the "exist_unique" variable will be set to 1(TRUE). It tells that 
	 * the sudoku puzzle has been changed. And this cause  the corresponding condidates puzzle
	 * to be changed. Maybe the updated condidates puzzle contains unique condidates
	 * So it's needed to refill the sudoku puzzle again.
	 */
	if (exist_unique) {
//		printf("Another filling...\n");
		fill_unique(puzzle);
	} 
}


// restart from the begining of the game.
void reset(int puzzle[][9])
{
	int r, c;
	
//	empty_stack();
	for (r=0; r<9; r++)
		for (c=0; c<9; c++)
			puzzle[r][c] = osudoku[r][c];
}

/*
 * try_grid: try grid (r,c) with its condidates. 
 */
#if 0
void try_grid(int r, int c)
{
	int n;
	int ts[9+1][9][9]; // 9+1 tmp sudoku[9][9], sudoku[0][9][9] 
	int tc[9][9][9+1]; 

	/* save working sudoku puzzle to tmp */
	sudoku_copy(ts[0], sudoku);
	/* keep working sudoku condidates matrix */
	get_condidates(tc, sudoku);

	if (is_filled(sudoku, r, c)) {
		printf("try to fill non-empty grid...\n");
		return;
	}

	for (n=0; n<9; n++) 
		if (tc[r-1][c-1][n+1] >= 1 && tc[r-1][c-1][n+1] <= 9) {
			sudoku_copy(sudoku, ts[0]);
			get_condidates(condidates, sudoku);
			printf("tring grid (%d,%d) with \"%d\"...\n", r, c, tc[r-1][c-1][n+1]);
			fill_grid(r, c, tc[r-1][c-1][n+1]);
			fill_unique();
			if (exist_error(sudoku)) {
				printf("exist_error tring grid (%d,%d) with \"%d\"...\n", r, c, tc[r-1][c-1][n+1]);
				// rm condidate
				tc[r-1][c-1][n+1] = 0;
				tc[r-1][c-1][0]--;
				if (tc[r-1][c-1][0] < 1 || tc[r-1][c-1][0] > 9) {
					printf("\n\n\t\tUnkonwn error!...\n\t...\t\t...\n");
					exit(1);
				}
				continue;
			}
			sudoku_copy(ts[tc[r-1][c-1][n+1]-0], sudoku);
		}

	sudoku_copy(sudoku, ts[0]);
	if (tc[r-1][c-1][0] == 1)
		for (n=0; n<9; n++) {
			if (tc[r-1][c-1][n+1] >= 1 && tc[r-1][c-1][n+1] <= 9) {
				fill_grid(r, c, tc[r-1][c-1][n+1]);
				disp(sudoku);
				printf("Useful tring grid (%d,%d)...\"%d\" filled!...\n", r, c, tc[r-1][c-1][n+1]);
				break;
			}
		}
	 else {
		for (n=0; n<9; n++)
			if (tc[r-1][c-1][n+1] >= 1 && tc[r-1][c-1][n+1] <= 9) {
				sudoku_copy(sudoku, ts[tc[r-1][c-1][n+1]]);
				for (++n; n<9; n++) 
					if (tc[r-1][c-1][n+1] >= 1 && tc[r-1][c-1][n+1] <= 9)
						sudoku_and(sudoku, ts[tc[r-1][c-1][n+1]]);
			}
		if (same_sudoku(sudoku, ts[0]))
			printf("Useless trying grid (%d,%d)...\n", r, c);
		else {
			printf("Useful tring grid (%d,%d)........\n", r, c);
			disp(sudoku);
		}
	}
	get_condidates(condidates, sudoku);
}

void tmptry(int n)
{
	int r, c;
	
	if (is_finished(sudoku)) {
		printf("sudoku alreadly finished!...\n");
		return;
	} else {
		for (r=0; r<9; r++)
			for (c=0; c<9; c++) 
				if (!is_filled(sudoku, r+1, c+1) && condidates[r][c][0] == n) { 
					try_grid(r+1, c+1);
				}
	}

}
#endif
