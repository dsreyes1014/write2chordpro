// Author: Andrew Reyes
// Date Last Modified: 11-26-2013

#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

#include "songs.h"
#include "editor.h"
#include "display.h"

/********* Global Variables **************************************************/

GtkTreeModel *model;

GtkWidget *tree_view,
          *t_view_display;
          
GtkTreePath *tree_path;

GtkListStore *list_store;

GtkTreeViewColumn *column;

GtkTreeSelection *selection;

GtkTextBuffer *t_buffer_display;

gchar song[50],
      directory[75], 
      song_path[100], 
      display_body[2000];
      
const gchar *title_display;

extern GtkWidget *entry_title, 
                 *entry_artist, 
                 *entry_key, 
                 *entry_genre,
				 *t_view_editor, 
				 *button_5,
				 *window;
				 
extern GtkTextBuffer *t_buffer_editor;

/****** 'append_to_list' Function ********************************************/

void append_to_list(gchar *value)
{
	GtkTreePath *path;	
	
	gboolean check;
	
	GtkTreeIter iter;
	
	gchar *path_string;	
	
	check = gtk_tree_selection_get_selected(selection, &model, &iter);	
	
	if(check == TRUE)
	{
		path = gtk_tree_model_get_path(GTK_TREE_MODEL(list_store), &iter);		
		
		path_string = gtk_tree_path_to_string(path);	
		
		gtk_list_store_clear(list_store);
		
		list_files();
		
		path = gtk_tree_path_new_from_string(path_string);
		
		gtk_tree_selection_select_path(selection, path);
	                                
		activate_row(tree_view, NULL);	                                		
	}
	else 
	{
		gtk_list_store_append(list_store, &iter);
		
		gtk_list_store_set(list_store, &iter, 0, value, -1);
		
		gtk_tree_view_column_clicked(column);
		gtk_tree_view_column_clicked(column);
		
		path = gtk_tree_model_get_path(GTK_TREE_MODEL(list_store), &iter);
		
		path_string = gtk_tree_path_to_string(path);
		
		gtk_list_store_clear(list_store);
		
		list_files();
		
		path = gtk_tree_path_new_from_string(path_string);
		
		gtk_tree_selection_select_path(selection, path);
	                                
		activate_row(tree_view, NULL);	                                			
	}
}

/********** 'save_dialog' Function *******************************************/

void save_dialog(void)
{	
	GtkWidget *message_window;
	
	gint run;
	
	message_window = gtk_message_dialog_new(NULL,
	                                       GTK_DIALOG_MODAL, 
	                                       GTK_MESSAGE_QUESTION,
	                                       GTK_BUTTONS_NONE,
	                                       "Do you want to save changes?"
	                                       );
	
	gtk_dialog_add_button(GTK_DIALOG(message_window), "No", 1);	
	
	gtk_dialog_add_button(GTK_DIALOG(message_window), "Yes", 2);
	
	run = gtk_dialog_run(GTK_DIALOG(message_window));
	
	if(run == 2)
	{
		save(message_window, NULL);	
		
		gtk_widget_destroy(message_window);
	}
	else 
	{                            
		gtk_widget_destroy(message_window);	                     
	}
}

/****** 'create_dir' Function ************************************************/

void create_dir(void)
{
	gchar user[30],
	      *home_dir,
	      *program_dir,
	      *user_variable; 
	 
	 
	
	user_variable = "USER";
	home_dir = "home";
	program_dir = "W2C";
	
	// Checks environment's user variable. 
	sprintf(user, "%s", getenv(user_variable));
	
	// Prints out program directory for directory creation.
	sprintf(directory, "/%s/%s/%s/", home_dir, user, program_dir);

	// Creates directory.
	mkdir(directory, S_IRWXU);
}

/******** 'activate_row' Function ********************************************/

