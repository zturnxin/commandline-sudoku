#include <stdio.h>
#include "zone.h"

/* disp: display sudoku[9][9]. */
void disp(int puzzle[][9])
{
	int i;

	printf("\t\t   1 2 3     4 5 6     7 8 9\n");
	for (i=0; i<9; i++) {
		if (i==3 || i==6)
			printf("\t\t +++++++++++++++++++++++++++++\n");
		printf("\t\t%c{ %c %c %c }+{ %c %c %c }+{ %c %c %c }\n", '1'+i, (puzzle[i][0]) ? '0'+puzzle[i][0]:'.', (puzzle[i][1]) ? '0'+puzzle[i][1]:'.', (puzzle[i][2]) ? '0'+puzzle[i][2]:'.', (puzzle[i][3]) ? '0'+puzzle[i][3]:'.', (puzzle[i][4]) ? '0'+puzzle[i][4]:'.', (puzzle[i][5]) ? '0'+puzzle[i][5]:'.', (puzzle[i][6]) ? '0'+puzzle[i][6]:'.', (puzzle[i][7]) ? '0'+puzzle[i][7]:'.', (puzzle[i][8]) ? '0'+puzzle[i][8]:'.');
	}
}

/* display the 9x9x9 array condidates[9][9][9] */

void dispcond_grid(int r, int c)
{
	int n;

	// if the grid is not empty
	if ( sudoku[r-1][c-1] >= 1 && sudoku[r-1][c-1] <= 9)
		return;
	printf("(%d,%d)--[%d]: ", r, c, condidates[r-1][c-1][0]);
	for (n=0; n<9; n++)
		if (condidates[r-1][c-1][n+1] >= 1 && condidates[r-1][c-1][n+1] <= 9)
			printf("%d ", condidates[r-1][c-1][n+1]);
	printf("\n");
}

void dispcond_line(int r)
{
	int c;

	for (c=0; c<9; c++) 
		dispcond_grid(r, c+1);
}
		
void dispcond_col(int c)
{
	int r;

	for (r=0; r<9; r++) 
		dispcond_grid(r+1, c);
}

void dispcond_box(int b)
{
	int r, c;

	for (r=(b-1)/3*3; r<(b-1)/3*3+3; r++)
		for (c=(b-1)%3*3; c<(b-1)%3*3+3; c++)
			dispcond_grid(r+1, c+1);
}
			
void dispcond_all(void)
{
	int r, c;

	for (r=0; r<9; r++)
		for (c=0; c<9; c++)
			dispcond_grid(r+1, c+1);
}

void dispcand_all(void)
{
	int r, c, t;
	
	for (r=0; r<9; r++) {
		printf("%d", r+1);
		for (c=0; c<9; c++) {
			printf("[");	
			for (t=1; t<=9; t++)
				printf("%c", condidates[r][c][t]? '0'+condidates[r][c][t]:'.');
			printf("]");
			if (!((c+1)%3))
				printf(" ");
		}
		printf("\n");
		if (!((r+1)%3))
			printf("\n");
	}
}

/* display condidates of 1-condidate grid */
void dispcond_unique()
{
	int r, c;
	
	for (r=0; r<9; r++)
		for (c=0; c<9; c++)
			if (condidates[r][c][0] == 1)
				dispcond_grid(r+1, c+1);
}

void tmpdisp(void)
{
	int r, c;

	for (r=0; r<9; r++)
		for (c=0; c<9; c++)
			printf("%d\t%d\t%d\n", r+1, c+1, (condidates[r][c][0] >= 1 && condidates[r][c][0] <= 9) ? condidates[r][c][0]:0);
}

/*
 * menu: display the menu of the program.
 */
void menu(void)
{
	printf("\n\
Welcome! Enjoy yourself with this sudoku game!\n\
+-------------------------- Menu --------------------------+\n\
\t 1. easy\n\t 2. medium\n\t 3. hard\n\
\t 4. quit\n\
+----------------------------------------------------------+\n\
Choose [1-4]: ");
}
