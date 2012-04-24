#ifndef FILL_H
#define FILL_H

//fill_grid: fill a grid (r,c) with n 
int fill_grid(int puzzle[][9], int r, int c, int n);

//fill_unique: automatically fill sudoku[MAX][MAX] using unique condidates method
void fill_unique(int puzzle[][9]);

// unfill: unfill a filled grid 
void unfill(void);

// reset: restart from the begining of the game.
void reset(int puzzle[][9]);

/*
 * try_grid: try grid (r,c) with n
 */
void try_grid(int r, int c);


#endif
