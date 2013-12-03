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

GtkWidget *treeView;
GtkListStore *listStore;
GtkTreeViewColumn *column;
GtkTreeSelection *selection;
GtkTreeModel *model;
gchar directory[75], song[50], songPath[100], displayBody[999];
const gchar *titleDisplay;
extern GtkWidget *entryTitle, *entryArtist, *tViewEditor, *tViewDisplay;
extern GtkTextBuffer *tBufferEditor, *tBufferDisplay;

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
	GtkTextIter startEditor, endEditor, startDisplay, endDisplay;
	gchar *getSong;
	gchar ch;
	gchar title[50], artist[50], body[999];
	gint i, line1, line2, pos, lineCount, lineDisplay;
		
	
	FILE *fp;	
		
	if(gtk_tree_selection_get_selected(GTK_TREE_SELECTION(selection), &model, &songIter))
	{		
		gtk_tree_model_get(GTK_TREE_MODEL(listStore), &songIter, 0, &getSong, -1);	
		
		gtk_text_buffer_get_start_iter(GTK_TEXT_BUFFER(tBufferEditor), &startEditor);
		gtk_text_buffer_get_end_iter(GTK_TEXT_BUFFER(tBufferEditor), &endEditor);
		
		gtk_text_buffer_delete(GTK_TEXT_BUFFER(tBufferEditor), &startEditor, &endEditor);
		
		gtk_text_buffer_get_start_iter(GTK_TEXT_BUFFER(tBufferDisplay), &startDisplay);
		gtk_text_buffer_get_end_iter(GTK_TEXT_BUFFER(tBufferDisplay), &endDisplay);
		
		gtk_text_buffer_delete(GTK_TEXT_BUFFER(tBufferDisplay), &startDisplay, &endDisplay);		
		
		sprintf(song, "%s.chordpro", getSong);
		sprintf(songPath, "%s%s", directory, song);		

		// This gets the line count for file.
		if((fp = fopen(songPath, "r")) == NULL)				
		{													 
			g_print("Error");									
		}                                                   
		else												
		{													
			lineCount = 0;									
															
			while((ch = fgetc(fp)) != EOF)					 
			{														
				if(ch == '\n')										
				{													
					lineCount++;									
				}													
			}														
					
			g_print("Line count is: %d\n", lineCount);
		
			fclose(fp);		
		}	
	
		gchar lines[lineCount][100];	
		
		
		// This will read each line for 
		// future text manipulation.
		if((fp = fopen(songPath, "r")) == NULL)            
		{														
			g_print("Error");									 
		}														 
		else													
		{														 
			for(i = 0; i < lineCount; i++)						
			{													
				fgets(lines[i], 100, fp);							
			}																	
																			
			fclose(fp);													
		}			
		
		line1 = strlen(lines[0]);
		line2 = strlen(lines[1]);
		
		g_print("Count of first line: %d\n", line1);			
																			
		g_print("Count of second line: %d\n", line2);		
																			
		g_print("All of line1: %s\n", lines[0]);				
																			
		g_print("All of line2: %s\n", lines[1]);															
		
		
		// This will get title and input into
		// entry.		
		if((fp = fopen(songPath, "r")) == NULL)						
		{																			
			g_print("Error");													
		}																		
		else																	
		{																		 
			if(strlen(lines[0]) != 0)										 
			{																
				fseek(fp, 8, SEEK_SET);										
																			
				fgets(title, 50, fp);										
																									
				title[strlen(title) -2] = '\0';							
																					
				gtk_entry_set_text(GTK_ENTRY(entryTitle), title);
																					
				gtk_editable_set_editable(GTK_EDITABLE(entryTitle), FALSE);				
								
				fclose(fp);													
			}	
		}
	
		// This will get artist and input into entry.													
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
		
		// This will get the rest of file after artist and 
		// put it in the song editor text view.				
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
		
			gtk_text_buffer_set_text(GTK_TEXT_BUFFER(tBufferEditor), body, i);		
			
			gtk_text_view_set_editable(GTK_TEXT_VIEW(tViewEditor), FALSE);					
			
			fclose(fp);		
		}
	
		// This grabs everything from file and 
		// puts it in notebook tab display.
		if((fp = fopen(songPath, "r")) == NULL)
		{
			g_print("Error");
		}
		else
		{								
			i = 0;
						
			fseek(fp, 0, SEEK_SET);
			
			while((ch = fgetc(fp)) != EOF)
			{
				displayBody[i++] = ch;		
			}
		
			gtk_text_buffer_set_text(GTK_TEXT_BUFFER(tBufferDisplay), displayBody, i);						
			
			fclose(fp);
			
			GtkTextTag *tag;
			GtkTextIter startOfLine, endOfLine, ch, matchStart, matchEnd;
			gchar *chord;		
			gboolean chordStart, chordEnd;
			
			// Sets these iters to a range on line 0 to delete and set desired visible text.
			gtk_text_buffer_get_iter_at_line(GTK_TEXT_BUFFER(tBufferDisplay), &startOfLine, 0);
			gtk_text_buffer_get_iter_at_line_offset(GTK_TEXT_BUFFER(tBufferDisplay), &ch, 0, 8);
			gtk_text_buffer_delete(GTK_TEXT_BUFFER(tBufferDisplay), &startOfLine, &ch);
			
			
			// Deletes last character of line 0 to output just the title. 
			gtk_text_buffer_get_iter_at_line(GTK_TEXT_BUFFER(tBufferDisplay), &endOfLine, 0);
			gtk_text_iter_forward_to_line_end(&endOfLine);
			gtk_text_buffer_backspace(GTK_TEXT_BUFFER(tBufferDisplay), &endOfLine, FALSE, TRUE);
			
			// Sets attributes for Title (line 0).			
			gtk_text_buffer_get_iter_at_line(GTK_TEXT_BUFFER(tBufferDisplay), &startOfLine, 0);
			gtk_text_buffer_get_iter_at_line(GTK_TEXT_BUFFER(tBufferDisplay), &endOfLine, 0);
			gtk_text_iter_forward_to_line_end(&endOfLine);			
			
			tag = gtk_text_buffer_create_tag(GTK_TEXT_BUFFER(tBufferDisplay), 
												  NULL, "weight", "850",
												  "justification", GTK_JUSTIFY_CENTER, 
												  "font", "30", NULL);
												  
			gtk_text_buffer_apply_tag(GTK_TEXT_BUFFER(tBufferDisplay), tag, &startOfLine, &endOfLine);
			
			// Sets these iters to a range on line 1 to delete and set desired visible text. 				
			gtk_text_buffer_get_iter_at_line(GTK_TEXT_BUFFER(tBufferDisplay), &startOfLine, 1);
			gtk_text_buffer_get_iter_at_line_offset(GTK_TEXT_BUFFER(tBufferDisplay), &ch, 1, 11);
			gtk_text_buffer_delete(GTK_TEXT_BUFFER(tBufferDisplay), &startOfLine, &ch);			
			
			// Deletes last character of line 1 to output just the artist.
			gtk_text_buffer_get_iter_at_line(GTK_TEXT_BUFFER(tBufferDisplay), &endOfLine, 1);
			gtk_text_iter_forward_to_line_end(&endOfLine);
			gtk_text_buffer_backspace(GTK_TEXT_BUFFER(tBufferDisplay), &endOfLine, FALSE, TRUE);	
			
		    // Inserts text before artist with attributes.
		    tag = gtk_text_buffer_create_tag(tBufferDisplay, NULL, "font", "12", 
		    								 "justification", GTK_JUSTIFY_CENTER, NULL);
			gtk_text_buffer_get_iter_at_line(tBufferDisplay, &startOfLine, 1);
			gtk_text_buffer_insert_with_tags(tBufferDisplay, &startOfLine, "by: ", 4, tag, NULL);
			
			// Sets attributes for Artist (line 1).
			gtk_text_buffer_get_iter_at_line_offset(GTK_TEXT_BUFFER(tBufferDisplay), &startOfLine, 1, 4);
			gtk_text_buffer_get_iter_at_line(GTK_TEXT_BUFFER(tBufferDisplay), &endOfLine, 1);
			gtk_text_iter_forward_to_line_end(&endOfLine);			
			tag = gtk_text_buffer_create_tag(GTK_TEXT_BUFFER(tBufferDisplay), 
												  NULL, "weight", "600",
												  "weight-set", TRUE, 
												  "font", "italic 18", NULL);
												  
			gtk_text_buffer_apply_tag(GTK_TEXT_BUFFER(tBufferDisplay), tag, &startOfLine, &endOfLine);	
			
			// This section is for setting the attributes of the text
			// 'Verse:', 'Chorus:'etc...			
			gtk_text_buffer_get_start_iter(tBufferDisplay, &startOfLine);		
			
			if(gtk_text_iter_forward_search(&startOfLine, "Verse:", 
											1, 
											&matchStart, &matchEnd, NULL))
			{
				tag = gtk_text_buffer_create_tag(tBufferDisplay, NULL, "font", "italic 12", NULL);
				gtk_text_buffer_apply_tag(tBufferDisplay, tag, &matchStart, &matchEnd);			
			}
				
			if(gtk_text_iter_forward_search(&startOfLine, "PreChorus:", 
											1, 
											&matchStart, &matchEnd, NULL))
			{
				tag = gtk_text_buffer_create_tag(tBufferDisplay, NULL, "font", "italic 12", NULL);
				gtk_text_buffer_apply_tag(tBufferDisplay, tag, &matchStart, &matchEnd);			
			}
		
			if(gtk_text_iter_forward_search(&matchEnd, "Chorus:", 
											1, 
											&matchStart, &matchEnd, NULL))
			{	
				tag = gtk_text_buffer_create_tag(tBufferDisplay, NULL, "font", "italic 12", NULL);
				gtk_text_buffer_apply_tag(tBufferDisplay, tag, &matchStart, &matchEnd);			
			}
			
			if(gtk_text_iter_forward_search(&startOfLine, "Intro:", 
											1, 
											&matchStart, &matchEnd, NULL))
			{
				tag = gtk_text_buffer_create_tag(tBufferDisplay, NULL, "font", "italic 12", NULL);
				gtk_text_buffer_apply_tag(tBufferDisplay, tag, &matchStart, &matchEnd);			
			}
		
			if(gtk_text_iter_forward_search(&startOfLine, "Bridge:", 
											1, 
											&matchStart, &matchEnd, NULL))
			{
				tag = gtk_text_buffer_create_tag(tBufferDisplay, NULL, "font", "italic 12", NULL);
				gtk_text_buffer_apply_tag(tBufferDisplay, tag, &matchStart, &matchEnd);			
			}
		
			if(gtk_text_iter_forward_search(&startOfLine, "Verse 1:", 
											1, 
											&matchStart, &matchEnd, NULL))
			{
				tag = gtk_text_buffer_create_tag(tBufferDisplay, NULL, "font", "italic 12", NULL);
				gtk_text_buffer_apply_tag(tBufferDisplay, tag, &matchStart, &matchEnd);			
			}
		
			if(gtk_text_iter_forward_search(&startOfLine, "Verse 3:", 
											1, 
											&matchStart, &matchEnd, NULL))
			{
				tag = gtk_text_buffer_create_tag(tBufferDisplay, NULL, "font", "italic 12", NULL);
				gtk_text_buffer_apply_tag(tBufferDisplay, tag, &matchStart, &matchEnd);			
			}						
			
			//g_print("Chord: %s\n", chord);
			//g_print("Number of \'[\': %d\n", i);
			
			lineDisplay = gtk_text_buffer_get_line_count(GTK_TEXT_BUFFER(tBufferDisplay));
			
			g_print("Line count for display is: %d\n", lineDisplay);					
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
	
	g_object_unref(listStore);	
		
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