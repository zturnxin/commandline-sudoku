#ifndef LOAD_H
#define LOAD_H

/*
 * This function load a sudoku puzzle
 * randomly from file *filename
 * into a 9x9 char array sudoku[9][9].
 * maxlines is the number of lines *filename
 * contains. And also initate the osudoku[9][9],
 *
 */
void load(char *filename, int maxlines);
#endif
