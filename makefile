all: shell.c
	gcc -o shell shell.c
run: all
	./shell
