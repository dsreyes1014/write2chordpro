CC = gcc
INSTALL_DIR = /usr/local/bin/
CFLAGS = -Wall -c -std=c99
PROGRAM = w2c-gui
OBJECTS = main.o menu.o chords.o songs.o editor.o display.o
HEADERS = menu.h chords.h songs.h editor.h display.h
GTK+3 = `pkg-config --cflags gtk+-3.0 --libs gtk+-3.0`

all: $(PROGRAM)
$(PROGRAM): $(OBJECTS)
	$(CC) $(OBJECTS) $(GTK+3) -o $(PROGRAM)
main.o: main.c $(HEADERS)
	$(CC) $(CFLAGS) main.c $(GTK+3)
menu.o: menu.c
	$(CC) $(CFLAGS) menu.c $(GTK+3)
chords.o: chords.c editor.h
	$(CC) $(CFLAGS) chords.c $(GTK+3)
songs.o: songs.c
	$(CC) $(CFLAGS) songs.c $(GTK+3)
editor.o: editor.c chords.h
	$(CC) $(CFLAGS) editor.c $(GTK+3)
display.o: display.c editor.h
	$(CC) $(CFLAGS) display.c $(GTK+3)
clean: 
	rm -rfv $(OBJECTS) w2c-gui
install:
	sudo cp -v $(PROGRAM) $(INSTALL_DIR)
uninstall: $(INSTALL_DIR)$(PROGRAM)
	sudo rm -v $(INSTALL_DIR)$(PROGRAM)
$(INSTALL_DIR)$(PROGRAM):
	ls $(INSTALL_DIR)$(PROGRAM)
