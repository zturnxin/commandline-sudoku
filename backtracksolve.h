#ifndef BACKTRACKSOLVE_H
#define BACKTRACKSOLVE_H

/*
 * keep the latest solution while backtracking...
 */
extern int board_solution[9][9];

/*
 * backtracksolve: use dfs to search the solutions in board[9][9]
 */
void backtracksolve(void);

/*
 * count_condidate: return the number of condidates in (r,c)
 */
inline int count_condidate(int r, int c, int *mark);


/*
 * sudoku_solve: return the number of solutions found and 
 * save the latest solution into board_solution[9][9] (use
 * "sudoku_copy(puzzle, board_solution)" to get the latest
 * solution of the puzzle[][9].) if solutions found. The 
 * puzzle[][9] won't be changed.
 * Parameters:
 * puzzle: a pointer to the sudoku[9][9] you want to solve.
 * mode: the maximal number of solutions you want to find.
 * Note if mode is set to 0, the function will try to find out
 * all solutions.
 */
unsigned long long sudoku_solve(int puzzle[][9], unsigned long long mode);

#endif
