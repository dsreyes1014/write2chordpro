// Author: Andrew Reye
// Date Last Modified: 11-29-2013

#include <gtk/gtk.h>
#include <stdio.h>

#include "display.h"
#include "editor.h"

/******* Global Variables ****************************************************/
gint char_line,
     line_num_C, 
     line_count_C,
     char_line_offset;

extern GtkWidget *entry_key;
extern GtkWidget *entry_title;
extern GtkWidget *entry_artist;

extern GtkTextBuffer *t_buffer_editor;

/********** 'set_chord_position' function ************************************/
gint set_chord_position(GtkWidget *t_view, GtkTextBuffer *buffer)
{
	GtkTextTag *tag;	

	GtkTextMark *end_chord,
	            *start_chord;	

	GtkTextIter ch,	
	            chord_S,
	            chord_E,
	            match_end,
	            match_start,	
	            start_of_line;
	
	GtkClipboard *clipboard;
		
	gint line_num_1,
	     line_num_2,
	     line_count_V,	
	     line_offset_1,
	     line_offset_2;

	line_count_V = gtk_text_buffer_get_line_count(buffer);
	clipboard = gtk_clipboard_get(GDK_SELECTION_CLIPBOARD);	
	
	gtk_text_buffer_get_start_iter(buffer, &start_of_line);
	
	if(gtk_text_iter_forward_search(&start_of_line, "[", 1, 
									&match_start, &match_end, NULL))
	{		
		gtk_text_buffer_create_mark(buffer, "start_chord", &match_start, FALSE);
		
		start_chord = gtk_text_buffer_get_mark(buffer, "start_chord");
	}
	else 
	{
		return -1;
	}
	
	if(gtk_text_iter_forward_search(&start_of_line, "]", 1, 
									&match_start, &match_end, NULL))		
	{		
		gtk_text_buffer_create_mark(buffer, "end_chord", &match_end, FALSE);
		
		end_chord = gtk_text_buffer_get_mark(buffer, "end_chord");	
	}	
	else 
	{
		return -1;	
	}

	// Initializes iters at mark.
	gtk_text_buffer_get_iter_at_mark(buffer, &chord_S, start_chord);
	gtk_text_buffer_get_iter_at_mark(buffer, &chord_E, end_chord);
	
	// Get line and line offset of iter. If we just obtain the offset 
	// within buffer then chord_S will not format as desired.
	line_num_1 = gtk_text_iter_get_line(&chord_S);
	line_offset_1 = gtk_text_iter_get_line_index(&chord_S);	
	line_num_2 = gtk_text_iter_get_line(&chord_E);
	line_offset_2 = gtk_text_iter_get_line_index(&chord_E);
	
	// This returns with error if end bracket does not have a 
	// matching start bracket.
	if(line_offset_1 > line_offset_2)
	{
		return -1;	
	}
	
	//g_print("Lineoffset of start:end bracket:\n%d\n%d\n", line_offset_1, line_offset_2);
		
	// If chord found is found more than two lines down
	// refresh global values of 'line_count_C' and 'line_num_C'. 
	if(line_num_1 > (line_num_C + 1))	
	{
		line_num_C = line_num_1;
		line_count_C = line_count_V;
	}
	
	// Copy, cut, and add tags to the section between the marks.
	gtk_text_buffer_select_range(buffer, &chord_S, &chord_E);
	tag = gtk_text_buffer_create_tag(buffer, NULL, "background", "gold",
									 "weight", "500", 
									 "foreground-gdk", "black3", NULL);
	gtk_text_buffer_apply_tag(buffer, tag, &chord_S, &chord_E);
	gtk_text_buffer_cut_clipboard(buffer, clipboard, TRUE);
	
	// This finds first chord of line.
	if(line_count_V == line_count_C) 
	{	
		gtk_text_buffer_get_iter_at_line(buffer, &start_of_line, line_num_1);
		gtk_text_buffer_insert(buffer, &start_of_line, "\n", -1);
	}

	// This finds the rest of the chord_S on the same line as the first. 
	if(line_num_1 == (line_num_C + 1))
	{
		line_num_1 = line_num_1 - 1;		
		line_num_2 = line_num_2 - 1;
	}

	gtk_text_buffer_get_iter_at_line(buffer, &ch, line_num_1);
	
	// Insert 110 blank spaces so we can insert chord_S at higher offsets than 0.
	// GtkTextBuffer does not allow us to insert past a newline character
	// so we move it with spaces to allow us to place chord_S at offsets 
	// past a newline character.
	if(gtk_text_iter_get_char(&ch) == '\n')
	{	
		gtk_text_buffer_insert(buffer, &ch, 
	    "                                                                                                              ",
							    -1);		
	}
	
	// Place iter at the same offset one line above.
	gtk_text_buffer_get_iter_at_line_index(buffer, &ch, line_num_1, line_offset_1);
	
	//g_print("Position after cut: %d\n", line_offset_1);
	gtk_text_buffer_paste_clipboard(buffer, clipboard, &ch, TRUE);	
	
	gtk_text_buffer_get_iter_at_line_offset(buffer, &ch, line_num_1, line_offset_2);
	
	// Deletes the end bracket.	
	gtk_text_buffer_backspace(buffer, &ch, FALSE, TRUE);
	gtk_text_buffer_get_iter_at_line_offset(buffer, &ch, line_num_1, line_offset_1 +1);
	
	// Deletes the start bracket. 	
	gtk_text_buffer_backspace(buffer, &ch, FALSE, TRUE);
	gtk_text_buffer_delete_mark_by_name(buffer, "start_chord");
	gtk_text_buffer_delete_mark_by_name(buffer, "end_chord");
	
	return 0;
}

