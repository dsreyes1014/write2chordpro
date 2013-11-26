// Author: Andrew Reyes.
// Date Modified: 11-25-2013. 

#include <gtk/gtk.h>
#include <string.h>
#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "menu.h"
#include "chords.h"

GtkWidget *window;
GtkWidget *entryTitle, *entryArtist;
GtkWidget *textView;
GtkTextBuffer *buffer;
GtkTreeStore *treeStore;
GtkTreeSelection *selection;
GtkTreeViewColumn *column;
GtkTreeModel *model;
GtkTextMark *cursor;
GtkListStore *listStore;
const gchar *getTitle, *getArtist;
gchar *filename;

int main(int argc, char *argv[])
{
	GtkWidget *box1, *box2, *box3;
	GtkWidget *paned;
	GtkWidget *frame1, *frame2;
	GtkWidget *notebook;
	GtkWidget *grid;
	GtkWidget *label1, *label2;
	GtkWidget *tabLabel;
	GtkWidget *treeView1;
	GtkWidget *scrolledWindow, *scrolledWindow1;
	GtkWidget *button1, *button2, *button3;
	GtkCellRenderer *cell;
	GtkTreeViewColumn *column;
		
	gtk_init(&argc, &argv);
	
	box1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 2);
	box2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
	box3 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 2);
	paned = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);
	notebook = gtk_notebook_new();
	grid = gtk_grid_new();
	label1 = gtk_label_new("Title:");
	label2 = gtk_label_new("Artist:");
	entryTitle = gtk_entry_new();
	entryArtist = gtk_entry_new();
	frame1 = gtk_frame_new(NULL);	
	frame2 = gtk_frame_new(NULL);
	scrolledWindow = gtk_scrolled_window_new(NULL, NULL);
	scrolledWindow1 = gtk_scrolled_window_new(NULL, NULL);
	button1 = gtk_button_new_with_label("Insert Chord");
	button2 = gtk_button_new_with_label("Transpose");
	button3 = gtk_button_new_with_label("Save");
	textView = gtk_text_view_new();	
	buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textView));
	listStore = gtk_list_store_new(1, G_TYPE_STRING);
	treeView1 = gtk_tree_view_new_with_model(GTK_TREE_MODEL(listStore));
	cell = gtk_cell_renderer_text_new();	
	column = gtk_tree_view_column_new_with_attributes("Songs", cell, "text", NULL);	
		
	gtk_entry_set_placeholder_text(GTK_ENTRY(entryTitle), "Enter name of title here");
	gtk_entry_set_placeholder_text(GTK_ENTRY(entryArtist), "Enter name of artist here");	
	                                         
	// This creates main window titled 'Write 2 Chordpro'.
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "Write 2 Chordpro");
	
	menuFunc();
		
	// Packs menubar and paned in box1.
	gtk_box_pack_start(GTK_BOX(box1), menuBar, FALSE, FALSE, 2);
	gtk_box_pack_start(GTK_BOX(box1), paned, FALSE, FALSE, 2);
	
	gtk_frame_set_shadow_type(GTK_FRAME(frame1), GTK_SHADOW_ETCHED_IN);
	gtk_frame_set_shadow_type(GTK_FRAME(frame2), GTK_SHADOW_ETCHED_IN);

	// Sizes frame2.	
	gtk_widget_set_size_request(GTK_WIDGET(frame2), 100, 100);
	
	// Packs textView inside of scrolledWindow.	
	gtk_container_add(GTK_CONTAINER(scrolledWindow), textView);
	
	// Packs scrolledWindow into frame2.
	gtk_container_add(GTK_CONTAINER(frame2), scrolledWindow);
	
	// Places button1 & button2 into box3.
	gtk_box_pack_start(GTK_BOX(box3), button1, FALSE, FALSE, 2);
	gtk_box_pack_start(GTK_BOX(box3), button2, FALSE, FALSE, 2);
	
	// Connects function to button 'insertChord'.	
	g_signal_connect(button1, "clicked", G_CALLBACK(insertChord), NULL);
		
	/* Attaches widgets to widget grid */	
	gtk_grid_attach(GTK_GRID(grid), label1, 3, 1, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), label2, 3, 10, 1, 1);	
	gtk_grid_attach_next_to(GTK_GRID(grid), entryTitle, label1, GTK_POS_RIGHT, 100, 1);
	gtk_grid_attach_next_to(GTK_GRID(grid), entryArtist, label2, GTK_POS_RIGHT, 100, 1);
	gtk_grid_attach(GTK_GRID(grid), frame2, 0, 14, 130, 150);
	gtk_grid_attach_next_to(GTK_GRID(grid), box3, frame2, GTK_POS_RIGHT, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(grid), button3, entryArtist, GTK_POS_RIGHT, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(grid), separator, frame2, GTK_POS_TOP, 1, 1);
	
	// Connects function to button 'Print Song'.
	g_signal_connect(button3, "clicked", G_CALLBACK(save), NULL);
	
	// Sets row & column spacing between widgets inside grid.
	gtk_grid_set_row_spacing(GTK_GRID(grid), 3);
	gtk_grid_set_column_spacing(GTK_GRID(grid), 3);
	
	// Creates tabs for 'notebook' widget.
	gtk_notebook_append_page(GTK_NOTEBOOK(notebook), box2, NULL);
	gtk_notebook_append_page(GTK_NOTEBOOK(notebook), grid, NULL);
	
	// Sets labels for 'notebook' widget tabs.	
	tabLabel = gtk_label_new("Display");	
	gtk_notebook_set_tab_label(GTK_NOTEBOOK(notebook), box2, tabLabel);	
	tabLabel = gtk_label_new("Song Editor");	
	gtk_notebook_set_tab_label(GTK_NOTEBOOK(notebook), grid, tabLabel);
	
	listFiles();	
	
	// Add column to treeView1.	
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeView1), column);
	
	// Packs 'treeView1' widget into 'scrolledWindow1' widget
	// and 'scrolledWindow1' widget  into 'frame1' widget.
	gtk_container_add(GTK_CONTAINER(scrolledWindow1), treeView1);	
	gtk_container_add(GTK_CONTAINER(frame1), scrolledWindow1);
	
	// Packs 'frame1' & 'notebook' widgets inside pane 1 & 2 respectively.
	gtk_paned_pack1(GTK_PANED(paned), frame1, FALSE, TRUE);
	gtk_paned_pack2(GTK_PANED(paned), notebook, FALSE, TRUE);
	
	// Sizes both 'frame' and 'notebook' widgets. 
	gtk_widget_set_size_request(frame1, 200, 75);
	gtk_widget_set_size_request(notebook, 300, 150);
	
	// This signal terminates main window when the close button is clicked.	
	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	
	// Adds the paned widget to main window widget.	
	gtk_container_add(GTK_CONTAINER(window), box1);
	
	// Make toplevel window and it's child windows visible.	
	gtk_widget_show_all(window);
	
	gtk_main();
	
	return 0;
}