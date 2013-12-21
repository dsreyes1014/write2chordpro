// Author: Andrew Reyes.
// Date Last Modified: 11-26-2013.

#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
#include <stdio.h>
#include <string.h>

#include "chords.h"
#include "songs.h"
#include "editor.h"
#include "transpose.h"
#include "display.h"

GtkWidget *entryTitle, *entryArtist, *entryKey, *entryGenre, 
		  *tViewEditor, *button5;
GtkEntryBuffer *entryBuffer;
GtkTextBuffer *tBufferEditor;
GtkToolItem *toggleTB;
const gchar *getTitle, *getArtist, *getKey, *getGenre;
extern char directory[];
extern GtkListStore *listStore;
extern GtkTreeSelection *selection;
extern GtkWidget *treeView;
extern gchar songPath[];
/*---------------------------------------------------------------------------*/
gint setTitle(gchar *text, gchar *filePath, gint lineNum)
{
	FILE *fp;
	
	if((fp = fopen(filePath, "r")) == NULL)
	{
		g_print("Error. No such file exists.\n");
		
		return -1;
	}
	else 
	{
		fseek(fp, 8, SEEK_SET);
		fgets(text, COLUMN_N, fp);
		
		text[strlen(text) -2] = '\0';	
		
		return 0;
	}
}
/*---------------------------------------------------------------------------*/
gint setArtist(gchar *text, gchar *filePath, gint pos)
{
	FILE *fp;
	
	if((fp = fopen(filePath, "r")) == NULL)
	{
		g_print("Error. No such file exists.\n");
		
		return -1;
	}
	else 
	{
		fseek(fp, pos, SEEK_SET);
		fgets(text, COLUMN_N, fp);
		
		text[strlen(text) -2] = '\0';	
		
		return 0;
	}
}
/*---------------------------------------------------------------------------*/
gint setGenre(gchar *text, gchar *filePath, gint pos)
{
	FILE *fp;
	
	if((fp = fopen(filePath, "r")) == NULL)
	{
		g_print("Error. No such file exists.\n");
		
		return -1;
	}
	else 
	{
		fseek(fp, pos, SEEK_SET);
		fgets(text, COLUMN_N, fp);
		
		text[strlen(text) -2] = '\0';	
		
		return 0;
	}
}
/*---------------------------------------------------------------------------*/
gint setKey(gchar *text, gchar *filePath, gint pos)
{
	FILE *fp;
	
	if((fp = fopen(filePath, "r")) == NULL)
	{
		g_print("Error. No such file exists.\n");
		
		return -1;
	}
	else 
	{
		fseek(fp, pos, SEEK_SET);
		fgets(text, COLUMN_N, fp);
		
		text[strlen(text) -2] = '\0';	
		
		return 0;
	}
}
/*---------------------------------------------------------------------------*/
// Grabs text starting from 'pos' to 'EOF' and outputs text to 'text'.
// Returns char count through to 'i'. 
gint getChars(gchar *text, gchar *filePath, gint pos)
{
	gint i;
	gchar ch;	
	FILE *fp;	
	
	if((fp = fopen(filePath, "r")) == NULL)
	{
		g_print("No such file or directory\n");
		
		return -1;
	}
	else 
	{		
		i = 0;		
		//pos = ftell(fp);
		
		//g_print("Position in file before setting it for body read: %d\n", pos);
		
		fseek(fp, pos, SEEK_SET);
			
		//pos = ftell(fp);
			
		//g_print("Position in file after setting it for body read: %d\n", pos);			
			
		while((ch = fgetc(fp)) != EOF)
		{
			text[i++] = ch;			
		}					
		
		fclose(fp);
		
		return i;
	}
}	
/*---------------------------------------------------------------------------*/
gint getLineCharCount(gchar line[][COLUMN_N], gint lineNum)
{
	gint charCount;
	
	charCount = strlen(line[lineNum]);
	
	return charCount;
}
/*---------------------------------------------------------------------------*/
gint getTextForEachLine(gchar lines[][COLUMN_N], gint lineNum)
{
	gint i;
	FILE *fp;	
	
	// This will read each line for 
	// future text manipulation.
	if((fp = fopen(songPath, "r")) == NULL)            
	{														
		g_print("Error\n");
		
		return -1;									 
	}														 
	else 													
	{														 
		for(i = 0; i < lineNum; i++)						
		{													
			fgets(lines[i], COLUMN_N, fp);							
		}
	
		fclose(fp);													
	}

	return 0;
}
/*---------------------------------------------------------------------------*/
gint getLineCount(gchar *filePath)
{
	gchar ch;	
	gint lineCount;	
	FILE *fp;
	
	if((fp = fopen(filePath, "r")) == NULL)				
	{													 
		g_print("Error\n");
		
		return -1;									
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
																	
		//g_print("Line count is: %d\n", lineCount);
		
		fclose(fp);		
	}

	return lineCount;
}
/*---------------------------------------------------------------------------*/
void save(GtkWidget *widget, gpointer data)
{	
	GtkTextIter start, end;	
	gchar *body;
	char newFile[25];
	
	FILE *fp;		
	
	gtk_text_buffer_get_start_iter(GTK_TEXT_BUFFER(tBufferEditor), &start);
	gtk_text_buffer_get_end_iter(GTK_TEXT_BUFFER(tBufferEditor), &end);	
	
	getTitle = gtk_entry_get_text(GTK_ENTRY(entryTitle));
	getArtist = gtk_entry_get_text(GTK_ENTRY(entryArtist));
	getGenre = gtk_entry_get_text(GTK_ENTRY(entryGenre));
	getKey = gtk_entry_get_text(GTK_ENTRY(entryKey));	
	body = gtk_text_buffer_get_text(GTK_TEXT_BUFFER(tBufferEditor), &start, &end, TRUE);
	
	sprintf(newFile, "%s%s.chordpro", directory, getTitle);
	
	fp = fopen(newFile, "w+");
		
	fprintf(fp, "{title: %s}\n", getTitle);
	fprintf(fp, "{subtitle: %s}\n", getArtist);
	fprintf(fp, "{tags: %s}\n", getGenre);
	fprintf(fp, "{key: %s}\n\n", getKey);
	fprintf(fp, "%s", body);
	
	fclose(fp);
	
	g_free(body);	
	
	//gtk_tree_view_set_model(GTK_TREE_VIEW(treeView), NULL);
	//listStore = gtk_list_store_new(1, G_TYPE_STRING);
	//gtk_tree_view_set_model(GTK_TREE_VIEW(treeView), GTK_TREE_MODEL(listStore));
	//g_object_unref(listStore);
	
	gtk_list_store_clear(listStore);
	
	listFiles();	
	
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(button5), FALSE);
}
/*---------------------------------------------------------------------------*/
void newSong(GtkWidget *widget, gpointer button)
{
	GtkTextIter start, end;	
	
	// Unselects all in 'songList' so it will not appear in song editor.	
	gtk_tree_selection_unselect_all(GTK_TREE_SELECTION(selection));	
	
	entryBuffer = gtk_entry_get_buffer(GTK_ENTRY(entryTitle));
	
	gtk_entry_buffer_delete_text(GTK_ENTRY_BUFFER(entryBuffer), 0, -1);

	entryBuffer = gtk_entry_get_buffer(GTK_ENTRY(entryArtist));
	
	gtk_entry_buffer_delete_text(GTK_ENTRY_BUFFER(entryBuffer), 0, -1);
	
	entryBuffer = gtk_entry_get_buffer(GTK_ENTRY(entryGenre));
	
	gtk_entry_buffer_delete_text(GTK_ENTRY_BUFFER(entryBuffer), 0, -1);
	
	entryBuffer = gtk_entry_get_buffer(GTK_ENTRY(entryKey));
	
	gtk_entry_buffer_delete_text(GTK_ENTRY_BUFFER(entryBuffer), 0, -1);
	
	gtk_text_buffer_get_start_iter(GTK_TEXT_BUFFER(tBufferEditor), &start);
	gtk_text_buffer_get_end_iter(GTK_TEXT_BUFFER(tBufferEditor), &end);
	
	gtk_text_buffer_delete(GTK_TEXT_BUFFER(tBufferEditor), &start, &end);
	
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(button), TRUE);	
}
/*---------------------------------------------------------------------------*/
void editSong(GtkToggleButton *button, gpointer data)
{
	if(gtk_toggle_button_get_active(button) == TRUE)
	{
		gtk_editable_set_editable(GTK_EDITABLE(entryTitle), TRUE);
	
		gtk_editable_set_editable(GTK_EDITABLE(entryArtist), TRUE);
		
		gtk_editable_set_editable(GTK_EDITABLE(entryGenre), TRUE);
		
		gtk_editable_set_editable(GTK_EDITABLE(entryKey), TRUE);
	
		gtk_text_view_set_editable(GTK_TEXT_VIEW(tViewEditor), TRUE);
	}
	else 
	{
		gtk_editable_set_editable(GTK_EDITABLE(entryTitle), FALSE);
	
		gtk_editable_set_editable(GTK_EDITABLE(entryArtist), FALSE);
		
		gtk_editable_set_editable(GTK_EDITABLE(entryGenre), FALSE);
		
		gtk_editable_set_editable(GTK_EDITABLE(entryKey), FALSE);
	
		gtk_text_view_set_editable(GTK_TEXT_VIEW(tViewEditor), FALSE);
	}
}
/*---------------------------------------------------------------------------*/
void editor(GtkWidget *grid, GtkWidget *window)
{
	GtkWidget *frame;
	GtkWidget *boxTop;
	GtkWidget *label1;
	GtkWidget *label2;
	GtkWidget *label3;
	GtkWidget *label4;
	GtkWidget *label5;	
	GtkWidget *button1;
	GtkWidget *button2; 
	GtkWidget *button3;
	GtkWidget *button4;  
	GtkWidget *button6;
	GtkWidget *boxMiddle;
	GtkWidget *boxBottom;
	GtkWidget *separator;
	GtkWidget *scrolledWindow;
	GtkAccelGroup *accelChord;
			    		
	frame = gtk_frame_new(NULL);	
	entryKey = gtk_entry_new();
	entryTitle = gtk_entry_new();
	entryGenre = gtk_entry_new();
	entryArtist = gtk_entry_new();	
	label1 = gtk_label_new("Title:");
	label2 = gtk_label_new("Artist:");
	label3 = gtk_label_new("Genre:");	
	label4 = gtk_label_new("Key:");
	label5 = gtk_label_new("Transpose");
	tViewEditor = gtk_text_view_new();
	accelChord = gtk_accel_group_new();	
	button1 = gtk_button_new_with_label("Insert Chord");
	button2 = gtk_button_new_with_label("Up");
	button6 = gtk_button_new_with_label("Down");
	button3 = gtk_button_new_with_label("Add New");
	button4 = gtk_button_new_with_label("Save");
	button5 = gtk_toggle_button_new_with_label("Edit");
	boxTop = gtk_box_new(GTK_ORIENTATION_VERTICAL, 2);
	boxMiddle = gtk_box_new(GTK_ORIENTATION_VERTICAL, 2);
	boxBottom = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
	scrolledWindow = gtk_scrolled_window_new(NULL, NULL);
	separator = gtk_separator_new(GTK_ORIENTATION_VERTICAL);	
	tBufferEditor = gtk_text_view_get_buffer(GTK_TEXT_VIEW(tViewEditor));
		
		
	gtk_entry_set_placeholder_text(GTK_ENTRY(entryTitle), 
	                               "Enter name of title here");
	gtk_entry_set_placeholder_text(GTK_ENTRY(entryArtist), 
	                               "Enter name of artist here");
//-----------------------------------------------------------------------------	
	// Sets cursor to visible. I think it's set by default 
	// but adding it to make sure.
	gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(tViewEditor), TRUE);