/****** 'text_tags' function *************************************************/
gint text_tags(GtkTextBuffer *buffer, const gchar *text)
{
	GtkTextTag *tag;	
	
	GtkTextIter start,
	            match_end,
	            match_start;

	gtk_text_buffer_get_iter_at_line_offset(buffer, &start, 
	                                        char_line,
	                                        char_line_offset);	
	
	if(gtk_text_iter_forward_search(&start, text,
		                                GTK_TEXT_SEARCH_CASE_INSENSITIVE,
										&match_start, &match_end, NULL))
	{
		tag = gtk_text_buffer_create_tag(buffer, NULL, 
									     "font", "italic 12", 
									     "weight", 650, "underline", 
									     PANGO_UNDERLINE_SINGLE, 
									     NULL);

		gtk_text_buffer_apply_tag(buffer, tag, &match_start, &match_end);
		
		char_line = gtk_text_iter_get_line(&match_end);
		char_line_offset = gtk_text_iter_get_line_offset(&match_end);
	
		return 0;	
	}	
	else 
	{
		return -1;	
	}
}

/****** 'display function' ***************************************************/
void display(GtkTextBuffer *buffer, GtkWidget *t_view)
{		
	GtkTextTag *tag;
	
	GtkTextIter end,
	            start,
	            match_end,
	            match_start;

	gint i,
	     j; 
	
	gchar *key,
	      *body,
	      *title,	
	      *artist;
	
	const gchar *song_section[] = {"Verse:", "Verse 1", "Verse 2:",
								  "Verse 3:","Bridge:", "Bridge 1:",
								  "Bridge 2:", "Bridge 3:", "Intro:",
								  "End:", "PreChorus:", "Verso:",
								  "Chorus:", "Coro:", "Puente:", 
								  "Key Shift:"};
								  
//-----------------------------------------------------------------------------				
	gtk_text_buffer_get_start_iter(buffer, &start);
	gtk_text_buffer_get_end_iter(buffer, &end);	
	
	gtk_text_buffer_delete(buffer, &start, &end);	
	
	gtk_text_view_set_editable(GTK_TEXT_VIEW(t_view), FALSE);
//-----------------------------------------------------------------------------	
	// Sets attributes for Title (line 0).	
	title = gtk_editable_get_chars(GTK_EDITABLE(entry_title), 0, -1);
	
	gtk_text_buffer_get_iter_at_line(buffer, &start, 0);
	
	gtk_text_buffer_place_cursor(buffer, &start);	
	
	gtk_text_buffer_insert_at_cursor(buffer, title, -1);
	
	g_free(title);
			
	gtk_text_buffer_get_iter_at_line(buffer, &start, 0);
	
	gtk_text_buffer_get_iter_at_line(buffer, &end, 0);
	
	gtk_text_iter_forward_to_line_end(&end);			
			
	tag = gtk_text_buffer_create_tag(buffer, NULL, "weight", 1000,
									 "font", "monospace 30", 
									  "underline", PANGO_UNDERLINE_SINGLE, 
									 NULL);
												  
	gtk_text_buffer_apply_tag(buffer, tag, &start, &end);
//-----------------------------------------------------------------------------			
	// Inserts text 'by:' before artist with attributes.
	tag = gtk_text_buffer_create_tag(buffer, NULL, "font", 
	                                 "monospace 10", 
		    						 "weight-set", TRUE, 
		    						 "weight", 650, NULL);
		    						 
	gtk_text_buffer_get_iter_at_line(buffer, &start, 0);
	
	gtk_text_iter_forward_to_line_end(&start);
	
	gtk_text_buffer_place_cursor(buffer, &start);
	
	// Have to insert '\n' to create next line
	gtk_text_buffer_insert_at_cursor(buffer, "\n", -1);
	
	gtk_text_buffer_get_iter_at_line(buffer, &start, 1);
	
	gtk_text_buffer_place_cursor(buffer, &start);
	
	gtk_text_buffer_insert_at_cursor(buffer, "Artist: ", -1);
	
	gtk_text_buffer_get_iter_at_line(buffer, &start, 1);
	
	gtk_text_buffer_get_iter_at_line(buffer, &end, 1);
	
	gtk_text_iter_forward_to_line_end(&end);
	
	gtk_text_buffer_apply_tag(buffer, tag, &start, &end);
//-----------------------------------------------------------------------------			
	artist = gtk_editable_get_chars(GTK_EDITABLE(entry_artist), 0, -1);	
	
	gtk_text_buffer_get_iter_at_line_offset(buffer, &start, 1, 8);
	
	gtk_text_buffer_place_cursor(buffer, &start);
	
	gtk_text_buffer_insert_at_cursor(buffer, artist, -1);
	
	g_free(artist);	
	
	// Sets attributes for Artist (line 1).
	gtk_text_buffer_get_iter_at_line_offset(buffer, &start, 1, 8);
	
	gtk_text_buffer_get_iter_at_line(buffer, &end, 1);
	
	gtk_text_iter_forward_to_line_end(&end);			
	
	tag = gtk_text_buffer_create_tag(buffer, NULL, "weight", 500,
									 "weight-set", TRUE, 
									 "font", "monospace italic 12", NULL);
												  
	gtk_text_buffer_apply_tag(buffer, tag, &start, &end);	
//-----------------------------------------------------------------------------	
	tag = gtk_text_buffer_create_tag(buffer, NULL, "font", 
	                                 "monospace 10", 
		    						 "weight", 650, NULL);
	
	gtk_text_buffer_get_iter_at_line(buffer, &start, 1);
	
	gtk_text_iter_forward_to_line_end(&start);
	
	gtk_text_buffer_place_cursor(buffer, &start);
	
	// Have to insert '\n' to create next line
	gtk_text_buffer_insert_at_cursor(buffer, "\n", -1);
	
	gtk_text_buffer_get_iter_at_line(buffer, &start, 2);
	
	gtk_text_buffer_place_cursor(buffer, &start);
	
	gtk_text_buffer_insert_at_cursor(buffer, "Key: ", -1);
	
	gtk_text_buffer_get_iter_at_line(buffer, &start, 2);
	
	gtk_text_buffer_get_iter_at_line(buffer, &end, 2);
	
	gtk_text_iter_forward_to_line_end(&end);
	
	gtk_text_buffer_apply_tag(buffer, tag, &start, &end);
//-----------------------------------------------------------------------------
	key = gtk_editable_get_chars(GTK_EDITABLE(entry_key), 0, -1);
	
	gtk_text_buffer_get_iter_at_line_offset(buffer, &start, 2, 5);
	
	gtk_text_buffer_place_cursor(buffer, &start);
	
	gtk_text_buffer_insert_at_cursor(buffer, key, -1);
	
	g_free(key);	
	
	gtk_text_buffer_get_iter_at_line_offset(buffer, &start, 2, 5);
	
	gtk_text_buffer_get_iter_at_line(buffer, &end, 2);
	
	gtk_text_iter_forward_to_line_end(&end);			
	
	tag = gtk_text_buffer_create_tag(buffer, NULL, "weight", 500,
									 "weight-set", TRUE, 
									 "font", "monospace italic 12", NULL);
												  
	gtk_text_buffer_apply_tag(buffer, tag, &start, &end);
//-----------------------------------------------------------------------------	
	gtk_text_buffer_get_iter_at_line(buffer, &start, 2);
	
	gtk_text_iter_forward_to_line_end(&start);
	
	gtk_text_buffer_place_cursor(buffer, &start);
	
	// Have to insert '\n' to create next line
	gtk_text_buffer_insert_at_cursor(buffer, "\n\n", -1);
	
	gtk_text_buffer_get_start_iter(t_buffer_editor, &start);
	gtk_text_buffer_get_end_iter(t_buffer_editor, &end);	
	
	body = gtk_text_buffer_get_text(t_buffer_editor, &start, &end, FALSE);
	
	gtk_text_buffer_get_iter_at_line(buffer, &start, 4);
	
	gtk_text_buffer_place_cursor(buffer, &start);
	
	gtk_text_buffer_insert_at_cursor(buffer, body, -1);
//-----------------------------------------------------------------------------
	gtk_text_buffer_get_iter_at_line(buffer, &start, 4);
	gtk_text_buffer_get_end_iter(buffer, &end);
	
	tag = gtk_text_buffer_create_tag(buffer, NULL, "font", 
	                                    "monospace", NULL);
	                                    
	gtk_text_buffer_apply_tag(buffer, tag, &start, &end);	
	
	line_count_C = gtk_text_buffer_get_line_count(buffer);
	
	gtk_text_buffer_get_start_iter(buffer, &start);	
	
	if(gtk_text_iter_forward_search(&start, "[", 1, 
								 &match_start, &match_end, NULL))
	{								 
 		line_num_C = gtk_text_iter_get_line(&match_start);
	}

	for(i = 0; i == 0;)
	{
		i = set_chord_position(t_view, buffer);	
	}

//-----------------------------------------------------------------------------			
	// This section is for setting the attributes of the text
	// 'Verse:', 'Chorus:'etc...			
	
	char_line = 0;
	char_line_offset = 0;
	
	for(i = 0; i < 16;)
	{
		for(j = 0; j == 0;)
		{
			j = text_tags(buffer, song_section[i]);		
		}	
		
		if(j != 0)
		{
			char_line = 0;
			char_line_offset = 0;	
			
			i++;	
		}
	}		

//-----------------------------------------------------------------------------
	//g_print("Function return: %d\n", set_chord_position(t_view, buffer));
	//g_print("Line number of chord: %d\n", line_num_C);*/	
}