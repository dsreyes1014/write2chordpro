CC = gcc
INSTALL_DIR = /usr/local/bin/
CFLAGS = -Wall -c
OBJ = main.o createdir.o openfile.o input.o editor.o
OBJDIR = .objects/
SRCDIR = src/
PROGRAM = w2c
HEADERS = $(SRCDIR)createdir.h $(SRCDIR)openfile.h $(SRCDIR)input.h $(SRCDIR)editor.h

all: w2c
w2c: $(OBJ)
	$(CC) $(OBJDIR)*.o -o $(PROGRAM)
$(OBJ): $(OBJDIR)
$(OBJDIR):
	mkdir -v .objects
main.o: $(SRCDIR)main.c $(HEADERS)
	$(CC) $(CFLAGS) $(SRCDIR)main.c
	mv -v main.o $(OBJDIR) 
createdir.o: $(SRCDIR)createdir.c
	$(CC) $(CFLAGS) $(SRCDIR)createdir.c
	mv -v createdir.o $(OBJDIR) 
openfile.o: $(SRCDIR)openfile.c
	$(CC) $(CFLAGS) $(SRCDIR)openfile.c
	mv -v openfile.o $(OBJDIR) 
input.o: $(SRCDIR)input.c
	$(CC) $(CFLAGS) $(SRCDIR)input.c
	mv -v input.o $(OBJDIR) 
editor.o: $(SRCDIR)editor.c
	$(CC) $(CFLAGS) $(SRCDIR)editor.c
	mv -v editor.o $(OBJDIR) 
clean:
	rm -rfv $(OBJDIR) w2c
install:
	sudo cp -v w2c $(INSTALL_DIR)
uninstall: $(INSTALL_DIR)$(PROGRAM)
	sudo rm -v $(INSTALL_DIR)$(PROGRAM)
$(INSTALL_DIR)$(PROGRAM):
	ls $(INSTALL_DIR)$(PROGRAM)