#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "generate.h"

#define MAX 1000 

char *db[3]={"easy.db", "medium.db", "hard.db"};

int main(void)
{
	int i, j, r, c, full[9][9], board[9][9];
	FILE *easy = fopen(db[0], "w+");
	FILE *medium = fopen(db[1], "w+");
	FILE *hard = fopen(db[2], "w+");
	FILE *fs[3] = { easy, medium, hard };
	int a[3] = {50, 30, 20};
	int b[3] = {31, 21, 11};
	
	if (!easy || !medium || !hard)
		return -1;

	srand(time(NULL));
	for (i=0; i<3; i++) {
		printf("Generating \"%s\"...\n[0\%%]", db[i]); 
		fflush(stdout);
		for (j=0; j<MAX; j++) {
			if (!((j+1)%100)) {
				printf("=>[%d\%%]",(j+1)/100*10);
				fflush(stdout);
			}
			generate_full(full);
			generate(board, a[i]+rand()%b[i], full);
			for (r=0; r<9; r++)
				for (c=0; c<9; c++)
					fputc('0'+board[r][c], fs[i]);
			fputc('\n', fs[i]);
		}
		printf("\nFinished.\n");
		fclose(fs[i]);
	}

	return 0;
}
