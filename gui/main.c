// Author: Andrew Reyes.
// Date Modified: 11-26-2013. 

#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>

#include "menu.h"
#include "chords.h"
#include "songs.h"
#include "editor.h"
#include "display.h"

GtkWidget *window;

GtkTreeSelection *selection;

GtkTreeViewColumn *column;

gchar *filename;

extern GtkWidget *menuBar,
                 *button5,                 
                 *treeView, 
                 *entryTitle,                
                 *tViewDisplay;
                 
extern GtkTextBuffer *tBufferEditor;                
/*****************************************************************************/
void closeWindow(GtkWidget *widget, gpointer data) 
{
	GtkEntryBuffer *buffer;	
	
	gint title;
	
	gboolean check1,
	         check2;	
	         
	buffer = gtk_entry_get_buffer(GTK_ENTRY(entryTitle));	
	check1 = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(button5));
	check2 = gtk_text_buffer_get_modified(tBufferEditor);
	title = gtk_entry_buffer_get_length(buffer);
	
	if((check1 == TRUE) && (title != 0) && (check2 == TRUE))
	{
		saveDialog();	
	}

	gtk_main_quit();
}
/*****************************************************************************/
int main(int argc, char *argv[])
{
	GtkWidget *grid,
	          *box1,
	          *box2,
	          *paned,
	          *frame1, 
	          *frame2,
	          *notebook,
	          *tabLabel,
	          *scrolledWindow1,
	          *scrolledWindow2;	
	
	gtk_init(&argc, &argv);
	
	grid = gtk_grid_new();	
	notebook = gtk_notebook_new();
	frame1 = gtk_frame_new(NULL);
	frame2 = gtk_frame_new("Song");
	box1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 2);
	box2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
	paned = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);	
	scrolledWindow1 = gtk_scrolled_window_new(NULL, NULL);
    scrolledWindow2 = gtk_scrolled_window_new(NULL, NULL);
    
    
   
	// This creates toplevel 'window' widget titled "Write 2 Chordpro".
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "Write 2 Chordpro");
	
	menuFunction();

	// Packs 'menuBar' and 'paned' widgets in 'box1' widget.
	gtk_box_pack_start(GTK_BOX(box1), menuBar, FALSE, FALSE, 1);
	gtk_box_pack_end(GTK_BOX(box1), paned, TRUE, TRUE, 1);	
	
	songList();	
	
	// Properties for 'frame1 & frame2' widgets.	
	gtk_frame_set_shadow_type(GTK_FRAME(frame1), GTK_SHADOW_ETCHED_IN);
	gtk_frame_set_shadow_type(GTK_FRAME(frame2), GTK_SHADOW_ETCHED_IN);
	
	// Packs 'treeView' widget into 'scrolledWindow' widget
	// and 'scrolledWindow' widget  into 'frame' widget.
	gtk_container_add(GTK_CONTAINER(scrolledWindow1), treeView);	
	gtk_container_add(GTK_CONTAINER(frame1), scrolledWindow1);	
	
	editor(grid, window);		
	
	gtk_container_add(GTK_CONTAINER(scrolledWindow2), tViewDisplay);
	gtk_box_pack_start(GTK_BOX(box2), scrolledWindow2, TRUE, TRUE, 2);

	// Creates tabs for 'notebook' widget.
	gtk_notebook_append_page(GTK_NOTEBOOK(notebook), box2, NULL);
	gtk_notebook_append_page(GTK_NOTEBOOK(notebook), grid, NULL);
	
	// Sets labels for 'notebook' widget tabs.	
	tabLabel = gtk_label_new("Display");	
	gtk_notebook_set_tab_label(GTK_NOTEBOOK(notebook), box2, tabLabel);	
	tabLabel = gtk_label_new("Song Editor");	
	gtk_notebook_set_tab_label(GTK_NOTEBOOK(notebook), grid, tabLabel);
	
	gtk_notebook_set_tab_detachable(GTK_NOTEBOOK(notebook), window, TRUE);
	
	// Packs 'frame' & 'notebook' widgets inside pane 1 & 2 respectively.
	gtk_paned_pack1(GTK_PANED(paned), frame1, TRUE, FALSE);
	gtk_paned_pack2(GTK_PANED(paned), notebook, TRUE, FALSE);
	
	// Sizes both 'frame' and 'notebook' widgets. 
	gtk_widget_set_size_request(frame1, 210, 125);
	gtk_widget_set_size_request(notebook, 200, 350);
	//gtk_widget_set_size_request(window, 750, 800);
	
	// This signal terminates main window when the close button is clicked.	
	g_signal_connect(window, "destroy", G_CALLBACK(closeWindow), NULL);
	
	// Adds the 'paned' widget contained in 'box1' widget to toplevel 'window' widget.	
	gtk_container_add(GTK_CONTAINER(window), box1);
	
	// Make toplevel 'window' widget and it's child widgets visible.	
	gtk_widget_show_all(window);
	
	gtk_main();
	
	return 0;
}