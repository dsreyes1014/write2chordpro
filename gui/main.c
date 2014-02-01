// Author: Andrew Reyes.
// Date Modified: 01/14/2014. 

#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>

#include "menu.h"
#include "chords.h"
#include "songs.h"
#include "editor.h"
#include "display.h"

/*********** Global Variables ************************************************/
GtkWidget *window;

GtkTreeSelection *selection;

GtkTreeViewColumn *column;

gchar *filename;

extern GtkWidget *menu_bar,
                 *button_5,                 
                 *tree_view, 
                 *entry_title,                
                 *t_view_display;
                 
extern GtkTextBuffer *t_buffer_editor;     

/******* 'tab_drag_drop' Function *********************************************/
gboolean 
tab_drag_drop(GtkWidget *widget, 
              GdkDragContext *context,
              gint x,
              gint y,
              guint time,
              gpointer data)
{
	
}                   
/******* 'tab_drag_begin' Function *********************************************/
void tab_drag_begin(GtkWidget *widget, GdkDragContext *context, gpointer data)
{
	GtkWidget *box,
	          *window,
	          *notebook;
	
	const gchar *group_name;	
	
	box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 2);		          
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	notebook = gtk_notebook_new();
	
	gtk_notebook_set_group_name(GTK_NOTEBOOK(notebook), "display_tab");	
	
	group_name = gtk_notebook_get_group_name(GTK_NOTEBOOK(notebook));	
	
	g_print("%s\n", group_name);	
	
	gtk_container_add(GTK_CONTAINER(box), notebook);
	gtk_container_add(GTK_CONTAINER(window), box);
	
	gtk_widget_set_size_request(window, 320, 320);	
	
	g_signal_connect(notebook, "drag-drop", G_CALLBACK(tab_drag_drop), NULL);	
	
	gtk_widget_show_all(window);
}         
/******* 'close_window' Function *********************************************/

void close_window(GtkWidget *widget, gpointer data) 
{
	GtkEntryBuffer *buffer;	
	
	gint title;
	
	gboolean check_1,
	         check_2;	
	         
	buffer = gtk_entry_get_buffer(GTK_ENTRY(entry_title));	
	check_1 = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(button_5));
	check_2 = gtk_text_buffer_get_modified(t_buffer_editor);
	title = gtk_entry_buffer_get_length(buffer);
	
	if((check_1 == TRUE) && (title != 0) && (check_2 == TRUE))
	{
		save_dialog();	
	}

	gtk_main_quit();
}

/****** 'main' function ******************************************************/

int main(int argc, char *argv[])
{
	GtkWidget *grid,
	          *box_1,
	          *box_2,
	          *paned,
	          *frame_1, 
	          *frame_2,
	          *notebook,	         
	          *tab_label,
	          *scrolled_window_1,
	          *scrolled_window_2;		
	     
	const gchar *group_name;         
	
	gtk_init(&argc, &argv);
	
	grid = gtk_grid_new();
	notebook = gtk_notebook_new();
	frame_1 = gtk_frame_new(NULL);
	frame_2 = gtk_frame_new("Song");
	box_1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 2);
	box_2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
	paned = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);	
	scrolled_window_1 = gtk_scrolled_window_new(NULL, NULL);
    scrolled_window_2 = gtk_scrolled_window_new(NULL, NULL);
   
	// This creates toplevel 'window' widget titled 'Write 2 Chordpro'.
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "Write 2 Chordpro");
	
	menu_function();

	// Packs 'menuBar' and 'paned' widgets in 'box1' widget.
	gtk_box_pack_start(GTK_BOX(box_1), menu_bar, FALSE, FALSE, 1);
	gtk_box_pack_end(GTK_BOX(box_1), paned, TRUE, TRUE, 1);	
	
	song_list();	
	
	// Properties for 'frame_1 & frame_2' widgets.	
	gtk_frame_set_shadow_type(GTK_FRAME(frame_1), GTK_SHADOW_ETCHED_IN);
	gtk_frame_set_shadow_type(GTK_FRAME(frame_2), GTK_SHADOW_ETCHED_IN);
	
	// Packs 'tree_view' widget into 'scrolled_window' widget
	// and 'scrolled_window' widget  into 'frame' widget.
	gtk_container_add(GTK_CONTAINER(scrolled_window_1), tree_view);	
	gtk_container_add(GTK_CONTAINER(frame_1), scrolled_window_1);	
	
	editor(grid, window);		
	
	gtk_container_add(GTK_CONTAINER(scrolled_window_2), t_view_display);
	gtk_box_pack_start(GTK_BOX(box_2), scrolled_window_2, TRUE, TRUE, 2);

//----- Creates tabs for 'notebook' widget and tab labels. --------------------
	
	tab_label = gtk_label_new("Display");
	gtk_notebook_insert_page(GTK_NOTEBOOK(notebook), box_2, tab_label, 0);
	tab_label = gtk_label_new("Song Editor");
	gtk_notebook_insert_page(GTK_NOTEBOOK(notebook), grid, tab_label, 1);	
	
	gtk_notebook_set_tab_detachable(GTK_NOTEBOOK(notebook), box_2, TRUE);	
	
	gtk_notebook_popup_enable(GTK_NOTEBOOK(notebook));
	
	gtk_notebook_set_group_name(GTK_NOTEBOOK(notebook), "display_tab");	
	
	group_name = gtk_notebook_get_group_name(GTK_NOTEBOOK(notebook));
	
	g_signal_connect(notebook, "drag-begin", G_CALLBACK(tab_drag_begin), NULL);
	
	g_print("%s\n", group_name);

//-----------------------------------------------------------------------------
	                 			
	//-- Packs 'frame' & 'notebook' widgets inside pane 1 & 2 respectively. ---
	 
	gtk_paned_pack1(GTK_PANED(paned), frame_1, TRUE, FALSE);
	gtk_paned_pack2(GTK_PANED(paned), notebook, TRUE, FALSE);
	
	// Sizes both 'frame' and 'notebook' widgets. 
	gtk_widget_set_size_request(frame_1, 210, 125);
	gtk_widget_set_size_request(notebook, 200, 350);
	//gtk_widget_set_size_request(window, 750, 800);
	
	// This signal terminates main window when the close button is clicked.	
	g_signal_connect(window, "destroy", G_CALLBACK(close_window), NULL);
	
	// Adds the 'paned' widget contained in 'box1' widget to toplevel 'window' widget.	
	gtk_container_add(GTK_CONTAINER(window), box_1);
	
	// Make toplevel 'window' widget and it's child widgets visible.	
	gtk_widget_show_all(window);
	
	gtk_main();
	
	return 0;
}