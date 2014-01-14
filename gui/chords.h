// Author: Andrew Reyes.
// Date Last Modified: 11-25-2013.

#ifndef CHORDS_H
#define CHORDS_H

// Prototypes.
void list_chords(void);
void activate_chord_row(GtkTreeView *tree_view, gpointer data);
void chord_select(GtkTreeSelection *selection, gpointer data);
void insert_chord(GtkWidget *widget, gpointer data);

#endif

// End.