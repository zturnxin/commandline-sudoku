#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <regex.h>
#include "sudoku.h"
#include "stack.h"

#define CMDS 14 

char cmd_buf[1024];
static const char cmd_pattern[CMDS][50] = {
	"^[ \t]*fill[ \t]+([1-9]),([1-9])[ \t]+([1-9])[ \t]*\n$",
	"^[ \t]*fill[ \t]+unique[ \t]*\n$",
	"^[ \t]*fill[ \t]+all[ \t]*\n$",
	"^[ \t]*unfill[ \t]+([1-9]),([1-9])[ \t]*\n$",
	"^[ \t]*reset[ \t]*\n$",
	"^[ \t]*list[ \t]+([1-9]),([1-9])[ \t]*\n$",
	"^[ \t]*list[ \t]+,([1-9])[ \t]*\n$",
	"^[ \t]*list[ \t]+([1-9]),[ \t]*\n$",
	"^[ \t]*list[ \t]+([1-9])[ \t]*\n$",
	"^[ \t]*list[ \t]+unique[ \t]*\n$",
	"^[ \t]*list[ \t]+all[ \t]*\n$",
	"^[ \t]*disp[ \t]*\n$",
	"^[ \t]*undo[ \t]*\n$",
	"^[ \t]*quit[ \t]*\n$"
};

void internal_help(void)
{
	printf("\n\
Available Commands:\n\
\tfill i,j n\t# fill (i,j) with n\n\
\tfill unique\t# fill with unique condidate method\n\
\tfill all\t# fill the sudoku automatically.\n\
\tunfill i,j\t# unfill (i,j)\n\
\treset\t\t# reset the sudoku\n\
\tlist i,j\t# list condidates in (i,j)\n\
\tlist i,\t\t# list condidates in line i\n\
\tlist ,j\t\t# list condidates in coloum j\n\
\tlist i\t\t# list condidates in box(i,j)\n\
\tlist unique\t# list unique condidate grids\n\
\tlist all\t# list all condidates.\n\
\tdisp\t\t# display sudoku manually.\n\
\tquit\t\t# quit\n\
\tundo\t\t# undo\n\
\thelp\t\t# print help message\n\n\
Example:\n\
\tfill 3,4 5\
\t# fill grid (3,4) with 5\n\n");
}

int internal_cmd(void)
{
	regex_t re[CMDS];
	regmatch_t pmatch[4];
	int i;

	printf(">> ");
	fgets(cmd_buf, 1024, stdin);
	for (i=0; i<CMDS; i++) 
		if (regcomp(&re[i], cmd_pattern[i], REG_EXTENDED)) {
			printf("error compile cmd_pattern[%d].\n", i); 
			exit(1); 
		} 

	if (!regexec(re, cmd_buf, 4, pmatch, 0)) {
		fill_grid(sudoku, cmd_buf[pmatch[1].rm_so]-'0', cmd_buf[pmatch[2].rm_so]-'0', cmd_buf[pmatch[3].rm_so]-'0');
		if (!full())
			push();
	} else if (!regexec(re+1, cmd_buf, 0, NULL, 0)) {
		fill_unique(sudoku);
		if (!full())
			push();
	} else if (!regexec(re+2, cmd_buf, 0, NULL, 0)) {
		sudoku_solve(sudoku, 1);
		sudoku_copy(sudoku, board_solution);
		if (!full())
			push();
		disp(sudoku);
	} else if (!regexec(re+3, cmd_buf, 3, pmatch, 0)) {
		fill_grid(sudoku, cmd_buf[pmatch[1].rm_so]-'0', cmd_buf[pmatch[2].rm_so]-'0', 0);
		if (!full())
			push();
	} else if (!regexec(re+4, cmd_buf, 0, NULL, 0)) {
		sudoku_copy(sudoku, osudoku);	
		if (!full())
			push();
	} else if (!regexec(re+5, cmd_buf, 3, pmatch, 0)) {
		get_condidates(condidates, sudoku);
		dispcond_grid(cmd_buf[pmatch[1].rm_so]-'0', cmd_buf[pmatch[2].rm_so]-'0');
	} else if (!regexec(re+6, cmd_buf, 2, pmatch, 0)) {
		get_condidates(condidates, sudoku);
		dispcond_col(cmd_buf[pmatch[1].rm_so]-'0');
	} else if (!regexec(re+7, cmd_buf, 2, pmatch, 0)) {
		get_condidates(condidates, sudoku);
		dispcond_line(cmd_buf[pmatch[1].rm_so]-'0');
	} else if (!regexec(re+8, cmd_buf, 2, pmatch, 0)) {
		get_condidates(condidates, sudoku);
		dispcond_box(cmd_buf[pmatch[1].rm_so]-'0');
	} else if (!regexec(re+9, cmd_buf, 0, NULL, 0)) {
		get_condidates(condidates, sudoku);
		dispcond_unique();
	} else if (!regexec(re+10, cmd_buf, 0, NULL, 0)) {
		get_condidates(condidates, sudoku);
		dispcand_all();
	} else if (!regexec(re+11, cmd_buf, 0, NULL, 0)) {
		disp(sudoku);
	} else if (!regexec(re+12, cmd_buf, 0, NULL, 0)) {
		if (!empty())
			pop();
	} else if (!regexec(re+13, cmd_buf, 0, NULL, 0)) {
		return 1;
	} else
		internal_help();	

	for (i=0; i<CMDS; i++)
		regfree(re+i);
	return 0;
}

int main(void)
{
	int choose;

	srand(time(NULL));
	do {
		menu();
		while ((choose = getchar()) == ' ' || choose == '\t');	
		while (getchar() != '\n');
		switch (choose) {
			case '1': load("easy.db", 1000); break;
			case '2': load("medium.db", 1000); break;
			case '3': load("hard.db", 1000); break;
			case '4': continue;
			default: printf("Invalid choose!\n"); continue;
		}

		disp(sudoku);
		push();
		while(!internal_cmd());

	} while (choose != '4');

	return 0;
}
