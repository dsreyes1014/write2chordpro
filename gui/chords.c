// Author: Andrew Reyes.
// Date Last Modified: 11-25-2013.

#include <gtk/gtk.h>
#include <stdio.h>
#include "chords.h"

GtkWidget *chordDialog;
GtkTreeStore *treeStore;
extern GtkTextBuffer *buffer;

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
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child2, 0, "A#sus2", -1);	
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child2, &child1);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child2, 0, "A#sus4", -1);
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
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child2, 0, "Absus2", -1);	
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child2, &child1);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child2, 0, "Absus4", -1);	
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
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child1, 0, "Asus2", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child1, &parent);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child1, 0, "Asus4", -1);	
	
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
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child2, 0, "Bbsus2", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child2, &child1);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child2, 0, "Bbsus4", -1);
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
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child1, 0, "Bsus2", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child1, &parent);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child1, 0, "Bsus4", -1);
}

void chordSelect(GtkWidget *widget, gpointer data)
{
	GtkTreeIter selChord;
	GtkTextIter iter; 
	GtkTreePath *path;
	gchar *getChord;
	
	if(gtk_tree_selection_get_selected(GTK_TREE_SELECTION(widget), &model, &selChord))
	{		
		path = gtk_tree_model_get_path(GTK_TREE_MODEL(model), &selChord);

		gchar *stringPath = gtk_tree_path_to_string(path);
		
		g_print("%s\n", stringPath);
		
		if((strcmp(stringPath, "0") == 0) || (strcmp(stringPath, "0:0") == 0)
			|| (strcmp(stringPath, "0:1") == 0) || (strcmp(stringPath, "1") == 0)
			|| (strcmp(stringPath, "1:0") == 0))
		{
		}
		else 
		{
			gtk_tree_model_get(model, &selChord, 0, &getChord, -1);		

			g_print("%s\n", getChord);		
		
			gtk_text_buffer_insert_at_cursor(GTK_TEXT_BUFFER(buffer), getChord, -1);
		
			g_free(getChord);
		
			gtk_text_buffer_get_iter_at_mark(GTK_TEXT_BUFFER(buffer), &iter, cursor);
		
		// Move cursor forward one space out of brackets.
		gtk_text_iter_forward_chars(&iter, 1);
		gtk_text_buffer_place_cursor(GTK_TEXT_BUFFER(buffer), &iter);	
		
		// Hides dialog window from screen.
		gtk_widget_hide(chordDialog);
		}
	}	
}

static void insertChord(GtkWidget *widget, gpointer data)
{	
	GtkWidget *scrolledWindow, *treeView;
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
	cursor = gtk_text_buffer_get_insert(GTK_TEXT_BUFFER(buffer));   // Assigns cursor variable to the actual cursor within buffer.
	scrolledWindow = gtk_scrolled_window_new(NULL, NULL);	
	column = gtk_tree_view_column_new_with_attributes("Chord", cell, "text", 0, NULL); 
	frame = gtk_frame_new(NULL);		
	chordDialog = gtk_dialog_new();
	topHalf = gtk_dialog_get_content_area(GTK_DIALOG(chordDialog));
	bottomHalf = gtk_dialog_get_action_area(GTK_DIALOG(chordDialog));	
	label = gtk_label_new("Choose Chord");
	selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(treeView));	
	model = gtk_tree_view_get_model(GTK_TREE_VIEW(treeView));	
	
	// Sets cursor to visible. I think it's set by default but adding it to make sure.
	gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(textView), TRUE);	
	
	// Inserts string inside "..." at cursor location.
	gtk_text_buffer_insert_at_cursor(GTK_TEXT_BUFFER(buffer), brackets, 2);	
	
	// Initializes variable 'iter'.	
	gtk_text_buffer_get_iter_at_mark(GTK_TEXT_BUFFER(buffer), &iter, cursor);	
	
	// Moves cursor back one space.
	gtk_text_iter_backward_chars(&iter, 1);	
	gtk_text_buffer_place_cursor(GTK_TEXT_BUFFER(buffer), &iter);		
	
	// Sets properties of frame & dialog widgets.	
	gtk_frame_set_shadow_type(GTK_FRAME(frame), GTK_SHADOW_ETCHED_IN);
		
	// Pack widgets.
	gtk_container_add(GTK_CONTAINER(scrolledWindow), treeView);
	gtk_container_add(GTK_CONTAINER(frame), scrolledWindow);
	gtk_container_add(GTK_CONTAINER(topHalf), label);
	gtk_container_add(GTK_CONTAINER(bottomHalf), frame);	
	
	gtk_tree_view_set_activate_on_single_click(GTK_TREE_VIEW(treeView), TRUE);	
	
	gtk_widget_show_all(chordDialog);	
	
	g_object_unref(treeStore);	
	
	listChords();	
		
	// Adds column to treeView.
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeView), column);
		
	// Sets properties for chordDialog widget.	
	gtk_window_set_modal(GTK_WINDOW(chordDialog), TRUE);
	gtk_widget_set_size_request(chordDialog, 200, 320);	
	gtk_widget_set_size_request(frame, 190, 300);
	
	gtk_tree_selection_set_mode(GTK_TREE_SELECTION(selection), GTK_SELECTION_BROWSE);
	
	g_signal_connect(selection, "changed", G_CALLBACK(chordSelect), NULL);			
}