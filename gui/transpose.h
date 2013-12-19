// Author: Andrew Reyes
// Date: 12-18-2013

#ifndef TRANSPOSE_H
#define TRANSPOSE_H

// Prototypes.

gint slashChordDown(void);
gint slashChordUp(void);
gint chordUp(void);
gint chordDown(void);
void transposeDown(GtkWidget *button, gpointer data);
void transposeUp(GtkWidget *button, gpointer data);

#endif