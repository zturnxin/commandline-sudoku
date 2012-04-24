#ifndef ZONE_H
#define ZONE_H

// sudoku puzzle
extern int sudoku[9][9];

// store sudoku zone
extern int box[9];
extern int row[9];
extern int col[9];

/*
 * Keep original sudoku puzzle. Can also be
 * used for illegally fill check. It's must be 
 * initate by load function. [space]: empty. [1-9]: origin 
 */
extern int osudoku[9][9];

/*
 * store condidates of all grids.
 * the condidates[i][j][0]: stores the number of condidates in (i+1,j+1)
 */
extern int condidates[9][9][9+1];

/*
 * getbox/getrow/getcol: get box[9]/row[9]/col[9] of grid
 * (row, col) in puzzle[][9]
 */
void getbox(int puzzle[][9], int rw, int cl);
void getrow(int puzzle[][9], int rw, int cl);
void getcol(int puzzle[][9], int rw, int cl);

/*
 * get_condidates: get puzzle[][9]'s condidates matrix cond[][9][9]
 */
void get_condidates(int cond[][9][9+1], int puzzle[][9]);

/*
 * sudoku_copy: copy q[9][9] into p[9][9]
 */
void sudoku_copy(int p[][9], int q[][9]);

/*
 * same_sudoku: compare p[9][9] with q[9][9]
 * return 1 if is the same, and 0 if not.
 */
int same_sudoku(int p[][9], int q[][9]);

/*
 * sudoku_swap: exchange p[9][9] with q[9][9]
 */
void sudoku_swap(int p[][9], int q[][9]);

/*
 * sudoku_and: and operation of p[9][9] and q[9][9]
 * store the result into p[][9]
 */
void sudoku_and(int p[][9], int q[][9]);

/*
 * condidates_copy: copy p[9][9][9+1] into q[9][9][9+1]
 */
void condidates_copy(int p[][9][9+1], int q[][9][9+1]);

/*
 * condidates_cmp: compare p[9][9][9+1] with q[9][9][9+1]
 * return 1 if is the same, and 0 if not.
 */
int condidates_cmp(int p[][9][9+1], int q[][9][9+1]);

/*
 * condidates_swap: exchange p[9][9][9+1] with q[9][9][9+1]
 */
void condidates_swap(int p[][9][9+1], int q[][9][9+1]);

/*
 * init_sudoku: initate puzzle[][9] with ' '
 */
void init_sudoku(int puzzle[][9]);

/*
 * init_condidates: initate cond[][9][9+1] with '\0'
 */
void init_condidates(int cond[][9][9+1]);

/*
 * stobuf: save n int puzzle to buf per line
 * return the number of puzzles save to sudoku_buf
 */
int stobuf(int puzzle[][9]);

/*
 * empty_sudoku_buf: empty buf before use.
 */
void empty_sudoku_buf(void);

// return the current size of sudoku_buf
int sudoku_buf_size(void);

// return 1 if sudoku_buf full.
int sbuf_full(void);

/*
 * buftos: get a sudoku from sudoku_buf
 */
int buftos(int puzzle[][9]);

#endif
