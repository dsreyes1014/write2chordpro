// Author: Andrew Reyes.
// Date Last Modified: 11-26-2013.

#ifndef EDITOR_H
#define EDITOR_H

// Prototypes.
#define COLUMN_N 130

gint setEditorView(gchar *text, gchar *filePath, gint pos);
gint setKey(gchar *text, gchar *filePath, gint pos);
gint setGenre(gchar *text, gchar *filePath, gint pos);
gint setArtist(gchar *text, gchar *filePath, gint pos);
gint setTitle(gchar *text, gchar *filePath, gint lineNum);
gint getLineCharCount(gchar line[][COLUMN_N], gint lineNum);
gint getTextForEachLine(gchar lines[][COLUMN_N], gint lineNum);
gint getLineCount(gchar *filePath);
void save(GtkWidget *widget, gpointer data);
void newSong(GtkWidget *widget, gpointer data);
void editSong(GtkToggleToolButton *toggleTB, gpointer data);
void editor(void);

#endif

// End.