#include <stdio.h>
/* 
 * count a file's max line by filestream and return
 */
int maxlines(char *fn) 
{
	int count = -1;
	char line[1024];
	FILE *fs = fopen(fn, "r");

	if (!fs) {
		printf("can't open file \"%s\"...\n", fn);
		return -1;
	}

	while (!feof(fs)) {
		fgets(line,1024,fs);
		count++;
	}
	return count;
}

