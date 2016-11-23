#CC=gcc
#CFLAGS=-I.
#DEPS= table.h block.h command.h
#OBJ= table.o block.o command.o dab.o

#%.o: %.c $(DEPS)
#	$(CC) -c -o $@ $< $(CFLAGS)

#dabmake: $(OBJ)
#	$(CC) -o $@ $^ $(CFLAGS) 
all: 
	gcc -o DAB dab.c table.c command.c block.c -std=c99
wine:
	winegcc -o DAB.exe dab.c table.c command.c block.c -std=c99
