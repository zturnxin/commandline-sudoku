#ifndef GENERATE_H
#define GENERATE_H

void swap(int *a, int *b);

/*
 * randindex: init index to 1..81, and rand its order
 */
void randindex(int index[]);

/*
 * generate_full: generate a full sudoku board[9][9] randomly
 * and save as puzzle[][9]
 */
void generate_full(int puzzle[][9]);

/*
 * generate: use full[][9] to generate a sudoku board b[9][9] 
 * with unique solution. return the number of filled grid 
 * in b[9][9].
 * Parameters:
 * b[][9]: a sudoku board[9][9] with unique solution
 * max_filled: the maximal number of filled grid in b[9][9]
 * full[][9]: a full sudoku board[9][9]
 */
int generate(int b[][9], int max_filled, int full[][9]);

#endif
