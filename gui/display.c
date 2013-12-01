// Author: Andrew Reye
// Date Last Modified: 11-29-2013

#include <gtk/gtk.h>
#include <stdio.h>

#include "display.h"
#include "editor.h"
#include "songs.h"

GtkWidget *tViewDisplay;
GtkTextBuffer *tBufferDisplay;
extern GtkWidget *entryTitle, *entryArtist, *tViewEditor;
extern const gchar *titleDisplay;
extern gchar displayBody[];

void display(void)
{	
	GtkTextIter start, end, line, ch;
	
	gint lineCount;
	
	tViewDisplay = gtk_text_view_new();
	tBufferDisplay = gtk_text_view_get_buffer(GTK_TEXT_VIEW(tViewDisplay));
	
	gtk_text_buffer_get_start_iter(GTK_TEXT_BUFFER(tBufferDisplay), &start);
	gtk_text_buffer_get_end_iter(GTK_TEXT_BUFFER(tBufferDisplay), &end);
	gtk_text_buffer_get_iter_at_line(GTK_TEXT_BUFFER(tBufferDisplay), &line, 0);
	gtk_text_buffer_get_iter_at_offset(GTK_TEXT_BUFFER(tBufferDisplay), &ch, 0);
	
	lineCount = gtk_text_buffer_get_line_count(GTK_TEXT_BUFFER(tBufferDisplay));
	
	g_print("Line count is: %d\n", lineCount);
	
	gtk_text_view_set_editable(GTK_TEXT_VIEW(tViewDisplay), FALSE);
	
	g_print("This is for the display: %s\n", displayBody);
}