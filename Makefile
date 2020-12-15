GCC=gcc -I ./include/ -o

all: compile
compile:
	$(GCC) ./bin/shell ./src/shell.c

