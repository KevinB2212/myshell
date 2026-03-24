# MyShell Makefile, Kevin Biju - Operating Systems Project 1
# ca216/myshell
CC = gcc
CFLAGS = -Wall
DEPS = myshell.h utility.h
OBJ = myshell.o utility.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

myshell: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f $(OBJ) myshell
