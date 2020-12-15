GCC=gcc -I ./include/ -o

all: compile run
compile:
	$(GCC) ./bin/shell ./src/shell.c

run:
	./bin/shell
