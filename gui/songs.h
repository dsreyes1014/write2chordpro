// Author: Andrew Reyes
// Date Last Modified: 11-26-2013

#ifndef SONGS_H
#define SONGS_H

// Prototypes.
void create_dir(void);
void save_dialog(void);
void activate_row(GtkTreeView *tree_view, gpointer data);
void song_select(GtkTreeSelection *selection, gpointer data);
void list_files(void);
void song_list(void);
void modified_entry(void);
void modified_buffer(GtkTextBuffer *buffer, gpointer data);

#endif

// End.