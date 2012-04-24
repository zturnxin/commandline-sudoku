#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "zone.h"
#include "check.h"
#include "disp.h"

/* 
 * loae: load a 81 length string into sudoku from 
 * sudokudb file contains "lines" line. randomly. 
 */
void load(char *filename, int lines)
{
	int r, c, randnu;
	char randline[9*9+1];
	FILE *sudokudb = fopen(filename, "r");

	if (!sudokudb) {
		printf("Error open file!...\n");
		exit(1);
	}

	// randomize a line number: randnu
	randnu = rand()%lines;

	// read a sudoku puzzle into sudoku[9][9] and osudoku[9][9]
	for (r=0; !feof(sudokudb) && r<=randnu; r++)
		fgets(randline, 100, sudokudb);
	for (r=0; r<9; r++)
		for (c=0; c<9; c++) {
			sudoku[r][c] = (*(randline+r*9+c) >= '1' && *(randline+r*9+c) <= '9') ? *(randline+r*9+c)-'0' : 0;
			// keep the orginal sudoku
			osudoku[r][c] = sudoku[r][c];
		}
	fclose(sudokudb);

	if (exist_error(osudoku)) {
		printf("Load sudoku failed because exist_error in loaded sudoku puzzle...\n");
		disp(osudoku);
		exit(1);
	}
}
