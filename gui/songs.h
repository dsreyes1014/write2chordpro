// Author: Andrew Reyes
// Date Last Modified: 11-26-2013

#ifndef SONGS_H
#define SONGS_H

// Prototypes.
void create_dir(void);
void save_dialog(void);
void activate_row(GtkWidget *widget, gpointer data);
void song_select(GtkTreeSelection *tree_selection, gpointer data);
void list_files(void);
void song_list(void);
void append_to_list(gchar *value);

#endif

// End.