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

GtkWidget *treeView;
GtkListStore *listStore;
GtkTreeViewColumn *column;
GtkTreeSelection *selection;
GtkTreeModel *model;
gchar directory[75];
extern GtkWidget *entryTitle, *entryArtist;
extern GtkTextBuffer *buffer;

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

void songSelect(void)
{
	GtkTreeIter songIter;
	gchar *getSong;
	gchar ch;
	gchar textL1[100], textL2[100], title[100], artist[100], song[50], songPath[50], body[999];
	gint i, line1, line2, pos;
		
	FILE *fp;	
		
	if(gtk_tree_selection_get_selected(GTK_TREE_SELECTION(selection), &model, &songIter))
	{
		gtk_tree_view_set_activate_on_single_click(GTK_TREE_VIEW(treeView), FALSE);		
		gtk_tree_model_get(GTK_TREE_MODEL(listStore), &songIter, 0, &getSong, -1);	
		
		sprintf(song, "%s.chordpro", getSong);
		sprintf(songPath, "%s%s", directory, song);		

		if((fp = fopen(songPath, "r")) == NULL)
		{
			g_print("Error");
		}
		else
		{
			i = 0;
			
			pos = ftell(fp);
			
			g_print("Position in file before setting it for firstline read: %d\n", pos);
			
			fseek(fp, 0, SEEK_SET);			
			
			pos = ftell(fp);
			
			g_print("Position in file after setting it for firstline read: %d\n", pos);
			
			while((ch = fgetc(fp)) != '\n')
			{
				textL1[i++] = ch;			
			}
				
			line1 = strlen(textL1) + 1;
			
			fclose(fp);
		}
	
		if((fp = fopen(songPath, "r")) == NULL)
		{
			g_print("Error");
		}
		else
		{
			i = 0;
			
			pos = ftell(fp);
			
			g_print("Position in file before setting it for secondline read: %d\n", pos);

			fseek(fp, line1, SEEK_SET);		
			
			pos = ftell(fp);
			
			g_print("Position in file after setting it for secondline read: %d\n", pos);
						
			while((ch = fgetc(fp)) != '\n')
			{
				textL2[i++] = ch;			
			}
						
			line2 = strlen(textL2) + 1;
			
			fclose(fp);
		}		
				
		if((fp = fopen(songPath, "r")) == NULL)
		{
			g_print("Error");
		}
		else
		{		
			i = 0;
			
			pos = ftell(fp);
			
			g_print("Position in file before setting it for title read: %d\n", pos);
							
			// Postion in file where we grab title for visibility.
			fseek(fp, 8, SEEK_SET);			
			
			pos = ftell(fp);
			
			g_print("Position in file after setting it for title read: %d\n", pos);			
			
			// Grab characters 'til we reach the '\n' character
			// and place it in 'title'.
			while((ch = fgetc(fp)) != '\n')
			{
				title[i++] = ch;			
			}
		
			// Manually set null terminator.
			title[strlen(title) -1] = '\0';
			
			// Place 'title' in entry widget for title.
			gtk_entry_set_text(GTK_ENTRY(entryTitle), title);
		
			fclose(fp);
		}
		
		if((fp = fopen(songPath, "r")) == NULL)
		{
			g_print("Error");
		}
		else
		{
		
			i = 0;		
			
			pos = ftell(fp);
			
			g_print("Position in file before setting it for artist read: %d\n", pos);
			
			// Position in file where artist is set.
			fseek(fp, (line1 -1) + 11, SEEK_SET);
			
			pos = ftell(fp);
			
			g_print("Position in file after setting it for artist read: %d\n", pos);			
			
			// Grab characters 'til we reach the '\n' character
			// and place it in 'artist'.
			while((ch = fgetc(fp)) != '\n')
			{
				artist[i++] = ch;
			}
		
			// Manually set null terminator.		
			artist[strlen(artist) -1] = '\0';
		
			// Place 'artist' in entry widget for artist.
			gtk_entry_set_text(GTK_ENTRY(entryArtist), artist);	
		
			fclose(fp);
		}
		
		if((fp = fopen(songPath, "r")) == NULL)
		{
			g_print("Error");
		}
		else
		{		
			i = 0;
			
			pos = ftell(fp);
			
			g_print("Position in file before setting it for body read: %d\n", pos);
			
			fseek(fp, line1 + line2 + 1, SEEK_SET);
			
			pos = ftell(fp);
			
			g_print("Position in file after setting it for body read: %d\n", pos);			
			
			while((ch = fgetc(fp)) != EOF)
			{
				body[i++] = ch;			
			}
		
			body[strlen(body)] = '\0';
		
			gtk_text_buffer_set_text(GTK_TEXT_BUFFER(buffer), body, -1);					

			g_print("Count of first line: %d\n", line1);
			
			g_print("Count of second line: %d\n", line2);			
			
			g_print("Count of first and second line: %d\n", line1+line2);
			
			g_print("String: %s\n", body);
			
			fclose(fp);		
		}
	}
}

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
			gtk_list_store_insert_with_values(GTK_LIST_STORE(listStore), &iter, -1, 0, files, -1);		
		
			gtk_tree_view_column_set_sort_column_id(GTK_TREE_VIEW_COLUMN(column), 0);	
			gtk_tree_view_column_set_sort_indicator(GTK_TREE_VIEW_COLUMN(column), TRUE);
			gtk_tree_view_column_set_sort_order(GTK_TREE_VIEW_COLUMN(column), GTK_SORT_ASCENDING);
			
			g_print("%s\n", files);
		}
		else 
		{
			g_print("%s\n", files);		
		}	
		
		g_signal_connect(selection, "changed", G_CALLBACK(songSelect), NULL);
	}

	closedir(pdir);
}

void songList(void)
{
	GtkCellRenderer *cell;
	
	listStore = gtk_list_store_new(1, G_TYPE_STRING);	
	treeView = gtk_tree_view_new_with_model(GTK_TREE_MODEL(listStore));		
	cell = gtk_cell_renderer_text_new();	
	column = gtk_tree_view_column_new_with_attributes("Songs", cell, "text", NULL);
	selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(treeView));
	model = gtk_tree_view_get_model(GTK_TREE_VIEW(treeView));	
	
	gtk_tree_view_column_set_sort_column_id(GTK_TREE_VIEW_COLUMN(column), 0);	
	gtk_tree_view_column_set_sort_indicator(GTK_TREE_VIEW_COLUMN(column), TRUE);
	gtk_tree_view_column_set_sort_order(GTK_TREE_VIEW_COLUMN(column), GTK_SORT_ASCENDING);
		
	listFiles();	
	
	/* Add column to treeView1 */	
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeView), column);
}