void activate_row(GtkWidget *widget, gpointer data)
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

	gint i, 
	     n,  
	     line_1, 
	     line_2, 
	     line_3, 
	     line_4;
	
	gchar chars[2000];	
	
	n = 0;
	
	n = get_line_count(song_path);
		
	gchar text[n][COLUMN_N];
	
	get_text_for_each_line(text, n);
		
	line_1 = get_line_char_count(text, 0);
	line_2 = get_line_char_count(text, 1);
	line_3 = get_line_char_count(text, 2);
	line_4 = get_line_char_count(text, 3);
	
	// Sets title entry.	
	set_text(chars, song_path, 8);
	gtk_entry_set_text(GTK_ENTRY(entry_title), chars);
	gtk_editable_set_editable(GTK_EDITABLE(entry_title), FALSE);
	
	// Sets artist entry.	
	set_text(chars, song_path, line_1 + 11);
	gtk_entry_set_text(GTK_ENTRY(entry_artist), chars);
	gtk_editable_set_editable(GTK_EDITABLE(entry_artist), FALSE);
	
	// Sets genre entry.	
	set_text(chars, song_path, line_1 + line_2 + 7);
	gtk_entry_set_text(GTK_ENTRY(entry_genre), chars);
	gtk_editable_set_editable(GTK_EDITABLE(entry_genre), FALSE);
	
	// Sets key entry.	
	set_text(chars, song_path, line_1 + line_2 + line_3 + 6);
	gtk_entry_set_text(GTK_ENTRY(entry_key), chars);
	gtk_editable_set_editable(GTK_EDITABLE(entry_key), FALSE);
	
	// Sets body.
	i = get_chars(chars, song_path, line_1 + line_2 + line_3 + line_4 + 1);
	gtk_text_buffer_set_text(GTK_TEXT_BUFFER(t_buffer_editor), chars, i);
	gtk_text_view_set_editable(GTK_TEXT_VIEW(t_view_editor), FALSE);
	
	g_print("Variable i: %d\n", i);
	
	display(t_buffer_display, t_view_display);
	
	gtk_text_buffer_set_modified(t_buffer_editor, FALSE);	
	
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(button_5), FALSE);
}

/******* 'song_select' Function **********************************************/

void song_select(GtkTreeSelection *tree_selection, gpointer data)
{	
	GtkTreeIter iter;	
	
	gchar *get_song;
	
	gboolean check;
	
	check = gtk_tree_selection_get_selected(tree_selection, &model, &iter);
		                                           	
	if(check == TRUE)
	{		
		gtk_tree_model_get(GTK_TREE_MODEL(list_store), &iter, 0, 
					       &get_song, -1);	
					       
		sprintf(song, "%s.chordpro", get_song);
		sprintf(song_path, "%s%s", directory, song);		
		
		g_free(get_song);			                                               
	}
}

/******** 'list_files' Function **********************************************/

void list_files(void)
{		
	DIR *p_dir;
	
	struct dirent *p_entry;
	
	create_dir();
	
	p_dir = opendir(directory);
	
	if(p_dir == NULL)
	{
		printf("\nERROR!");	
	}

	while((p_entry = readdir(p_dir)) != NULL)
	{		
		gchar *files = p_entry -> d_name;
		
		GtkTreeIter iter;
		
		gint length;
		
		length = strlen(files);
		
		files[length - 9] = '\0';
		
		if(length >= 3)
		{						
			gtk_list_store_insert_with_values(GTK_LIST_STORE(list_store), 
											  &iter, -1, 0, files, -1);		
		}	
	}

	closedir(p_dir);
}

/******* 'song_list' Function ************************************************/

void song_list(void)
{
	GtkCellRenderer *cell;
		
	list_store = gtk_list_store_new(1, G_TYPE_STRING);		
	tree_view = gtk_tree_view_new_with_model(GTK_TREE_MODEL(list_store));
	
	t_view_display = gtk_text_view_new();
	t_buffer_display = gtk_text_view_get_buffer(GTK_TEXT_VIEW(t_view_display));
		
	g_object_unref(list_store);	
				
	cell = gtk_cell_renderer_text_new();	
	column = gtk_tree_view_column_new_with_attributes("Songs", cell, "text", NULL);
	selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(tree_view));
	model = gtk_tree_view_get_model(GTK_TREE_VIEW(tree_view));	
	
	gtk_tree_view_column_set_sort_column_id(GTK_TREE_VIEW_COLUMN(column), 0);	
	
	gtk_tree_view_column_set_sort_order(GTK_TREE_VIEW_COLUMN(column), GTK_SORT_ASCENDING);
	
	gtk_tree_selection_set_mode(selection, GTK_SELECTION_BROWSE);
		
	list_files();	
	
	/* Add column to tree_view */	
	gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column);
	
	gtk_tree_view_column_clicked(column);
	
	g_signal_connect(selection, "changed", G_CALLBACK(song_select), NULL);
	g_signal_connect(tree_view, "row-activated", G_CALLBACK(activate_row), NULL);
}