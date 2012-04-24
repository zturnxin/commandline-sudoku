CC=gcc

CFLAGS:=-Wall -g

sudoku: sudoku.o countlines.o load.o zone.o disp.o stack.o fill.o check.o backtracksolve.o generate.o 
	${CC} ${CFLAGS} $^ -o $@

clean:
	-rm -v sudoku *.o 

.PHONY: clean

install-db:
	@${CC} -Wall -c generate_db_main.c -o generate_db_main.o
	@${CC} -Wall -g generate.o zone.o check.o backtracksolve.o generate_db_main.o -o generate_db_main 
	@./generate_db_main

uninstall-db:
	@rm -f generate_db_main generate_db_main.o *db
