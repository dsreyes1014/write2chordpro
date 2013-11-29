// Author: Andrew Reyes.
// Date Last Modified: 11-26-2013.

#include <gtk/gtk.h>
#include <stdio.h>

#include "chords.h"
#include "songs.h"

GtkWidget *entryTitle, *entryArtist, *textView, *grid;
GtkEntryBuffer *entryBuffer;
GtkTextBuffer *buffer;
const gchar *getTitle, *getArtist;
extern char directory[];
extern GtkListStore *listStore;
extern GtkTreeSelection *selection;

void save(GtkWidget *widget, gpointer data)
{	
	GtkTextIter start, end;	
	gchar *body;
	char newFile[25];
	
	FILE *pFile;		
	
	gtk_text_buffer_get_start_iter(GTK_TEXT_BUFFER(buffer), &start);
	gtk_text_buffer_get_end_iter(GTK_TEXT_BUFFER(buffer), &end);	
	
	getTitle = gtk_entry_get_text(GTK_ENTRY(entryTitle));
	getArtist = gtk_entry_get_text(GTK_ENTRY(entryArtist));
	body = gtk_text_buffer_get_text(GTK_TEXT_BUFFER(buffer), &start, &end, TRUE);
	
	sprintf(newFile, "%s%s.chordpro", directory, getTitle);
	
	pFile = fopen(newFile, "w+");
		
	fprintf(pFile, "{title: %s}\n", getTitle);
	fprintf(pFile, "{subtitle: %s}\n\n", getArtist);
	fprintf(pFile, "%s\n", body);
	
	fclose(pFile);
	
	gtk_list_store_clear(GTK_LIST_STORE(listStore));	
	
	listFiles();	
}

void newSong(GtkWidget *widget, gpointer data)
{
	GtkTextIter start, end;	
	
	// Unselects all in 'songList' so it will not appear in song editor.	
	gtk_tree_selection_unselect_all(GTK_TREE_SELECTION(selection));	
	
	entryBuffer = gtk_entry_get_buffer(GTK_ENTRY(entryTitle));
	
	gtk_entry_buffer_delete_text(GTK_ENTRY_BUFFER(entryBuffer), 0, -1);

	entryBuffer = gtk_entry_get_buffer(GTK_ENTRY(entryArtist));
	
	gtk_entry_buffer_delete_text(GTK_ENTRY_BUFFER(entryBuffer), 0, -1);
	
	gtk_text_buffer_get_start_iter(GTK_TEXT_BUFFER(buffer), &start);
	gtk_text_buffer_get_end_iter(GTK_TEXT_BUFFER(buffer), &end);
	
	gtk_text_buffer_delete(GTK_TEXT_BUFFER(buffer), &start, &end);
}

void editSong(GtkWidget *widget, gpointer data)
{
	gtk_editable_set_editable(GTK_EDITABLE(entryTitle), TRUE);
	
	gtk_editable_set_editable(GTK_EDITABLE(entryArtist), TRUE);
	
	gtk_text_view_set_editable(GTK_TEXT_VIEW(textView), TRUE);
}

void editor(void)
{
	GtkWidget *label1, *label2, *button1, *button2, *button3,
			    *button4, *button5, *frame, *boxTop, *scrolledWindow,
			    *boxBottom;
		
	grid = gtk_grid_new();
	entryTitle = gtk_entry_new();
	entryArtist = gtk_entry_new();
	label1 = gtk_label_new("Title:");
	label2 = gtk_label_new("Artist:");
	textView = gtk_text_view_new();
	buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textView));
	button1 = gtk_button_new_with_label("Insert Chord");
	button2 = gtk_button_new_with_label("Transpose");
	button3 = gtk_button_new_with_label("Add New");
	button4 = gtk_button_new_with_label("Save");
	button5 = gtk_toggle_button_new_with_label("Edit");
	frame = gtk_frame_new(NULL);
	boxTop = gtk_box_new(GTK_ORIENTATION_VERTICAL, 2);
	boxBottom = gtk_box_new(GTK_ORIENTATION_VERTICAL, 2);
	scrolledWindow = gtk_scrolled_window_new(NULL, NULL);
	
	gtk_entry_set_placeholder_text(GTK_ENTRY(entryTitle), "Enter name of title here");
	gtk_entry_set_placeholder_text(GTK_ENTRY(entryArtist), "Enter name of artist here");
	
	// Sets cursor to visible. I think it's set by default but adding it to make sure.
	gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(textView), TRUE);

	// Properties for 'frame' widget.	
	gtk_frame_set_shadow_type(GTK_FRAME(frame), GTK_SHADOW_ETCHED_IN);	
	gtk_widget_set_size_request(GTK_WIDGET(frame), 100, 100);
	
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(button5), FALSE);
	
	// Packs 'button3' & 'button4' into 'boxTop'.
	gtk_box_pack_start(GTK_BOX(boxTop), button3, FALSE, FALSE, 2);
	gtk_box_pack_start(GTK_BOX(boxTop), button5, FALSE, FALSE, 2);
	gtk_box_pack_start(GTK_BOX(boxTop), button4, FALSE, FALSE, 2); 
	// Packs 'button1' & 'button2' widgets into 'boxBottom' widget.
	gtk_box_pack_start(GTK_BOX(boxBottom), button1, FALSE, FALSE, 2);
	gtk_box_pack_start(GTK_BOX(boxBottom), button2, FALSE, FALSE, 2);    
	
	// Packs 'textView' widget inside of 'scrolledWindow' widget.	
	gtk_container_add(GTK_CONTAINER(scrolledWindow), textView);
	
	// Packs 'scrolledWindow' widget into 'frame2' widget.
	gtk_container_add(GTK_CONTAINER(frame), scrolledWindow);
    
    // Attaches widgets to widget grid.	
	gtk_grid_attach(GTK_GRID(grid), label1, 3, 1, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), label2, 3, 10, 1, 1);	
	gtk_grid_attach_next_to(GTK_GRID(grid), entryTitle, label1, GTK_POS_RIGHT, 80, 1);
	gtk_grid_attach_next_to(GTK_GRID(grid), entryArtist, label2, GTK_POS_RIGHT, 80, 1);
	gtk_grid_attach(GTK_GRID(grid), frame, 0, 14, 130, 150);
	gtk_grid_attach_next_to(GTK_GRID(grid), boxTop, frame, GTK_POS_RIGHT, 1, 50);
	gtk_grid_attach_next_to(GTK_GRID(grid), boxBottom, boxTop, GTK_POS_BOTTOM, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), button3, 80, 10, 1, 1);
	
	// Sets row & column spacing between widgets inside 'grid' widget.
	gtk_grid_set_row_spacing(GTK_GRID(grid), 3);
	gtk_grid_set_column_spacing(GTK_GRID(grid), 3);	
	
	// Connects function 'insertChord' to 'button1' widget.	
	g_signal_connect(button1, "clicked", G_CALLBACK(insertChord), NULL);
	// Connects function 'save' to 'button3' labeled "Save".
	g_signal_connect(button4, "clicked", G_CALLBACK(save), NULL);
	g_signal_connect(button3, "clicked", G_CALLBACK(newSong), NULL);
	g_signal_connect(button5, "toggled", G_CALLBACK(editSong), NULL);
}