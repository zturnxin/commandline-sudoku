#ifndef CHECK_H
#define CHECK_H

/*
 * is_filled: return 1 if grid(r,c) is filled 
 * return 0 if not.
 */
int is_filled(int puzzle[][9], int r, int c);

/*
 * is_unique: return 1 if grid (r, c) not empty and
 * puzzle[r-1][c-1] is unique among line r, col c and
 * the corresponding box. 0 if not.
 */
int is_unique(int r, int c, int puzzle[][9]);


/*
 * is_finished: return 1 if no empty grid exist in 
 * puzzle[][9] and all grid is unique. return 0 if not.
 */
int is_finished(int puzzle[][9]);

/*
 * exist_error: return 1 if the sudoku puzzle[][9] exist a
 * empty grid with no condidates. 0 if not.
 */
int exist_error(int puzzle[][9]);

#endif
