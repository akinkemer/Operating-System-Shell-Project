GCC=gcc -I ./include/ -o

all: compile run
compile:
	$(GCC) ./lib/file_input.o -c ./src/file_input.c
	$(GCC) ./bin/shell ./lib/file_input.o ./src/shell.c

run:
	./bin/shell
