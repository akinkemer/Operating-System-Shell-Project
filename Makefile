all: compile run
compile:
	gcc -I ./include/ -o ./bin/shell ./src/shell.c

run:
	./bin/shell
