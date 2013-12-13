// Author: Andrew Reyes
// Date Last Modified: 11-29-2013

#ifndef DISPLAY_H
#define DISPLAY_H

// Prototypes.

void display(GtkTextBuffer *buffer, GtkWidget *tView, gchar *view, gint number);
//gint searchCharPos(gchar body[], gchar ch);
//gint charCount(gchar body[], gchar ch);
gint setChordPosition(GtkWidget *tView, GtkTextBuffer *buffer);

#endif

// End.