#include "check.h"
#include "zone.h"

/*
 * is_filled: return 1 if grid(r,c) is filled 
 * return 0 if not.
 */
int is_filled(int puzzle[][9], int r, int c)
{
	return (puzzle[r-1][c-1] >= 1 && puzzle[r-1][c-1] <= 9);
}

/*
 * To be replace with count_condidates(int r, int c, int puzzle[][9])
 */
/*
 * is_unique: return 1 if grid (r, c) not empty and
 * grid (r, c)'s number is unique among line r, col c and
 * the corresponding box. 0 if not.
 */
int is_unique(int r, int c, int puzzle[][9])
{
	int i, flag[9];

	// make sure (r,c) not empty!
	if (!is_filled(puzzle, r, c))
		return 0;
	for (i=0; i<9; i++)
		flag[i] = 0;
	
	i = puzzle[r-1][c-1];
	puzzle[r-1][c-1] = 0;
	getbox(puzzle, r, c);
	getrow(puzzle, r, c);
	getcol(puzzle, r, c);
	puzzle[r-1][c-1] = i;
	
	flag[puzzle[r-1][c-1] - 1] = 1;
	for (i=0; i<9; i++) {
		if (box[i] >= 1 && box[i] <= 9)
			flag[box[i]-1]++;
		if (row[i] >= 1 && row[i] <= 9)
			flag[row[i]-1]++;
		if (col[i] >= 1 && col[i] <= 9)
			flag[col[i]-1]++;
	}

	for (i=0; i<9; i++)
		if (flag[i] > 1)
			return 0;
	return 1;
}

	
/*
 * is_finished: return 1 if no empty grid exist in 
 * puzzle[][9] and all grid is unique. return 0 if not.
 */
int is_finished(int puzzle[][9])
{
	int r, c;

	for (r=0; r<9; r++)
		for (c=0; c<9; c++)
			if (!(is_filled(puzzle, r+1, c+1) || is_unique(r+1, c+1, puzzle)))
				return 0;
	return 1;
}

/*
 * exist_error: return 1 if the sudoku puzzle[][9] exist a
 * empty grid with no condidates. 0 if not.
 */
int exist_error(int puzzle[][9])
{
	int cond[9][9][9+1];
	int r, c;

	get_condidates(cond, puzzle);
	for (r=0; r<9; r++)
		for (c=0; c<9; c++)
			if (!is_filled(puzzle, r+1, c+1) && (cond[r][c][0] < 1 || cond[r][c][0] > 9))
				return 1;
	return 0;
}
	
