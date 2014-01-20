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

/******** Global Variables ***************************************************/

GtkWidget *button_5,
          *entry_key,
          *entry_genre,
          *entry_title,
          *entry_artist, 
          *t_view_editor;
 
GtkEntryBuffer *entry_buffer;

GtkTextBuffer *t_buffer_editor;

const gchar *get_key,
            *get_title, 
            *get_genre,
            *get_artist;
            
extern char directory[];

extern GtkListStore *list_store;

extern GtkTreeSelection *selection;

extern GtkWidget *tree_view, 
                 *t_view_display;
                 
extern GtkTextBuffer *t_buffer_display;

extern GtkTreePath *tree_path;

extern GtkTreeViewColumn *column;

extern gchar song_path[];

/********** 'set_text' Function **********************************************/

gint set_text(gchar *text, gchar *file_path, gint pos)
{
	FILE *fp;
	
	if((fp = fopen(file_path, "r")) == NULL)
	{
		g_print("Error. No such file exists.\n");
		
		return -1;
	}
	else 
	{
		fseek(fp, pos, SEEK_SET);
		fgets(text, COLUMN_N, fp);
		
		text[strlen(text) -2] = '\0';	
	}
	
	return 0;
}

/************* 'get_chars' Function ******************************************/

// Grabs text starting from 'pos' to 'EOF' and outputs text to 'text'.
// Returns char count through to 'i'. 
gint get_chars(gchar *text, gchar *file_path, gint pos)
{
	gint i;
	
	gchar ch;
		
	FILE *fp;	
	
	if((fp = fopen(file_path, "r")) == NULL)
	{
		g_print("No such file or directory\n");
		
		return -1;
	}
	else 
	{		
		i = 0;		
		
		fseek(fp, pos, SEEK_SET);			
			
		while((ch = fgetc(fp)) != EOF)
		{
			text[i++] = ch;			
		}					
		
		fclose(fp);
		
		return i;
	}
}
	
/*********** 'get_line_char_count' Function **********************************/

gint get_line_char_count(gchar line[][COLUMN_N], gint line_num)
{
	gint char_count;
	
	char_count = strlen(line[line_num]);
	
	return char_count;
}

/********** 'get_text_for_each_line' Function ********************************/

gint get_text_for_each_line(gchar lines[][COLUMN_N], gint line_num)
{
	gint i;
	
	FILE *fp;	
	
	// This will read each line for future text manipulation.
	if((fp = fopen(song_path, "r")) == NULL)            
	{														
		g_print("Error\n");
		
		return -1;									 
	}														 
	else 													
	{														 
		for(i = 0; i < line_num; i++)						
		{													
			fgets(lines[i], COLUMN_N, fp);							
		}
	
		fclose(fp);													
	}

	return 0;
}

/*********** 'get_line_count' Function ***************************************/

gint get_line_count(gchar *file_path)
{
	gchar ch;	
	gint line_count;	
	FILE *fp;
	
	if((fp = fopen(file_path, "r")) == NULL)				
	{													 
		g_print("Error\n");
		
		return -1;									
	}                                                   
	else  											
	{													
		line_count = 0;									
		
		while((ch = fgetc(fp)) != EOF)					 
		{														
			if(ch == '\n')										
			{													
				line_count++;									
			}													
		}
																		
		fclose(fp);		
	}

	return line_count;
}

/******** 'save' function ****************************************************/

