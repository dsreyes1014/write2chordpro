// Author: Andrew Reyes.
// Date Last Modified: 11-26-2013.

#ifndef EDITOR_H
#define EDITOR_H

// Prototypes.
#define COLUMN_N 130


gint get_chars(gchar *text, gchar *file_path, gint pos); // arg1 = out, arg2 = input filepath,
                                                       // arg3 = position in file;

gint set_text(gchar *text, gchar *filePath, gint pos);
gint get_line_char_count(gchar line[][COLUMN_N], gint line_num);
gint get_text_for_each_line(gchar lines[][COLUMN_N], gint line_num);
gint get_line_count(gchar *file_path);
void save(GtkWidget *widget, gpointer data);
void new_song(GtkWidget *widget, gpointer button);
void edit_song(GtkToggleButton *button, gpointer data);
void editor(GtkWidget *grid, GtkWidget *window);

#endif

// End.