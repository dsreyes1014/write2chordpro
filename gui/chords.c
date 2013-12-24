// Author: Andrew Reyes.
// Date Last Modified: 11-25-2013.

#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>

#include "chords.h"
#include "editor.h"

GtkWidget *chordDialog, *treeView;
GtkTreeModel *model;
GtkTreeStore *treeStore;
GtkTreeIter selChord;
GtkTextMark *cursor;
GtkTreePath *path;

gchar *stringPath;
extern GtkTextBuffer *tBufferEditor;
extern GtkWidget *button5, *tViewEditor;

/*---------------------------------------------------------------------------*/
void activateChordRow(GtkTreeView *treeView, gpointer data)
{
	//GtkTreeIter selChord;
	GtkTextIter iter;
	gchar *getChord;
	
	if((strcmp(stringPath, "0") == 0) || (strcmp(stringPath, "0:0") == 0)
		|| (strcmp(stringPath, "0:1") == 0) || (strcmp(stringPath, "1") == 0)
		|| (strcmp(stringPath, "1:0") == 0) || (strcmp(stringPath, "2") == 0) || 
		(strcmp(stringPath, "2:0") == 0) || (strcmp(stringPath, "3") == 0)
		|| (strcmp(stringPath, "3:0") == 0) || (strcmp(stringPath, "3:1") == 0)
		|| (strcmp(stringPath, "4") == 0) || (strcmp(stringPath, "4:0") == 0)
		|| (strcmp(stringPath, "5") == 0) || (strcmp(stringPath, "5:0") == 0)
		|| (strcmp(stringPath, "6") ==0) || (strcmp(stringPath, "6:0") == 0)
		|| (strcmp(stringPath, "6:1") == 0))
	{
	}
	else if(gtk_text_view_get_editable(GTK_TEXT_VIEW(tViewEditor)) == TRUE)
	{
		gtk_tree_model_get(model, &selChord, 0, &getChord, -1);		

		g_print("%s\n", getChord);		
	
		gtk_text_buffer_insert_at_cursor(GTK_TEXT_BUFFER(tBufferEditor), getChord, -1);
		
		g_free(getChord);
		
		gtk_text_buffer_get_iter_at_mark(GTK_TEXT_BUFFER(tBufferEditor), &iter, cursor);
		
		// Move cursor forward one space out of brackets.
		gtk_text_iter_forward_chars(&iter, 1);
		gtk_text_buffer_place_cursor(GTK_TEXT_BUFFER(tBufferEditor), &iter);	
		
		// Hides dialog window from screen.
		gtk_widget_hide(chordDialog);
		
		gtk_widget_grab_focus(tViewEditor);
	}
}
/*---------------------------------------------------------------------------*/
void listChords(void)
{
	GtkTreeIter parent, child1, child2;
	
	// Adds toplevel row 'A' to the 'treeStore'. 	
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &parent, NULL);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &parent, 0, "A", -1);	
	
	// Section for chords 'A', 'A#', and 'Ab'.
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child1, &parent);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child1, 0, "A#", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child2, &child1);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child2, 0, "A#", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child2, &child1);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child2, 0, "A#m", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child2, &child1);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child2, 0, "A#7", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child2, &child1);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child2, 0, "A#M7", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child2, &child1);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child2, 0, "A#m7", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child2, &child1);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child2, 0, "A#2", -1);	
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child2, &child1);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child2, 0, "A#sus4", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child2, &child1);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child2, 0, "A#5", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child1, &parent);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child1, 0, "Ab", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child2, &child1);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child2, 0, "Ab", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child2, &child1);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child2, 0, "Abm", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child2, &child1);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child2, 0, "Ab7", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child2, &child1);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child2, 0, "AbM7", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child2, &child1);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child2, 0, "Abm7", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child2, &child1);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child2, 0, "Ab2", -1);	
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child2, &child1);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child2, 0, "Absus4", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child2, &child1);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child2, 0, "Ab5", -1);	
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child1, &parent);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child1, 0, "A", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child1, &parent);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child1, 0, "Am", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child1, &parent);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child1, 0, "A7", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child1, &parent);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child1, 0, "AM7", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child1, &parent);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child1, 0, "Am7", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child1, &parent);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child1, 0, "A2", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child1, &parent);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child1, 0, "Asus4", -1);	
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child1, &parent);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child1, 0, "A5", -1);
	
	// Adds toplevel row 'B' to 'treeStore'.
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &parent, NULL);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &parent, 0, "B", -1);
	
	// Sections for chords 'B' and 'Bb'.
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child1, &parent);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child1, 0, "Bb", -1);	
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child2, &child1);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child2, 0, "Bb", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child2, &child1);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child2, 0, "Bbm", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child2, &child1);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child2, 0, "Bb7", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child2, &child1);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child2, 0, "BbM7", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child2, &child1);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child2, 0, "Bbm7", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child2, &child1);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child2, 0, "Bb2", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child2, &child1);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child2, 0, "Bbsus4", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child2, &child1);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child2, 0, "Bb5", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child1, &parent);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child1, 0, "B", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child1, &parent);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child1, 0, "Bm", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child1, &parent);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child1, 0, "B7", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child1, &parent);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child1, 0, "BM7", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child1, &parent);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child1, 0, "Bm7", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child1, &parent);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child1, 0, "B2", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child1, &parent);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child1, 0, "Bsus4", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child1, &parent);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child1, 0, "B5", -1);

	// Adds toplevel row 'C' to 'treeStore'.
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &parent, NULL);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &parent, 0, "C", -1);
	
	// Sections for chords 'C' and 'C#'.
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child1, &parent);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child1, 0, "C#", -1);	
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child2, &child1);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child2, 0, "C#", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child2, &child1);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child2, 0, "C#m", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child2, &child1);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child2, 0, "C#7", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child2, &child1);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child2, 0, "C#M7", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child2, &child1);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child2, 0, "C#m7", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child2, &child1);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child2, 0, "C#2", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child2, &child1);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child2, 0, "C#sus4", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child2, &child1);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child2, 0, "C#5", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child1, &parent);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child1, 0, "C", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child1, &parent);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child1, 0, "Cm", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child1, &parent);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child1, 0, "C7", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child1, &parent);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child1, 0, "CM7", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child1, &parent);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child1, 0, "Cm7", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child1, &parent);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child1, 0, "C2", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child1, &parent);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child1, 0, "Csus4", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child1, &parent);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child1, 0, "C5", -1);
	
	// Adds toplevel row 'D' to the 'treeStore'. 	
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &parent, NULL);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &parent, 0, "D", -1);	
	
	// Section for chords 'D', 'D#', and 'Db'.
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child1, &parent);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child1, 0, "D#", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child2, &child1);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child2, 0, "D#", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child2, &child1);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child2, 0, "D#m", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child2, &child1);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child2, 0, "D#7", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child2, &child1);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child2, 0, "D#M7", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child2, &child1);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child2, 0, "D#m7", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child2, &child1);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child2, 0, "D#2", -1);	
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child2, &child1);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child2, 0, "D#sus4", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child2, &child1);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child2, 0, "D#5", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child1, &parent);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child1, 0, "Db", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child2, &child1);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child2, 0, "Db", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child2, &child1);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child2, 0, "Dbm", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child2, &child1);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child2, 0, "Db7", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child2, &child1);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child2, 0, "DbM7", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child2, &child1);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child2, 0, "Dbm7", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child2, &child1);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child2, 0, "Db2", -1);	
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child2, &child1);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child2, 0, "Dbsus4", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child2, &child1);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child2, 0, "Db5", -1);	
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child1, &parent);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child1, 0, "D", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child1, &parent);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child1, 0, "Dm", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child1, &parent);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child1, 0, "D7", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child1, &parent);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child1, 0, "DM7", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child1, &parent);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child1, 0, "Dm7", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child1, &parent);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child1, 0, "D2", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child1, &parent);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child1, 0, "Dsus4", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child1, &parent);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child1, 0, "D5", -1);
	
	// Adds toplevel row 'E' to 'treeStore'.
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &parent, NULL);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &parent, 0, "E", -1);
	
	// Sections for chords 'E' and 'Eb'.
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child1, &parent);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child1, 0, "Eb", -1);	
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child2, &child1);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child2, 0, "Eb", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child2, &child1);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child2, 0, "Ebm", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child2, &child1);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child2, 0, "Eb7", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child2, &child1);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child2, 0, "EbM7", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child2, &child1);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child2, 0, "Ebm7", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child2, &child1);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child2, 0, "Eb2", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child2, &child1);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child2, 0, "Ebsus4", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child2, &child1);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child2, 0, "Eb5", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child1, &parent);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child1, 0, "E", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child1, &parent);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child1, 0, "Em", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child1, &parent);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child1, 0, "E7", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child1, &parent);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child1, 0, "EM7", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child1, &parent);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child1, 0, "Em7", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child1, &parent);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child1, 0, "E2", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child1, &parent);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child1, 0, "Esus4", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child1, &parent);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child1, 0, "E5", -1);
	
	// Adds toplevel row 'F' to 'treeStore'.
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &parent, NULL);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &parent, 0, "F", -1);
	
	// Sections for chords 'F' and 'F#'.
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child1, &parent);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child1, 0, "F#", -1);	
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child2, &child1);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child2, 0, "F#", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child2, &child1);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child2, 0, "F#m", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child2, &child1);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child2, 0, "F#7", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child2, &child1);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child2, 0, "F#M7", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child2, &child1);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child2, 0, "F#m7", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child2, &child1);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child2, 0, "F#2", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child2, &child1);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child2, 0, "F#sus4", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child2, &child1);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child2, 0, "F#5", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child1, &parent);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child1, 0, "F", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child1, &parent);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child1, 0, "Fm", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child1, &parent);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child1, 0, "F7", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child1, &parent);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child1, 0, "FM7", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child1, &parent);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child1, 0, "Fm7", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child1, &parent);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child1, 0, "F2", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child1, &parent);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child1, 0, "Fsus4", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child1, &parent);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child1, 0, "F5", -1);
	
	// Adds toplevel row 'G' to the 'treeStore'. 	
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &parent, NULL);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &parent, 0, "G", -1);	
	
	// Section for chords 'G', 'G#', and 'Gb'.
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child1, &parent);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child1, 0, "G#", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child2, &child1);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child2, 0, "G#", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child2, &child1);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child2, 0, "G#m", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child2, &child1);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child2, 0, "G#7", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child2, &child1);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child2, 0, "G#M7", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child2, &child1);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child2, 0, "G#m7", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child2, &child1);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child2, 0, "G#2", -1);	
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child2, &child1);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child2, 0, "G#sus4", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child2, &child1);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child2, 0, "G#5", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child1, &parent);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child1, 0, "Gb", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child2, &child1);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child2, 0, "Gb", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child2, &child1);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child2, 0, "Gbm", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child2, &child1);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child2, 0, "Gb7", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child2, &child1);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child2, 0, "GbM7", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child2, &child1);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child2, 0, "Gbm7", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child2, &child1);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child2, 0, "Gb2", -1);	
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child2, &child1);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child2, 0, "Gbsus4", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child2, &child1);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child2, 0, "Gb5", -1);	
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child1, &parent);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child1, 0, "G", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child1, &parent);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child1, 0, "Gm", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child1, &parent);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child1, 0, "G7", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child1, &parent);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child1, 0, "GM7", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child1, &parent);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child1, 0, "Gm7", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child1, &parent);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child1, 0, "G2", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child1, &parent);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child1, 0, "Gsus4", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child1, &parent);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child1, 0, "G5", -1);
}