//-----------------------------------------------------------------------------
	// Properties for 'frame' widget.	
	gtk_frame_set_shadow_type(GTK_FRAME(frame), GTK_SHADOW_ETCHED_IN);	
	//gtk_widget_set_size_request(GTK_WIDGET(frame), 200, 200);
	
//-----------------------------------------------------------------------------	
	// Packs 'button3' & 'button4' into 'boxTop'.
	gtk_box_pack_start(GTK_BOX(boxTop), button3, FALSE, TRUE, 2);
	gtk_box_pack_start(GTK_BOX(boxTop), button5, FALSE, TRUE, 2);
	gtk_box_pack_start(GTK_BOX(boxTop), button4, FALSE, TRUE, 2); 
	
	gtk_box_pack_start(GTK_BOX(boxBottom), button6, FALSE, TRUE, 2);
	gtk_box_pack_start(GTK_BOX(boxBottom), separator, FALSE, TRUE, 2);
	gtk_box_pack_start(GTK_BOX(boxBottom), button2, FALSE, TRUE, 2);	
	
	// Packs 'button1' & 'button2' widgets into 'boxBottom' widget.
	gtk_box_pack_start(GTK_BOX(boxMiddle), label5, FALSE, TRUE, 2); 
	gtk_box_pack_start(GTK_BOX(boxMiddle), boxBottom, FALSE, TRUE, 2);
	gtk_box_pack_start(GTK_BOX(boxMiddle), button1, FALSE, TRUE, 2);
	
	// Packs 'textView' widget inside of 'scrolledWindow' widget.	
	gtk_container_add(GTK_CONTAINER(scrolledWindow), tViewEditor);
	
	// Packs 'scrolledWindow' widget into 'frame2' widget.
	gtk_container_add(GTK_CONTAINER(frame), scrolledWindow);
	
	// Adds accelChord to toplevel window.
	gtk_window_add_accel_group(GTK_WINDOW(window), accelChord);
	
	gtk_widget_add_accelerator(button1, "clicked", accelChord, GDK_KEY_i, 
	                           GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
//-----------------------------------------------------------------------------    
    // Attaches widgets to widget grid.	
	gtk_grid_attach(GTK_GRID(grid), label1, 3, 1, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), label2, 3, 2, 1, 1);	
	gtk_grid_attach_next_to(GTK_GRID(grid), entryTitle, label1, GTK_POS_RIGHT, 100, 1);
	gtk_grid_attach_next_to(GTK_GRID(grid), entryArtist, label2, GTK_POS_RIGHT, 100, 1);
	gtk_grid_attach(GTK_GRID(grid), label3, 115, 1, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(grid), entryGenre, label3, GTK_POS_RIGHT, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(grid), label4, label3, GTK_POS_BOTTOM, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(grid), entryKey, label4, GTK_POS_RIGHT, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), frame, 0, 3, 150, 175);
	gtk_grid_attach_next_to(GTK_GRID(grid), boxTop, frame, GTK_POS_RIGHT, 1, 50);
	gtk_grid_attach_next_to(GTK_GRID(grid), boxMiddle, boxTop, GTK_POS_BOTTOM, 1, 1);
	
	// Sets row & column spacing between widgets inside 'grid' widget.
	gtk_grid_set_row_spacing(GTK_GRID(grid), 3);
	gtk_grid_set_column_spacing(GTK_GRID(grid), 3);	
//-----------------------------------------------------------------------------
	g_signal_connect(button5, "toggled", G_CALLBACK(editSong), NULL);	
	g_signal_connect(button1, "clicked", G_CALLBACK(insertChord), NULL);
	g_signal_connect(button4, "clicked", G_CALLBACK(save), NULL);
	g_signal_connect(button3, "clicked", G_CALLBACK(newSong), button5);	
	g_signal_connect(button2, "clicked", G_CALLBACK(transposeUp), button5);
	g_signal_connect(button6, "clicked", G_CALLBACK(transposeDown), button5);	
}