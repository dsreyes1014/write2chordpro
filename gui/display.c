// Author: Andrew Reye
// Date Last Modified: 11-29-2013

#include <gtk/gtk.h>
#include <stdio.h>

#include "display.h"
#include "editor.h"

GtkWidget *tViewDisplay;
extern GtkWidget *entryTitle, *entryArtist, *tViewEditor;

void display(void)
{
	GtkTextBuffer *tBufferDisplay;
	GtkTextIter start, end;
	gchar display[15][100];
	const gchar *title, *artist;	
	
	tViewDisplay = gtk_text_view_new();
	tBufferDisplay = gtk_text_view_get_buffer(GTK_TEXT_VIEW(tViewDisplay));
	
	gtk_text_buffer_get_start_iter(GTK_TEXT_BUFFER(tBufferDisplay), &start);
	gtk_text_buffer_get_end_iter(GTK_TEXT_BUFFER(tBufferDisplay), &end);
	
	gtk_text_view_set_editable(GTK_TEXT_VIEW(tViewDisplay), FALSE);
	
	title = gtk_entry_get_text(GTK_ENTRY(entryTitle));
	
	g_print("%s\n", title);
	
	gtk_text_buffer_insert_at_cursor(GTK_TEXT_BUFFER(tBufferDisplay), title, -1);
	
	artist = gtk_entry_get_text(GTK_ENTRY(entryArtist));
	
}