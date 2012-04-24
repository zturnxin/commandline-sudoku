#include "zone.h"
#include "check.h"

// sudoku: 9 * 9 puzzle. 1~9: filled-grid, 0: empty-grid
int sudoku[9][9];

// store sudoku zone
int box[9];
int row[9];
int col[9];

// save sudoku per line
static char sudokubuf[1024][81];
static int sbufsize;

/*
 * Keep original sudoku puzzle.
 * It's initated by load function. 
 */
int osudoku[9][9];

/* 
 * condidates: 9 * 9 * (9+1) matrix. Stores condidates of all grids.
 * 1~9: condidate
 * 0: not-condidate or condidate number is 0
 * condidates[i][j][0]: stores the number of condidates in grid (i+1,j+1)
 */
int condidates[9][9][9+1];

/*
 * getbox/getrow/getcol: get box[9]/row[9]/col[9] of grid
 * (row, col) in puzzle[][9]
 */
void getbox(int puzzle[][9], int r, int c)
{
	int i;
	for (i=0; i<9; i++)
		box[i] = puzzle[(r-1)/3*3+i/3][(c-1)/3*3+i%3];
}

void getrow(int puzzle[][9], int r, int c)
{
	int i;
	for (i=0; i<9; i++)
		row[i] = puzzle[i][c-1];
}

void getcol(int puzzle[][9], int r, int c)
{
	int j;
	for (j=0; j<9; j++)
		col[j] = puzzle[r-1][j];
}

/*
 * get_condidates: get puzzle[][9]'s condidates matrix cond[][9][9+1]
 */
void get_condidates(int cond[][9][9+1], int puzzle[][9])
{
	int r, c, n;

	// initate cond[9][9][9+1] 
	for (r=0; r<9; r++)
		for (c=0; c<9; c++)
			for (n=0; n<=9; n++) 
				cond[r][c][n] = (puzzle[r][c] >= 1 && puzzle[r][c] <= 9) ? 0 : n;

	for (r=0; r<9; r++)
		for (c=0; c<9; c++) {
			if (puzzle[r][c] >= 1 && puzzle[r][c] <= 9)
				continue;
			getbox(puzzle, r+1, c+1);
			getrow(puzzle, r+1, c+1);
			getcol(puzzle, r+1, c+1);
			for (n=0; n<9; n++) {
				if (box[n] >= 1 && box[n] <= 9)
					cond[r][c][box[n]] = 0;
				if (row[n] >= 1 && row[n] <= 9)
					cond[r][c][row[n]] = 0;
				if (col[n] >= 1 && col[n] <= 9)
					cond[r][c][col[n]] = 0;
			}
			// count condidates
			for (n=0; n<9; n++)
				if (cond[r][c][n+1] >= 1 && cond[r][c][n+1] <= 9)
					cond[r][c][0]++;
		}
}

/*
 * sudoku_copy: copy q[9][9] into p[9][9]
 */
void sudoku_copy(int p[][9], int q[][9])
{
	int r, c;

	for (r=0; r<9; r++)
		for (c=0; c<9; c++)
			p[r][c] = q[r][c];
}

/*
 * same_sudoku: compare p[9][9] with q[9][9]
 * return 1 if is the same, and 0 if not.
 */
int same_sudoku(int p[][9], int q[][9])
{
	int r, c;

	for (r=0; r<9; r++)
		for (c=0; c<9; c++)
			if (p[r][c] != q[r][c])
				return 0;
	return 1;
}

/*
 * sudoku_swap: exchange p[9][9] with q[9][9]
 */
void sudoku_swap(int p[][9], int q[][9])
{
	int r, c, t;

	for (r=0; r<9; r++)
		for (c=0; c<9; c++) {
			t = p[r][c];
			p[r][c] = q[r][c];
			q[r][c] = t;
		}
}

/*
 * sudoku_and: and operation of p[9][9] and q[9][9], and store
 * the result puzzle into p[][9]
 */
void sudoku_and(int p[][9], int q[][9])
{
	int r, c;

	for (r=0; r<9; r++)
		for (c=0; c<9; c++)
			if (p[r][c] != q[r][c])
				p[r][c] = 0;
}

/*
 * init_sudoku: initate puzzle[][9] with 0
 */
void init_sudoku(int puzzle[][9])
{
	int r, c;

	for (r=0; r<9; r++)
		for (c=0; c<9; c++)
			puzzle[r][c] = 0;
}

/*
 * init_condidates: initate cond[][9][9+1] with 0
 */
void init_condidates(int cond[][9][9+1])
{
	int r, c, n;

	for (r=0; r<9; r++)
		for (c=0; c<9; c++)
			for (n=0; n<=9; n++)
				cond[r][c][n] = 0;
}

/*
 * stobuf: save n int puzzle to buf per line
 * return the number of puzzles save to sudoku_buf
 */
int stobuf(int puzzle[][9])
{
	int r, c;
	
	if (sbufsize < 1024) 
		for (r=0; r<9; r++)
			for (c=0; c<9; c++)
				sudokubuf[sbufsize][r*9+c] = '0' + puzzle[r][c];
	else 
		return 0;
	return ++sbufsize;
}
				
/*
 * empty_sudoku_buf: empty buf before use.
 */
void empty_sudoku_buf(void)
{
	sbufsize = 0;
}

// return the current size of sudoku_buf
int sudoku_buf_size(void)
{
	return sbufsize;
}

// return 1 if sudoku_buf full.
int sbuf_full(void)
{
	return (sbufsize == 1024);
}

/*
 * buftos: get a sudoku from sudoku_buf
 */
int buftos(int puzzle[][9])
{
	int r, c;

	if (sbufsize)
		for (r=0; r<9; r++)
			for (c=0; c<9; c++)
				 puzzle[r][c] = sudokubuf[sbufsize-1][r*9+c] - '0';
	else
		return 0;
	return sbufsize--;
}
