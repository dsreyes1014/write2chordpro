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
	GtkTextIter start;
	gchar *getSong;
	gchar song[50], line1[100], line2[100], title[50], artist[50], songPath[100];
	gint firstLine, secondLine, titleL, artistL, lines, line, n;
	
	gtk_text_buffer_get_start_iter(GTK_TEXT_BUFFER(buffer), &start);	
	
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
			fgets(line1, 100, fp);  // Grabs first line of file and puts it in 'line1'.
			
			firstLine = strlen(line1);	// Counts number of characters for 'firstLine'.		
			
			fseek(fp, 8, SEEK_SET);  // Sets position in file relative to beginning of file.
			
			fgets(title, 50, fp);   // Reads line in file at set position.
			
			titleL = strlen(title);  // Counts number of characters for 'titleL'.
			
			title[titleL - 2] = '\0';
			
			fseek(fp, firstLine + 11 , SEEK_SET);			
			
			fgets(artist, 50, fp);   
					
			artistL = strlen(artist);
			
			artist[artistL -2] = '\0';
			
			fseek(fp, firstLine + 1, SEEK_SET);
			
			fgets(line2, 100, fp);
			
			secondLine = strlen(line2);
			
			fseek(fp, firstLine + secondLine + 2, SEEK_SET);				
			
			while((n = fgetc(fp)) != EOF)			
			{							
				if(n == '\n')
				{
					lines++;		
				}						
				//g_print("%d\n", lines);
			}
		
			//gchar text[lines][50];		
		
			//fseek(fp, firstLine + secondLine + 2, SEEK_SET);					
			
			/*for(line = 0; line <= lines; line++)
			{						
				fgets(&text[line], 50, fp);	
				
				//gtk_text_buffer_set_text(GTK_TEXT_BUFFER(buffer), text[line], -1);
			}			
			for(line = 0; line <= lines; line++)
			{
				g_print("Line %d: %s\n", line, text[line]);												
			}	*/
			
			line = 0;			
			
			gchar text[line], body;
			 			
			text[line] = '\0';			
			
			while((body = fgetc(fp)) != EOF)
			{
				text[line++] = body;
				
				g_print("%c", body);			
				
				gtk_text_buffer_set_text(GTK_TEXT_BUFFER(buffer), &body, -1);
			}
			
			//line = 0;
			
			//gtk_text_buffer_set_text(GTK_TEXT_BUFFER(buffer), *text, -1);
			
			//gtk_text_buffer_insert(GTK_TEXT_BUFFER(buffer), &start, *text[lines], -1);

			gtk_entry_set_text(GTK_ENTRY(entryTitle), title);	
			
			gtk_entry_set_text(GTK_ENTRY(entryArtist), artist);
			//g_print("%s\n", song);	
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