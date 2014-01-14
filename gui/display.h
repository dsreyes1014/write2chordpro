// Author: Andrew Reyes
// Date Last Modified: 11-29-2013

#ifndef DISPLAY_H
#define DISPLAY_H

// Prototypes.

void display(GtkTextBuffer *buffer, GtkWidget *t_view);
//gint searchCharPos(gchar body[], gchar ch);
//gint charCount(gchar body[], gchar ch);
gint set_chord_position(GtkWidget *t_view, GtkTextBuffer *buffer);
gint text_tags(GtkTextBuffer *buffer, const gchar *text);

#endif

// End.