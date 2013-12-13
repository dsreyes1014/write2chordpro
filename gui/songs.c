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
//-----------------------------------------------------------------------------
GtkWidget *treeView;
GtkListStore *listStore;
//GtkTreeStore *treeStore;
GtkTreeViewColumn *column;
GtkTreeSelection *selection;
GtkTreeModel *model;
GtkWidget *tViewDisplay;
GtkTextBuffer *tBufferDisplay;
gchar directory[75], song[50], songPath[100], displayBody[999];
const gchar *titleDisplay;
extern GtkWidget *entryTitle, *entryArtist, *entryKey, *entryGenre,
				 *tViewEditor, *button5;
extern GtkTextBuffer *tBufferEditor;
extern GtkToolItem *toggleTB;
//-----------------------------------------------------------------------------
void createDir(void)
{
	char user[30];
	
	char *userVariable = "USER";
	char *homeDir = "home";
	char *programDir = "W2C";
	
	// Checks environment's user variable. 
	sprintf(user, "%s", getenv(userVariable));
	
	// Prints out program directory for directory creation.
	sprintf(directory, "/%s/%s/%s/", homeDir, user, programDir);

	// Creates directory.
	mkdir(directory, S_IRWXU);
}
/*---------------------------------------------------------------------------*/
void songSelect(GtkTreeSelection *selection, gpointer data)
{
	GtkTreeIter songIter;
	gchar *getSong;
	gchar ch;
	gchar chars[2000];
	gint i, n = 0,  line1, line2, line3, line4; 	
	
	FILE *fp;	
		
	if(gtk_tree_selection_get_selected(selection, &model, &songIter))
	{		
		gtk_tree_model_get(GTK_TREE_MODEL(listStore), &songIter, 0, 
					       &getSong, -1);	
			
		sprintf(song, "%s.chordpro", getSong);
		sprintf(songPath, "%s%s", directory, song);		
		
		g_free(getSong);
		
		n = getLineCount(songPath);
		//g_print("Line count is: %d\n", n);
		
		gchar text[n][COLUMN_N];
	
		getTextForEachLine(text, n);
		
		line1 = getLineCharCount(text, 0);
		line2 = getLineCharCount(text, 1);
		line3 = getLineCharCount(text, 2);
		line4 = getLineCharCount(text, 3);
		
		setTitle(chars, songPath, 0);
		gtk_entry_set_text(GTK_ENTRY(entryTitle), chars);
		setArtist(chars, songPath, line1 + 11);
		gtk_entry_set_text(GTK_ENTRY(entryArtist), chars);
		setGenre(chars, songPath, line1 + line2 + 7);
		gtk_entry_set_text(GTK_ENTRY(entryGenre), chars);
		setGenre(chars, songPath, line1 + line2 + line3 + 6);
		gtk_entry_set_text(GTK_ENTRY(entryKey), chars);
		i = setEditorView(chars, songPath, line1 + line2
				      + line3 + line4 + 1);
		gtk_text_buffer_set_text(GTK_TEXT_BUFFER(tBufferEditor), chars, i);
		
		g_print("Variable i: %d\n", i);
//-----------------------------------------------------------------------------
		// This grabs everything from file and 
		// puts it in notebook tab display.
		if((fp = fopen(songPath, "r")) == NULL)
		{
			g_print("Error");
		}
		else //if(gtk_toggle_tool_button_get_active(GTK_TOGGLE_TOOL_BUTTON(toggleTB)) == TRUE)
		{								
			i = 0;
						
			fseek(fp, 0, SEEK_SET);
			
			while((ch = fgetc(fp)) != EOF)
			{
				displayBody[i++] = ch;		
			}		
			
			display(tBufferDisplay, tViewDisplay, displayBody, i);			
			
		
			fclose(fp);		
		}
	
		gtk_tree_view_set_model(GTK_TREE_VIEW(treeView), NULL);
		listStore = gtk_list_store_new(1, G_TYPE_STRING);
		gtk_tree_view_set_model(GTK_TREE_VIEW(treeView), GTK_TREE_MODEL(listStore));
		g_object_unref(listStore);
		
		listFiles();
	}
}
/*---------------------------------------------------------------------------*/
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
		GtkTreeIter iter;		
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
		
		//g_signal_connect(selection, "changed", G_CALLBACK(songSelect), NULL);
	}

	closedir(pdir);
}
//-----------------------------------------------------------------------------
void songList(void)
{
	GtkCellRenderer *cell;
		
	listStore = gtk_list_store_new(1, G_TYPE_STRING);	
	treeView = gtk_tree_view_new_with_model(GTK_TREE_MODEL(listStore));
		
	g_object_unref(listStore);
		
	tViewDisplay = gtk_text_view_new();
	tBufferDisplay = gtk_text_view_get_buffer(GTK_TEXT_VIEW(tViewDisplay));
		
	cell = gtk_cell_renderer_text_new();	
	column = gtk_tree_view_column_new_with_attributes("Songs", cell, "text", NULL);
	selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(treeView));
	model = gtk_tree_view_get_model(GTK_TREE_VIEW(treeView));	
	
	//gtk_tree_view_column_set_sort_column_id(GTK_TREE_VIEW_COLUMN(column), 0);	
	gtk_tree_model_sort_new_with_model(GTK_TREE_MODEL(listStore));
	gtk_tree_view_column_set_sort_indicator(GTK_TREE_VIEW_COLUMN(column), TRUE);
	gtk_tree_view_column_set_sort_order(GTK_TREE_VIEW_COLUMN(column), GTK_SORT_ASCENDING);
		
	listFiles();	
	
	/* Add column to treeView1 */	
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeView), column);
	
	g_signal_connect(selection, "changed", G_CALLBACK(songSelect), NULL);
}