void save(GtkWidget *widget, gpointer data)
{	
	GtkTextIter end,
	            start;
	
	gchar value[75];	
		
	gchar *body;
	      
	
	char new_file[45];
	
	FILE *fp;		
	
	gtk_text_buffer_get_start_iter(GTK_TEXT_BUFFER(t_buffer_editor), &start);
	gtk_text_buffer_get_end_iter(GTK_TEXT_BUFFER(t_buffer_editor), &end);	
	
	get_title = gtk_entry_get_text(GTK_ENTRY(entry_title));
	get_artist = gtk_entry_get_text(GTK_ENTRY(entry_artist));
	get_genre = gtk_entry_get_text(GTK_ENTRY(entry_genre));
	get_key = gtk_entry_get_text(GTK_ENTRY(entry_key));	
	body = gtk_text_buffer_get_text(GTK_TEXT_BUFFER(t_buffer_editor), 
	                                &start, &end, TRUE);
	
	sprintf(new_file, "%s%s.chordpro", directory, get_title);
	
	fp = fopen(new_file, "w+");
		
	fprintf(fp, "{title: %s}\n", get_title);
	fprintf(fp, "{subtitle: %s}\n", get_artist);
	fprintf(fp, "{tags: %s}\n", get_genre);
	fprintf(fp, "{key: %s}\n\n", get_key);
	fprintf(fp, "%s", body);
	
	fclose(fp);
	
	g_free(body);	
	
	gtk_text_buffer_set_modified(t_buffer_editor, FALSE);
	
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(button_5), FALSE);
	
	sprintf(value, "%s.chordpro", get_title);	
	
	append_to_list(value);	
}

/********* 'new_song' Function ************************************************/

void new_song(GtkWidget *widget, gpointer button)
{
	GtkTextIter start, end;	
	
	// Unselects all in 'songList' so it will not appear in song editor.	
	gtk_tree_selection_unselect_all(GTK_TREE_SELECTION(selection));	
	
	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(button_5)) == TRUE)
	{
		entry_buffer = gtk_entry_get_buffer(GTK_ENTRY(entry_title));
	
		gtk_entry_buffer_delete_text(GTK_ENTRY_BUFFER(entry_buffer), 0, -1);

		entry_buffer = gtk_entry_get_buffer(GTK_ENTRY(entry_artist));
	
		gtk_entry_buffer_delete_text(GTK_ENTRY_BUFFER(entry_buffer), 0, -1);
	
		entry_buffer = gtk_entry_get_buffer(GTK_ENTRY(entry_genre));
	
		gtk_entry_buffer_delete_text(GTK_ENTRY_BUFFER(entry_buffer), 0, -1);
	
		entry_buffer = gtk_entry_get_buffer(GTK_ENTRY(entry_key));
	
		gtk_entry_buffer_delete_text(GTK_ENTRY_BUFFER(entry_buffer), 0, -1);
	
		gtk_text_buffer_get_start_iter(GTK_TEXT_BUFFER(t_buffer_editor), &start);
		gtk_text_buffer_get_end_iter(GTK_TEXT_BUFFER(t_buffer_editor), &end);
	
		gtk_text_buffer_delete(GTK_TEXT_BUFFER(t_buffer_editor), &start, &end);
	}	
}

/************* 'edit_song' Function ******************************************/

void edit_song(GtkToggleButton *button, gpointer data)
{
	if(gtk_toggle_button_get_active(button) == TRUE)
	{
		gtk_editable_set_editable(GTK_EDITABLE(entry_title), TRUE);
	
		gtk_editable_set_editable(GTK_EDITABLE(entry_artist), TRUE);
		
		gtk_editable_set_editable(GTK_EDITABLE(entry_genre), TRUE);
		
		gtk_editable_set_editable(GTK_EDITABLE(entry_key), TRUE);
	
		gtk_text_view_set_editable(GTK_TEXT_VIEW(t_view_editor), TRUE);
	}
	else 
	{
		gtk_editable_set_editable(GTK_EDITABLE(entry_title), FALSE);
	
		gtk_editable_set_editable(GTK_EDITABLE(entry_artist), FALSE);
		
		gtk_editable_set_editable(GTK_EDITABLE(entry_genre), FALSE);
		
		gtk_editable_set_editable(GTK_EDITABLE(entry_key), FALSE);
	
		gtk_text_view_set_editable(GTK_TEXT_VIEW(t_view_editor), FALSE);
	}
}

