// Author: Andrew Reyes.
// Date Last Modified: 11-26-2013.

#ifndef EDITOR_H
#define EDITOR_H

// Prototypes.
#define COLUMN_N 130


gint getChars(gchar *text, gchar *filePath, gint pos); // arg1 = out, arg2 = input filepath,
                                                       // arg3 = position in file;

gint setText(gchar *text, gchar *filePath, gint pos);
gint getLineCharCount(gchar line[][COLUMN_N], gint lineNum);
gint getTextForEachLine(gchar lines[][COLUMN_N], gint lineNum);
gint getLineCount(gchar *filePath);
void save(GtkWidget *widget, gpointer data);
void newSong(GtkWidget *widget, gpointer button);
void editSong(GtkToggleButton *button, gpointer data);
void editor(GtkWidget *grid, GtkWidget *window);

#endif

// End.