void chordSelect(GtkTreeSelection *selection, gpointer data)
{
	//GtkTreeIter selChord;
	//GtkTextIter iter; 
	//GtkTreePath *path;
	//gchar *getChord;
	
	if(gtk_tree_selection_get_selected(selection, &model, &selChord))
	{		
		path = gtk_tree_model_get_path(GTK_TREE_MODEL(model), &selChord);

		stringPath = gtk_tree_path_to_string(path);
		
		//g_print("%s\n", stringPath);
		
		
	}	
}

void insertChord(GtkWidget *widget, gpointer data)
{	
	GtkWidget *scrolledWindow;
	GtkWidget *frame, *topHalf, *bottomHalf, *label;
	GtkTreeViewColumn *column;
	GtkCellRenderer *cell; 
	GtkTextIter iter;
	GtkTreeSelection *selection;
	gchar *brackets;
	
	brackets = "[]";	//Instantiates (assigns) 'brackets'. 				
	cell = gtk_cell_renderer_text_new(); 
	treeStore = gtk_tree_store_new(1, G_TYPE_STRING); 
	treeView = gtk_tree_view_new_with_model(GTK_TREE_MODEL(treeStore));	
	cursor = gtk_text_buffer_get_insert(GTK_TEXT_BUFFER(tBufferEditor));   // Assigns cursor variable to the actual cursor within buffer.
	scrolledWindow = gtk_scrolled_window_new(NULL, NULL);	
	column = gtk_tree_view_column_new_with_attributes("Chord", cell, "text", 0, NULL); 
	frame = gtk_frame_new(NULL);		
	chordDialog = gtk_dialog_new();
	topHalf = gtk_dialog_get_content_area(GTK_DIALOG(chordDialog));
	bottomHalf = gtk_dialog_get_action_area(GTK_DIALOG(chordDialog));	
	label = gtk_label_new("Choose Chord");
	selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(treeView));	
	model = gtk_tree_view_get_model(GTK_TREE_VIEW(treeView));		
	
	if(gtk_text_view_get_editable(GTK_TEXT_VIEW(tViewEditor)) == TRUE)	
	{
		// Inserts string inside "..." at cursor location.
		gtk_text_buffer_insert_at_cursor(GTK_TEXT_BUFFER(tBufferEditor), brackets, 2);	
	
		// Initializes variable 'iter'.	
		gtk_text_buffer_get_iter_at_mark(GTK_TEXT_BUFFER(tBufferEditor), &iter, cursor);	
	
		// Moves cursor back one space.
		gtk_text_iter_backward_chars(&iter, 1);	
		gtk_text_buffer_place_cursor(GTK_TEXT_BUFFER(tBufferEditor), &iter);		
	}
	// Sets properties of frame & dialog widgets.	
	gtk_frame_set_shadow_type(GTK_FRAME(frame), GTK_SHADOW_ETCHED_IN);
		
	// Pack widgets.
	gtk_container_add(GTK_CONTAINER(scrolledWindow), treeView);
	gtk_container_add(GTK_CONTAINER(frame), scrolledWindow);
	gtk_container_add(GTK_CONTAINER(topHalf), label);
	gtk_container_add(GTK_CONTAINER(bottomHalf), frame);	
	
	gtk_tree_view_set_activate_on_single_click(GTK_TREE_VIEW(treeView), FALSE);	
	
	gtk_widget_show_all(chordDialog);	
	
	g_object_unref(treeStore);	
	
	listChords();	
		
	// Adds column to treeView.
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeView), column);
	
	gtk_tree_view_set_hover_expand(GTK_TREE_VIEW(treeView), TRUE);
		
	// Sets properties for chordDialog widget.	
	gtk_window_set_modal(GTK_WINDOW(chordDialog), TRUE);
	gtk_widget_set_size_request(chordDialog, 200, 320);	
	gtk_widget_set_size_request(frame, 190, 300);
	
	gtk_tree_selection_set_mode(GTK_TREE_SELECTION(selection), GTK_SELECTION_BROWSE);
	
	g_signal_connect(selection, "changed", G_CALLBACK(chordSelect), NULL);	
	g_signal_connect(treeView, "row-activated", G_CALLBACK(activateChordRow), NULL);		
}