/************ 'editor' Function **********************************************/

void editor(GtkWidget *grid, GtkWidget *window)
{
	GtkWidget *frame,
	          *box_top,
	          *label_1,
	          *label_2,
	          *label_3,
	          *label_4,
	          *label_5,	
	          *button_1,
	          *button_2, 
	          *button_3,
	          *button_4,  
	          *button_6,
	          *box_middle,
	          *box_bottom,
	          *arrow_left,
	          *arrow_right,
	          *scrolled_window;
			    		
	frame = gtk_frame_new(NULL);	
	entry_key = gtk_entry_new();
	entry_title = gtk_entry_new();
	entry_genre = gtk_entry_new();
	entry_artist = gtk_entry_new();		
	label_1 = gtk_label_new("Title:");
	label_2 = gtk_label_new("Artist:");
	label_3 = gtk_label_new("Genre:");	
	label_4 = gtk_label_new("Key:");
	label_5 = gtk_label_new("Transpose");
	t_view_editor = gtk_text_view_new();
	//accelChord = gtk_accel_group_new();	
	button_1 = gtk_button_new_with_mnemonic("_Insert Chord");
	button_2 = gtk_button_new();
	button_6 = gtk_button_new();
	button_3 = gtk_button_new_with_label("Add New");
	button_4 = gtk_button_new_with_label("Save");
	button_5 = gtk_toggle_button_new_with_label("Edit");
	box_top = gtk_box_new(GTK_ORIENTATION_VERTICAL, 2);
	box_middle = gtk_box_new(GTK_ORIENTATION_VERTICAL, 2);
	box_bottom = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
	scrolled_window = gtk_scrolled_window_new(NULL, NULL);
	arrow_left = gtk_arrow_new(GTK_ARROW_LEFT, GTK_SHADOW_ETCHED_IN);
	arrow_right = gtk_arrow_new(GTK_ARROW_RIGHT, GTK_SHADOW_ETCHED_IN);	
	t_buffer_editor = gtk_text_view_get_buffer(GTK_TEXT_VIEW(t_view_editor));
	
	gtk_editable_set_editable(GTK_EDITABLE(entry_key), FALSE);
	gtk_editable_set_editable(GTK_EDITABLE(entry_genre), FALSE);
	gtk_editable_set_editable(GTK_EDITABLE(entry_title), FALSE);
	gtk_editable_set_editable(GTK_EDITABLE(entry_artist), FALSE);
	gtk_text_view_set_editable(GTK_TEXT_VIEW(t_view_editor), FALSE);		
	
	
	gtk_entry_set_placeholder_text(GTK_ENTRY(entry_key), 
	                               "Key");
	gtk_entry_set_placeholder_text(GTK_ENTRY(entry_genre), 
	                               "Enter genre");
	gtk_entry_set_placeholder_text(GTK_ENTRY(entry_title), 
	                               "Enter title");
	gtk_entry_set_placeholder_text(GTK_ENTRY(entry_artist), 
	                               "Enter artist");

	gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(t_view_editor), TRUE);

//---- Properties for 'frame' widget ------------------------------------------
	
	gtk_frame_set_shadow_type(GTK_FRAME(frame), GTK_SHADOW_ETCHED_IN);		
	
//--- Packs 'button3', 'button 4', & button 5' into 'box_top'------------------	
	
	gtk_box_pack_start(GTK_BOX(box_top), button_3, FALSE, TRUE, 2);
	gtk_box_pack_start(GTK_BOX(box_top), button_5, FALSE, TRUE, 2);
	gtk_box_pack_start(GTK_BOX(box_top), button_4, FALSE, TRUE, 2);
	 
