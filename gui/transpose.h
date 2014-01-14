// Author: Andrew Reyes
// Date: 12-18-2013

#ifndef TRANSPOSE_H
#define TRANSPOSE_H

// Prototypes.

gint slash_chord_down(void);
gint slash_chord_up(void);
gint chord_up(void);
gint chord_down(void);
void transpose_down(GtkWidget *button, gpointer data);
void transpose_up(GtkWidget *button, gpointer data);

#endif