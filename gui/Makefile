CC = gcc
PROG_DIR = /opt/Write2chordpro
INSTALL_DIR = $(PROG_DIR)/bin
CFLAGS = -Wall -c -std=c99 -I../include -L../lib
PROGRAM = w2c-gui
OBJECTS = main.o menu.o chords.o songs.o editor.o display.o transpose.o
HEADERS = menu.h chords.h songs.h editor.h display.h transpose.h
GTK+3 = `pkg-config --cflags gtk+-3.0 --libs gtk+-3.0`
UNINSTALL = uninstallW2C
DEPS = lib include etc bin

all: $(PROGRAM)
$(PROGRAM): $(OBJECTS)
	$(CC) $(OBJECTS) $(GTK+3) -o $(PROGRAM)
main.o: main.c $(HEADERS)
	$(CC) $(CFLAGS) main.c $(GTK+3)
display.o: display.c editor.h songs.h
	$(CC) $(CFLAGS) display.c $(GTK+3)
menu.o: menu.c
	$(CC) $(CFLAGS) menu.c $(GTK+3)
chords.o: chords.c editor.h
	$(CC) $(CFLAGS) chords.c $(GTK+3)
songs.o: songs.c
	$(CC) $(CFLAGS) songs.c $(GTK+3)
editor.o: editor.c chords.h transpose.h
	$(CC) $(CFLAGS) editor.c $(GTK+3)
transpose.o: transpose.c editor.h
	$(CC) $(CFLAGS) transpose.c $(GTK+3)

clean: 
	rm -rfv $(OBJECTS) w2c-gui *~
install: makedirectory
	cp -Rv ../bin $(PROG_DIR)/
	cp -Rv ../lib $(PROG_DIR)/
	cp -Rv ../etc $(PROG_DIR)/
	cp -v $(PROGRAM) $(INSTALL_DIR)/
	cp -v ../$(UNINSTALL) /opt
	cp -v $(INSTALL_DIR)/$(PROGRAM) /usr/local/bin
makedirectory:
	mkdir -v $(PROG_DIR)
uninstall: check
	/opt/$(UNINSTALL)
	rm -v /opt/$(UNINSTALL) 
check:
	ls /opt/$(UNINSTALL)