//-----------------------------------------------------------------------------	
	// Buttonbox setup and packing.	
	gtk_container_add(GTK_CONTAINER(button_2), arrow_right);
	gtk_container_add(GTK_CONTAINER(button_6), arrow_left);	
		                          
	gtk_widget_set_tooltip_text(GTK_WIDGET(button_6), "-1/2 step");
	gtk_widget_set_tooltip_text(GTK_WIDGET(button_2), "+1/2 step");	
	
	gtk_button_box_set_layout(GTK_BUTTON_BOX(box_bottom), 
	                          GTK_BUTTONBOX_CENTER);	
	
	gtk_container_add(GTK_CONTAINER(box_bottom), button_6);
	gtk_container_add(GTK_CONTAINER(box_bottom), button_2);	

	gtk_button_box_set_child_non_homogeneous(GTK_BUTTON_BOX(box_bottom),
	                                         GTK_WIDGET(button_6), TRUE);
	gtk_button_box_set_child_non_homogeneous(GTK_BUTTON_BOX(box_bottom),
	                                         GTK_WIDGET(button_2), TRUE);
//-----------------------------------------------------------------------------
	// Packs 'button_1' & 'button_2' widgets into 'box_bottom' widget.
	gtk_box_pack_start(GTK_BOX(box_middle), label_5, FALSE, TRUE, 2); 
	gtk_box_pack_start(GTK_BOX(box_middle), box_bottom, FALSE, TRUE, 2);
	gtk_box_pack_start(GTK_BOX(box_middle), button_1, FALSE, TRUE, 2);
	
	// Packs 'textView' widget inside of 'scrolled_window' widget.	
	gtk_container_add(GTK_CONTAINER(scrolled_window), t_view_editor);
	
	// Packs 'scrolled_window' widget into 'frame2' widget.
	gtk_container_add(GTK_CONTAINER(frame), scrolled_window);
	
	// Adds accelChord to toplevel window.
	//gtk_window_add_accel_group(GTK_WINDOW(window), accelChord);
	
	//gtk_widget_add_accelerator(button_1, "clicked", accelChord, GDK_KEY_i, 
	                           //GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
//-----------------------------------------------------------------------------    
    // Attaches widgets to widget grid.	
	gtk_grid_attach(GTK_GRID(grid), label_1, 3, 1, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), label_2, 3, 2, 1, 1);	
	gtk_grid_attach_next_to(GTK_GRID(grid), entry_title, label_1, GTK_POS_RIGHT, 100, 1);
	gtk_grid_attach_next_to(GTK_GRID(grid), entry_artist, label_2, GTK_POS_RIGHT, 100, 1);
	gtk_grid_attach(GTK_GRID(grid), label_3, 115, 1, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(grid), entry_genre, label_3, GTK_POS_RIGHT, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(grid), label_4, label_3, GTK_POS_BOTTOM, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(grid), entry_key, label_4, GTK_POS_RIGHT, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), frame, 0, 3, 150, 175);
	gtk_grid_attach_next_to(GTK_GRID(grid), box_top, frame, GTK_POS_RIGHT, 1, 50);
	gtk_grid_attach_next_to(GTK_GRID(grid), box_middle, box_top, GTK_POS_BOTTOM, 1, 1);
	
	// Sets row & column spacing between widgets inside 'grid' widget.
	gtk_grid_set_row_spacing(GTK_GRID(grid), 3);
	gtk_grid_set_column_spacing(GTK_GRID(grid), 3);	
//-----------------------------------------------------------------------------
	g_signal_connect(button_5, "toggled", G_CALLBACK(edit_song), NULL);	
	g_signal_connect(button_1, "clicked", G_CALLBACK(insert_chord), NULL);
	g_signal_connect(button_4, "clicked", G_CALLBACK(save), NULL);
	g_signal_connect(button_3, "clicked", G_CALLBACK(new_song), button_5);	
	g_signal_connect(button_2, "clicked", G_CALLBACK(transpose_up), button_5);
	g_signal_connect(button_6, "clicked", G_CALLBACK(transpose_down), button_5);	
}