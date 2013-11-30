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
gchar directory[75], song[50], songPath[100];
extern GtkWidget *entryTitle, *entryArtist, *tViewEditor;
extern GtkTextBuffer *tBufferEditor;

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
	gchar title[50], artist[50], body[999];
	gint i, line1, line2, pos, lineCount;
		
	
	FILE *fp;	
		
	if(gtk_tree_selection_get_selected(GTK_TREE_SELECTION(selection), &model, &songIter))
	{		
		gtk_tree_model_get(GTK_TREE_MODEL(listStore), &songIter, 0, &getSong, -1);	
		
		sprintf(song, "%s.chordpro", getSong);
		sprintf(songPath, "%s%s", directory, song);		

		if((fp = fopen(songPath, "r")) == NULL)				//  
		{																   // 
			g_print("Error");											//	
		}                                                  // 
		else																// This if/else
		{																	// statement will count how
			lineCount = 0;												// many lines
																			// are in the file.
			while((ch = fgetc(fp)) != EOF)						// 
			{																//
				if(ch == '\n')											//
				{															//
					lineCount++;										//
				}															//
			}																//
		
			g_print("Line count is: %d\n", lineCount);
		
			fclose(fp);		
		}	
	
		gchar lines[lineCount][100];	
		
		
		
		if((fp = fopen(songPath, "r")) == NULL)            //
		{																	//
			g_print("Error");											// This if/else 
		}																	// statement will 
		else																// read each line
		{																	//	for future 
			for(i = 0; i < lineCount; i++)						// text manipulation.
			{																//
				fgets(lines[i], 100, fp);							//
			}																
																			
			fclose(fp);													
		}			
		
		line1 = strlen(lines[0]);
		line2 = strlen(lines[1]);
		
		g_print("Count of first line: %d\n", line1);			// This section
																			// is for debugging
		g_print("Count of second line: %d\n", line2);		// purposes only.
																			//
		g_print("All of line1: %s\n", lines[0]);				//
																			//
		g_print("All of line1: %s\n", lines[1]);				//												
		
		if((fp = fopen(songPath, "r")) == NULL)						
		{																			
			g_print("Error");													//
		}																			//
		else																		// This if/else
		{																			// statement sets 
			if(strlen(lines[0]) != 0)										// the title and 
			{																		// enters it into
				fseek(fp, 8, SEEK_SET);										// the GtkEntry
																					// widget.
				fgets(title, 50, fp);										//
																					//
				title[strlen(title) -2] = '\0';							
																					
				gtk_entry_set_text(GTK_ENTRY(entryTitle), title);	
																					
				gtk_editable_set_editable(GTK_EDITABLE(entryTitle), FALSE);				
								
				fclose(fp);													
			}	
		}
															
		if((fp = fopen(songPath, "r")) == NULL)
		{
			g_print("Error");
		}
		else
		{
			if(strlen(lines[1]) != 0)
			{					
				fseek(fp, strlen(lines[0]) + 11, SEEK_SET);
				
				fgets(artist, 50, fp);					
				
				artist[strlen(artist) -2] = '\0';
				
				gtk_entry_set_text(GTK_ENTRY(entryArtist), artist);
				
				gtk_editable_set_editable(GTK_EDITABLE(entryArtist), FALSE);
				
				fclose(fp);		
			}	
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
		
			gtk_text_buffer_set_text(GTK_TEXT_BUFFER(tBufferEditor), body, -1);		
			
			gtk_text_view_set_editable(GTK_TEXT_VIEW(tViewEditor), FALSE);					
			
			g_print("Body:\n%s\n", body);
			
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