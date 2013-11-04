CC = gcc
CFLAGS = -Wall -c 
OBJ = main.o createdir.o openfile.o input.o editor.o
HEADER = createdir.h openfile.h input.h editor.h

all: w2c
w2c: $(OBJ) $(HEADER)
	$(CC) $(OBJ) -o w2c
createdir.o: createdir.c createdir.h 
	$(CC) $(CFLAGS) createdir.c
openfile.o: openfile.c openfile.h
	$(CC) $(CFLAGS) openfile.c
input.o: input.c input.h
	$(CC) $(CFLAGS) input.c
editor.o: editor.c editor.h
	$(CC) $(CFLAGS) editor.c
main.o: main.c $(HEADER)
	$(CC) $(CFLAGS) main.c
install:
	sudo cp -v w2c /usr/bin/
clean:
	rm -v *.o w2c