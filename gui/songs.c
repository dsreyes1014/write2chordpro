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
/*****************************************************************************/
GtkWidget *treeView,
          *tViewDisplay;
          
GtkTextBuffer *tBufferDisplay;

GtkListStore *listStore;

GtkTreeSelection *selection;

GtkTreeModel *model;

GtkTreeViewColumn *column;

GtkTextBuffer *tBufferDisplay;

GtkTreeIter iter;

gchar song[50],
      directory[75], 
      songPath[100], 
      displayBody[2000];
      
const gchar *titleDisplay;

extern GtkWidget *entryTitle, 
                 *entryArtist, 
                 *entryKey, 
                 *entryGenre,
				 *tViewEditor, 
				 *button5,
				 *window;
				 
extern GtkTextBuffer *tBufferEditor;
/*****************************************************************************/
void saveDialog(void)
{
	GtkWidget *messageWindow;
	
	gint run;
	
	messageWindow = gtk_message_dialog_new(NULL,
	                                       GTK_DIALOG_MODAL, 
	                                       GTK_MESSAGE_QUESTION,
	                                       GTK_BUTTONS_NONE,
	                                       "Do you want to save changes?"
	                                       );
	
	gtk_dialog_add_button(GTK_DIALOG(messageWindow), "No", 1);	
	
	gtk_dialog_add_button(GTK_DIALOG(messageWindow), "Yes", 2);
	
	run = gtk_dialog_run(GTK_DIALOG(messageWindow));
	
	if(run == 2)
	{
		save(messageWindow, NULL);	
		
		gtk_widget_destroy(messageWindow);
	}
	else 
	{                            
		gtk_widget_destroy(messageWindow);	                     
	}
}
/*****************************************************************************/
void createDir(void)
{
	gchar user[30];
	
	gchar *userVariable; 
	gchar *homeDir; 
	gchar *programDir; 
	
	userVariable = "USER";
	homeDir = "home";
	programDir = "W2C";
	
	// Checks environment's user variable. 
	sprintf(user, "%s", getenv(userVariable));
	
	// Prints out program directory for directory creation.
	sprintf(directory, "/%s/%s/%s/", homeDir, user, programDir);

	// Creates directory.
	mkdir(directory, S_IRWXU);
}
/*****************************************************************************/
void modifiedEntry(void)
{	
	display(tBufferDisplay, tViewDisplay);
}
/*****************************************************************************/
void modifiedBuffer(GtkTextBuffer *buffer, gpointer data)
{	
	display(tBufferDisplay, tViewDisplay);
}
/*****************************************************************************/
void activateRow(GtkTreeView *treeView, gpointer data)
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

	gint i, n,  line1, line2, line3, line4;
	
	gchar chars[2000];	
	
	n = 0;
	
	n = getLineCount(songPath);
		
	gchar text[n][COLUMN_N];
	
	getTextForEachLine(text, n);
		
	line1 = getLineCharCount(text, 0);
	line2 = getLineCharCount(text, 1);
	line3 = getLineCharCount(text, 2);
	line4 = getLineCharCount(text, 3);
	
	// Sets title entry.	
	setText(chars, songPath, 8);
	gtk_entry_set_text(GTK_ENTRY(entryTitle), chars);
	gtk_editable_set_editable(GTK_EDITABLE(entryTitle), FALSE);
	
	// Sets artist entry.	
	setText(chars, songPath, line1 + 11);
	gtk_entry_set_text(GTK_ENTRY(entryArtist), chars);
	gtk_editable_set_editable(GTK_EDITABLE(entryArtist), FALSE);
	
	// Sets genre entry.	
	setText(chars, songPath, line1 + line2 + 7);
	gtk_entry_set_text(GTK_ENTRY(entryGenre), chars);
	gtk_editable_set_editable(GTK_EDITABLE(entryGenre), FALSE);
	
	// Sets key entry.	
	setText(chars, songPath, line1 + line2 + line3 + 6);
	gtk_entry_set_text(GTK_ENTRY(entryKey), chars);
	gtk_editable_set_editable(GTK_EDITABLE(entryKey), FALSE);
	
	
	i = getChars(chars, songPath, line1 + line2 + line3 + line4 + 1);
	gtk_text_buffer_set_text(GTK_TEXT_BUFFER(tBufferEditor), chars, i);
	gtk_text_view_set_editable(GTK_TEXT_VIEW(tViewEditor), FALSE);
	
	g_print("Variable i: %d\n", i);
	
	display(tBufferDisplay, tViewDisplay);
	
	gtk_text_buffer_set_modified(tBufferEditor, FALSE);	
	
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(button5), FALSE);
}
/*****************************************************************************/
void songSelect(GtkTreeSelection *selection, gpointer data)
{
	//GtkTreeIter iter;	
	
	gchar *getSong;	
		                                           	
	if(gtk_tree_selection_get_selected(selection, &model, &iter))
	{		
		gtk_tree_model_get(GTK_TREE_MODEL(listStore), &iter, 0, 
					       &getSong, -1);	
					       
		sprintf(song, "%s.chordpro", getSong);
		sprintf(songPath, "%s%s", directory, song);		
		
		g_free(getSong);		                                               
	}
}
/*****************************************************************************/
void listFiles(void)
{		
	DIR *pdir;
	
	struct dirent *pentry;
	
	createDir();
	
	pdir = opendir(directory);
	
	if(pdir == NULL)
	{
		printf("\nERROR!");	
	}

	while((pentry = readdir(pdir)) != NULL)
	{		
		gchar *files = pentry -> d_name;
		gint length;
		
		length = strlen(files);
		
		files[length - 9] = '\0';
		
		if(length >= 3)
		{						
			gtk_list_store_insert_with_values(GTK_LIST_STORE(listStore), 
											  &iter, -1, 0, files, -1);		
			//g_print("%s\n", files);
		}
		else 
		{
			//g_print("%s\n", files);		
		}	
	}

	closedir(pdir);
}
/*****************************************************************************/
void songList(void)
{
	GtkCellRenderer *cell;
		
	listStore = gtk_list_store_new(1, G_TYPE_STRING);		
	treeView = gtk_tree_view_new_with_model(GTK_TREE_MODEL(listStore));
	
	tViewDisplay = gtk_text_view_new();
	tBufferDisplay = gtk_text_view_get_buffer(GTK_TEXT_VIEW(tViewDisplay));
		
	g_object_unref(listStore);	
				
	cell = gtk_cell_renderer_text_new();	
	column = gtk_tree_view_column_new_with_attributes("Songs", cell, "text", NULL);
	selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(treeView));
	model = gtk_tree_view_get_model(GTK_TREE_VIEW(treeView));	
	
	gtk_tree_view_column_set_sort_column_id(GTK_TREE_VIEW_COLUMN(column), 0);	
	
	gtk_tree_view_column_set_sort_order(GTK_TREE_VIEW_COLUMN(column), GTK_SORT_ASCENDING);
	
	gtk_tree_selection_set_mode(selection, GTK_SELECTION_BROWSE);
		
	listFiles();	
	
	/* Add column to treeView1 */	
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeView), column);
	
	gtk_tree_view_column_clicked(column);
	
	g_signal_connect(selection, "changed", G_CALLBACK(songSelect), NULL);
	g_signal_connect(treeView, "row-activated", G_CALLBACK(activateRow), NULL);
}