CC = gcc
PROG_DIR = /opt/Write2chordpro
INSTALL_DIR = $(PROG_DIR)/bin
INCLUDE = $(PWD)/../include
LIBDIR = $(PWD)/../lib
CFLAGS = -Wall -c -std=c99 
CPPFLAGS = -I$(INCLUDE)/atk-1.0 -I$(INCLUDE)/cairo -I$(INCLUDE)/gtk-3.0 \
           -I$(INCLUDE)/pango-1.0 -I$(INCLUDE)/gdk-pixbuf-2.0 \
           -I$(LIBDIR)/glib-2.0/include -I$(INCLUDE)/glib-2.0 -I$(INCLUDE)/pixman-1 \
           -I$(INCLUDE)/freetype2 -I$(INCLUDE)/libpng16
LDFLAGS = -L$(PWD)/../lib
LIBS = -lgtk-3 -lgdk-3 -lgobject-2.0 -latk-1.0 -lgio-2.0 -lglib-2.0 -lpangoft2-1.0 \
       -lgdk_pixbuf-2.0 -lpangocairo-1.0 -lcairo -lpango-1.0 -lfreetype -lfontconfig \
       -lgmodule-2.0 -lgthread-2.0
PROGRAM = w2c-gui
OBJECTS = main.o menu.o chords.o songs.o editor.o display.o transpose.o
HEADERS = menu.h chords.h songs.h editor.h display.h transpose.h
GTK+3 = `pkg-config --cflags gtk+-3.0 --libs gtk+-3.0`
UNINSTALL = uninstallW2C
DEPS = lib include etc bin

all: $(PROGRAM)
$(PROGRAM): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) $(LIBS) -o $(PROGRAM)
main.o: main.c $(HEADERS)
	$(CC) $(CFLAGS) $(CPPFLAGS) main.c 
display.o: display.c editor.h songs.h
	$(CC) $(CFLAGS) $(CPPFLAGS) display.c 
menu.o: menu.c
	$(CC) $(CFLAGS) $(CPPFLAGS) menu.c 
chords.o: chords.c editor.h
	$(CC) $(CFLAGS) $(CPPFLAGS) chords.c 
songs.o: songs.c
	$(CC) $(CFLAGS) $(CPPFLAGS) songs.c 
editor.o: editor.c chords.h transpose.h
	$(CC) $(CFLAGS) $(CPPFLAGS) editor.c 
transpose.o: transpose.c editor.h
	$(CC) $(CFLAGS) $(CPPFLAGS) transpose.c 

clean: 
	rm -rfv $(OBJECTS) w2c-gui *~
install: $(PROG_DIR)
	cp -Rv ../bin $(PROG_DIR)/
	cp -Rv ../lib $(PROG_DIR)/
	cp -Rv ../etc $(PROG_DIR)/
	cp -v $(PROGRAM) $(INSTALL_DIR)/
	cp -v ../$(UNINSTALL) /opt/
	cp -v $(INSTALL_DIR)/$(PROGRAM) /usr/local/bin/
$(PROG_DIR): 
	./progDir
uninstall: check
	/opt/$(UNINSTALL)
	rm -v /opt/$(UNINSTALL) 
check:
	ls /opt/$(UNINSTALL)