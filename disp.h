#ifndef DISP_H
#define DISP_H

/* display the 9x9 array sudoku[9][9] */
void disp(int puzzle[][9]);

/* display the 9x9x9 array condidates[9][9][9+1] */
void dispcond_grid(int r, int c);
void dispcond_line(int r);
void dispcond_col(int c);
void dispcond_box(int b);

/* display condidates of all empty grids 
 * update condidates before display
 */
void dispcond_all();
void dispcand_all();

/* display condidates of 1-condidate grid */
void dispcond_unique();

/*
 * menu: display the menu of the program.
 */
void menu(void);

#endif
