#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
#include "zone.h"
#include "backtracksolve.h"
#include "check.h"
#include "disp.h"

/*
 * the sudoku board backtracksolve deal with...
 */
static int board[9][9];

/*
 * keep the latest solution of board[9][9] while backtracking...
 */
int board_solution[9][9];

/*
 * keep the current solving mode
 */
static unsigned long long backtrack_mode;

/*
 * keep the number of solutions found
 */
static unsigned long long solutions;

/*
 * for exception jump out according to backtrack_mode
 */
static sigjmp_buf exception_buf;


/*
 * backtracksolve: use dfs to search the solution in board[9][9]
 */
void backtracksolve(void) 
{
	int i, j;
	int cc; //count condidates of a grid
	int imin, jmin; // (imin,jmin) which has minimal number of condidates.
	int min = 10; // minimal number of condidates
	int flag[10]; // for counting the condidates in each function call. 
	int solution_found = 1; //assum that a solution found

	// find the grid (imin,jmin) with minimal number of condidates
	for (i=0; i<9; i++) {
		for (j=0; j<9; j++) {
			// if filled, continue.
			if (board[i][j] >= 1 && board[i][j] <= 9)
				continue;   
			// count the empty grid's condidate.
			cc = count_condidate(i, j, flag);  

			// if empty grid (i,j) has no condidates, backtrack.
			if (!cc)
				return; 

			// find the grid (imin,jmin) which has minimal number of condidates.
			if (cc < min) {
				solution_found = 0; //empty grid status it's not a solution. 
				imin = i; 
				jmin = j; 
				min = cc; 
			}
		}
	}

	// !....found a solution.....!
	if (solution_found) {
		/*
		 * if mode is set to nonzero, it will test the second
		 * if solutions not less than backtrack_mode then call
		 * siglongjmp to jump out
		 */
		if (!backtrack_mode || solutions<backtrack_mode) {
			solutions++;
			/* 
			 * printf("No. %lld:\n", solutions); 
			 * disp(board);
			 */
			/*
			 * save the solution as board_solution
			 */
			sudoku_copy(board_solution, board);
			return; //backtrack ... 
		} else 
			siglongjmp(exception_buf, 1);
	}

	//get the (imin,jmin)'s condidates into flag[] 
	count_condidate(imin, jmin, flag); 
	for (i=1; i<=9; i++)
		if (flag[i] == 0) { // Yeah, it's condidate.
			board[imin][jmin] = i; //try each condidate. 
			backtracksolve(); 
		}
	/*
	 * after trying, put the number back
	 */
	board[imin][jmin] = 0;
}

/*
 * count_condidate: return grid (r+1,c+1)'s condidate number
 */
inline int count_condidate(int r, int c, int *flag)
{
	int i, j;
	int count = 0; // number of condidates

	//init flag[i] with 0
	for (i=1; i<=9; i++)
		flag[i] = 0; 

	for (i=0; i<9; i++)
		flag[board[r][i]] = 1; 
	for (i=0; i<9; i++)
		flag[board[i][c]] = 1; 
	r = r/3*3;
	c = c/3*3;
	for (i=0; i<3; i++) 
		for (j=0; j<3; j++)
			flag[board[r+i][c+j]] = 1; 
      
	for (i=1; i<=9; i++)
		if (flag[i] == 0)
			count++; 
	return count; 
}


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
unsigned long long sudoku_solve(int puzzle[][9], unsigned long long mode)
{
	solutions = 0;

	// copy puzzle into board for solving 
	sudoku_copy(board, puzzle);

	//pass solving mode to backtracksolve
	backtrack_mode = mode;
	
	/*
	 * mode is set to 0: find all solutions.
	 */
	if (!backtrack_mode)
		backtracksolve();
	else if (sigsetjmp(exception_buf, 1) == 0)  // prepare to jump out 
			backtracksolve(); 
			//here backtracksolve normally exit

	return solutions;
}


