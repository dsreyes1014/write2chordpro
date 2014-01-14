// Author: Andrew Reyes
// Date: 12-18-2013

#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>

#include "transpose.h"
#include "editor.h"

gchar *note_sharps[] = {"A", "A#", "B", 
                       "C", "C#", "D", 
                       "D#", "E", "F", 
                       "F#", "G", "G#"};
                 
gchar *note_flats[] = {"A", "Bb", "B",
                      "C", "Db", "D",
                      "Eb", "E", "F",
                      "Gb", "G", "Ab"};

gint pos_1, pos_2;
extern gchar song_path[];
extern GtkTextBuffer *t_buffer_editor;
extern GtkWidget *t_view_editor, *button_5, *entry_key;
extern GtkEntryBuffer *entry_buffer;

gint slash_chord_down(void)
{
	GtkTextIter ch_1;
	GtkTextIter ch_2;
	GtkTextIter match_end;
	GtkTextIter match_start;		
	GtkTextIter start;
	
	GtkTextMark *start_chord;
	GtkTextMark *end_chord;
	
	gchar *chord;
	gchar *accidental;
	
	gint i;	
	
	gtk_text_buffer_get_iter_at_offset(t_buffer_editor, &start, pos_2);	
	
	// This will find any slash chord and transpose it as well.
	if(gtk_text_iter_forward_search(&start, "/", 1,
	                                &match_start, &match_end, NULL))
	{
		// Get position after first instance of "[". If not it will keep looping 
		// on the first instance. 
		pos_2 = gtk_text_iter_get_offset(&match_end);	
		
		gtk_text_buffer_create_mark(t_buffer_editor, "start_chord", &match_start, FALSE);
		gtk_text_buffer_create_mark(t_buffer_editor, "end_chord", &match_end, FALSE);
		
		start_chord = gtk_text_buffer_get_mark(t_buffer_editor, "start_chord");		
		end_chord = gtk_text_buffer_get_mark(t_buffer_editor, "end_chord");
		
		gtk_text_buffer_get_iter_at_mark(t_buffer_editor, &ch_1, start_chord);
		gtk_text_buffer_get_iter_at_mark(t_buffer_editor, &ch_2, end_chord);		
				
		gtk_text_iter_forward_chars(&ch_1, 2);
		gtk_text_iter_forward_chars(&ch_2, 2);
		
		accidental = gtk_text_iter_get_slice(&ch_1, &ch_2);
		 
		if(((strcmp(accidental, "b")) == 0) ||
		   ((strcmp(accidental, "#")) == 0)) 
		{
			gtk_text_iter_backward_chars(&ch_1, 1);
			
			chord = gtk_text_iter_get_slice(&ch_1, &ch_2);
			
			if((strcmp(accidental, "b")) == 0)
			{	
				for(i = 0; i <= 11; i++)
				{				
					if((strcmp(chord, note_flats[i])) == 0)
					{
						break;				
					}
				}
			}
			else if((strcmp(accidental, "#")) == 0)
			{
				for(i = 0; i <= 11; i++)
				{				
					if((strcmp(chord, note_sharps[i])) == 0)
					{
						break;				
					}
				}			
			}
		
			gtk_text_buffer_place_cursor(t_buffer_editor, &ch_1);	
			
			gtk_text_buffer_select_range(t_buffer_editor, &ch_1, &ch_2);
			
			gtk_text_buffer_delete_selection(t_buffer_editor, FALSE, TRUE);
			
			gtk_text_buffer_insert_at_cursor(t_buffer_editor, note_flats[i - 1], -1);	
			
			g_free(chord);	
			g_free(accidental);
			
			gtk_text_buffer_delete_mark_by_name(t_buffer_editor, "start_chord");
			gtk_text_buffer_delete_mark_by_name(t_buffer_editor, "end_chord");			
		}		
		else 
		{
			gtk_text_iter_backward_chars(&ch_1, 1);
			gtk_text_iter_backward_chars(&ch_2, 1);	
			
			chord = gtk_text_iter_get_slice(&ch_1, &ch_2);
			
			for(i = 0; i <= 11; i++)
			{				
				if((strcmp(chord, note_flats[i])) == 0)
				{
					break;				
				}
			}	
			
			gtk_text_buffer_place_cursor(t_buffer_editor, &ch_1);
			
			gtk_text_buffer_select_range(t_buffer_editor, &ch_1, &ch_2);
			
			gtk_text_buffer_delete_selection(t_buffer_editor, FALSE, TRUE);
			
			if((strcmp(note_sharps[i], "A")) != 0)
			{			
				gtk_text_buffer_insert_at_cursor(t_buffer_editor, note_flats[i - 1], -1);
			}
			else 
			{
				gtk_text_buffer_insert_at_cursor(t_buffer_editor, note_flats[11], -1);
			}
			
			g_free(chord);
			g_free(accidental);
			
			gtk_text_buffer_delete_mark_by_name(t_buffer_editor, "start_chord");
			gtk_text_buffer_delete_mark_by_name(t_buffer_editor, "end_chord");
		}
	}
	else 
	{
		return -1;	
	}

	return 0;
}

gint slash_chord_up(void)
{
	GtkTextIter ch_1;
	GtkTextIter ch_2;
	GtkTextIter start;	
	GtkTextIter match_end;
	GtkTextIter match_start;		
	
	GtkTextMark *end_chord;
	GtkTextMark *start_chord;
	
	gchar *chord;
	gchar *accidental;
	
	gint i;
//-----------------------------------------------------------------------------	
	gtk_text_buffer_get_iter_at_offset(t_buffer_editor, &start, pos_2);	
	
	// This will find any slash chord and transpose it as well.
	if(gtk_text_iter_forward_search(&start, "/", 1,
	                                &match_start, &match_end, NULL))
	{
		pos_2 = gtk_text_iter_get_offset(&match_end);	
		
		gtk_text_buffer_create_mark(t_buffer_editor, "start_chord",
		                            &match_start, FALSE);
		                            
		gtk_text_buffer_create_mark(t_buffer_editor, "end_chord",
		                            &match_end, FALSE);
		
		start_chord = gtk_text_buffer_get_mark(t_buffer_editor, "start_chord");		
		end_chord = gtk_text_buffer_get_mark(t_buffer_editor, "end_chord");
		
		gtk_text_buffer_get_iter_at_mark(t_buffer_editor, &ch_1, start_chord);
		gtk_text_buffer_get_iter_at_mark(t_buffer_editor, &ch_2, end_chord);		
				
		gtk_text_iter_forward_chars(&ch_1, 2);
		gtk_text_iter_forward_chars(&ch_2, 2);
		
		accidental = gtk_text_iter_get_slice(&ch_1, &ch_2);
		 
		if(((strcmp(accidental, "b")) == 0) ||
		   ((strcmp(accidental, "#")) == 0)) 
		{
			gtk_text_iter_backward_chars(&ch_1, 1);
			
			chord = gtk_text_iter_get_slice(&ch_1, &ch_2);
			
			if((strcmp(accidental, "b")) == 0)
			{	
				for(i = 0; i <= 11; i++)
				{				
					if((strcmp(chord, note_flats[i])) == 0)
					{
						break;				
					}
				}
			}
			else if((strcmp(accidental, "#")) == 0)
			{
				for(i = 0; i <= 11; i++)
				{				
					if((strcmp(chord, note_sharps[i])) == 0)
					{
						break;				
					}
				}			
			}
		
			gtk_text_buffer_place_cursor(t_buffer_editor, &ch_1);	
			
			gtk_text_buffer_select_range(t_buffer_editor, &ch_1, &ch_2);
		
			gtk_text_buffer_delete_selection(t_buffer_editor, FALSE, TRUE);
			
			if((strcmp(note_sharps[i], "G#")) != 0)
			{			
				gtk_text_buffer_insert_at_cursor(t_buffer_editor, note_sharps[i + 1], -1);
			}
			else 
			{
				gtk_text_buffer_insert_at_cursor(t_buffer_editor, note_sharps[0], -1);
			}
			
			g_free(chord);	
			g_free(accidental);
			
			gtk_text_buffer_delete_mark_by_name(t_buffer_editor, "start_chord");
			gtk_text_buffer_delete_mark_by_name(t_buffer_editor, "end_chord");			
		}		
		else 
		{
			gtk_text_iter_backward_chars(&ch_1, 1);
			gtk_text_iter_backward_chars(&ch_2, 1);	
			
			chord = gtk_text_iter_get_slice(&ch_1, &ch_2);
						
			for(i = 0; i <= 11; i++)
			{				
				if((strcmp(chord, note_sharps[i])) == 0)
				{
					break;				
				}
			}	
			
			gtk_text_buffer_place_cursor(t_buffer_editor, &ch_1);
			
			gtk_text_buffer_select_range(t_buffer_editor, &ch_1, &ch_2);
			
			gtk_text_buffer_delete_selection(t_buffer_editor, FALSE, TRUE);
			
			gtk_text_buffer_insert_at_cursor(t_buffer_editor, note_sharps[i + 1], -1);	
			
			g_free(chord);
			g_free(accidental);
			
			gtk_text_buffer_delete_mark_by_name(t_buffer_editor, "start_chord");
			gtk_text_buffer_delete_mark_by_name(t_buffer_editor, "end_chord");
		}
	}
	else 
	{
		return -1;	
	}

	return 0;
}

gint chord_up(void)
{		
	GtkTextIter ch_1;
	GtkTextIter ch_2;
	GtkTextIter match_end;
	GtkTextIter match_start;		
	GtkTextIter start;
	
	GtkTextMark *start_chord;
	GtkTextMark *end_chord;
	
	gchar *chord;
	gchar *accidental;
	
	gint i;	
	
	gtk_text_buffer_get_iter_at_offset(t_buffer_editor, &start, pos_1);	

	if(gtk_text_iter_forward_search(&start, "[", 1,
	                                &match_start, &match_end, NULL))
	{
		pos_1 = gtk_text_iter_get_offset(&match_end);	
		
		gtk_text_buffer_create_mark(t_buffer_editor, "start_chord", &match_start, FALSE);
		gtk_text_buffer_create_mark(t_buffer_editor, "end_chord", &match_end, FALSE);
		
		start_chord = gtk_text_buffer_get_mark(t_buffer_editor, "start_chord");		
		end_chord = gtk_text_buffer_get_mark(t_buffer_editor, "end_chord");
		
		gtk_text_buffer_get_iter_at_mark(t_buffer_editor, &ch_1, start_chord);
		gtk_text_buffer_get_iter_at_mark(t_buffer_editor, &ch_2, end_chord);		
				
		gtk_text_iter_forward_chars(&ch_1, 2);
		gtk_text_iter_forward_chars(&ch_2, 2);
		
		accidental = gtk_text_iter_get_slice(&ch_1, &ch_2);
		 
		if(((strcmp(accidental, "b")) == 0) ||
		   ((strcmp(accidental, "#")) == 0)) 
		{
			gtk_text_iter_backward_chars(&ch_1, 1);
			
			chord = gtk_text_iter_get_slice(&ch_1, &ch_2);
			
			if((strcmp(accidental, "b")) == 0)
			{	
				for(i = 0; i <= 11; i++)
				{				
					if((strcmp(chord, note_flats[i])) == 0)
					{
						break;				
					}
				}
			}
			else if((strcmp(accidental, "#")) == 0)
			{
				for(i = 0; i <= 11; i++)
				{				
					if((strcmp(chord, note_sharps[i])) == 0)
					{
						break;				
					}
				}			
			}
		
			gtk_text_buffer_place_cursor(t_buffer_editor, &ch_1);	
			
			gtk_text_buffer_select_range(t_buffer_editor, &ch_1, &ch_2);
			
			gtk_text_buffer_delete_selection(t_buffer_editor, FALSE, TRUE);
			
			if((strcmp(note_sharps[i], "G#")) != 0)
			{			
				gtk_text_buffer_insert_at_cursor(t_buffer_editor, note_sharps[i + 1], -1);
			}
			else 
			{
				gtk_text_buffer_insert_at_cursor(t_buffer_editor, note_sharps[0], -1);
			}
					
			g_free(chord);	
			g_free(accidental);
			
			gtk_text_buffer_delete_mark_by_name(t_buffer_editor, "start_chord");
			gtk_text_buffer_delete_mark_by_name(t_buffer_editor, "end_chord");			
		}		
		else 
		{
			gtk_text_iter_backward_chars(&ch_1, 1);
			gtk_text_iter_backward_chars(&ch_2, 1);	
			
			chord = gtk_text_iter_get_slice(&ch_1, &ch_2);
			
			for(i = 0; i <= 11; i++)
			{				
				if((strcmp(chord, note_sharps[i])) == 0)
				{
					break;				
				}
			}	
			
			gtk_text_buffer_place_cursor(t_buffer_editor, &ch_1);
			
			gtk_text_buffer_select_range(t_buffer_editor, &ch_1, &ch_2);
			
			gtk_text_buffer_delete_selection(t_buffer_editor, FALSE, TRUE);
			
			gtk_text_buffer_insert_at_cursor(t_buffer_editor, note_sharps[i + 1], -1);
						
			g_free(chord);
			g_free(accidental);
			
			gtk_text_buffer_delete_mark_by_name(t_buffer_editor, "start_chord");
			gtk_text_buffer_delete_mark_by_name(t_buffer_editor, "end_chord");
		}
	}
	else 
	{
		return -1;	
	}

	return 0;
}

gint chord_down(void)
{
	GtkTextIter ch_1;
	GtkTextIter ch_2;
	GtkTextIter match_end;
	GtkTextIter match_start;		
	GtkTextIter start;
	
	GtkTextMark *start_chord;
	GtkTextMark *end_chord;
	
	gchar *chord;
	gchar *accidental;
	
	gint i;	
	
	gtk_text_buffer_get_iter_at_offset(t_buffer_editor, &start, pos_1);	

	if(gtk_text_iter_forward_search(&start, "[", 1,
	                                &match_start, &match_end, NULL))
	{
		// Get position after first instance of "[". If not it will keep looping 
		// on the first instance. 
		pos_1 = gtk_text_iter_get_offset(&match_end);	
		
		gtk_text_buffer_create_mark(t_buffer_editor, "start_chord", &match_start, FALSE);
		gtk_text_buffer_create_mark(t_buffer_editor, "end_chord", &match_end, FALSE);
		
		start_chord = gtk_text_buffer_get_mark(t_buffer_editor, "start_chord");		
		end_chord = gtk_text_buffer_get_mark(t_buffer_editor, "end_chord");
		
		gtk_text_buffer_get_iter_at_mark(t_buffer_editor, &ch_1, start_chord);
		gtk_text_buffer_get_iter_at_mark(t_buffer_editor, &ch_2, end_chord);		
				
		gtk_text_iter_forward_chars(&ch_1, 2);
		gtk_text_iter_forward_chars(&ch_2, 2);
		
		accidental = gtk_text_iter_get_slice(&ch_1, &ch_2);
		 
		if(((strcmp(accidental, "b")) == 0) ||
		   ((strcmp(accidental, "#")) == 0)) 
		{
			gtk_text_iter_backward_chars(&ch_1, 1);
			
			chord = gtk_text_iter_get_slice(&ch_1, &ch_2);
			
			if((strcmp(accidental, "b")) == 0)
			{	
				for(i = 0; i <= 11; i++)
				{				
					if((strcmp(chord, note_flats[i])) == 0)
					{
						break;				
					}
				}
			}
			else if((strcmp(accidental, "#")) == 0)
			{
				for(i = 0; i <= 11; i++)
				{				
					if((strcmp(chord, note_sharps[i])) == 0)
					{
						break;				
					}
				}			
			}
		
			gtk_text_buffer_place_cursor(t_buffer_editor, &ch_1);	
			
			gtk_text_buffer_select_range(t_buffer_editor, &ch_1, &ch_2);
			
			gtk_text_buffer_delete_selection(t_buffer_editor, FALSE, TRUE);
			
			gtk_text_buffer_insert_at_cursor(t_buffer_editor, note_flats[i - 1], -1);	
			
			g_free(chord);	
			g_free(accidental);
			
			gtk_text_buffer_delete_mark_by_name(t_buffer_editor, "start_chord");
			gtk_text_buffer_delete_mark_by_name(t_buffer_editor, "end_chord");			
		}		
		else 
		{
			gtk_text_iter_backward_chars(&ch_1, 1);
			gtk_text_iter_backward_chars(&ch_2, 1);	
			
			chord = gtk_text_iter_get_slice(&ch_1, &ch_2);
						
			for(i = 0; i <= 11; i++)
			{				
				if((strcmp(chord, note_flats[i])) == 0)
				{
					break;				
				}
			}	
			
			gtk_text_buffer_place_cursor(t_buffer_editor, &ch_1);
			
			gtk_text_buffer_select_range(t_buffer_editor, &ch_1, &ch_2);
			
			gtk_text_buffer_delete_selection(t_buffer_editor, FALSE, TRUE);
			
			if((strcmp(note_sharps[i], "A")) != 0)
			{			
				gtk_text_buffer_insert_at_cursor(t_buffer_editor, note_flats[i - 1], -1);
			}
			else 
			{
				gtk_text_buffer_insert_at_cursor(t_buffer_editor, note_flats[11], -1);
			}
						
			g_free(chord);
			g_free(accidental);
			
			gtk_text_buffer_delete_mark_by_name(t_buffer_editor, "start_chord");
			gtk_text_buffer_delete_mark_by_name(t_buffer_editor, "end_chord");
		}
	}
	else 
	{
		return -1;	
	}

	return 0;
}
/*---------------------------------------------------------------------------*/
void transpose_up(GtkWidget *button, gpointer data)
{	
	gchar *chord;
	gint i;	
	
	// Initializes pos. 
	pos_1 = 0;	                            
	pos_2 = 0;
	chord = gtk_editable_get_chars(GTK_EDITABLE(entry_key), 0, -1);	
	    
	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(button_5)) == TRUE)
	{                        
		for(i = 0; i == 0;)
		{
			i = chord_up();	
		}
	}
	
	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(button_5)) == TRUE)
	{                        
		for(i = 0; i == 0;)
		{
			i = slash_chord_up();	
		}
	}		
	
	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(button_5)) == TRUE)
	{	
		for(i = 0; i <= 11; i++)
		{				
			if((strcmp(chord, note_sharps[i])) == 0)
			{
				break;				
			}
		}

		if(i > 11)
		{
			for(i = 0; i <= 11; i++)
			{				
				if((strcmp(chord, note_flats[i])) == 0)
				{
					break;				
				}
			}		
		}	
	
		if((strcmp(note_sharps[i], "G#")) != 0)
		{			
			gtk_entry_set_text(GTK_ENTRY(entry_key), note_sharps[i + 1]);
		}
		else 
		{
			gtk_entry_set_text(GTK_ENTRY(entry_key), note_sharps[0]);
		}
	
		g_free(chord);
	}
}

void transpose_down(GtkWidget *button, gpointer data)
{
	gchar *chord;
	gint i;
	
	pos_1 = 0;
	pos_2 = 0;	                                
	chord = gtk_editable_get_chars(GTK_EDITABLE(entry_key), 0, -1);	
	
	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(button_5)) == TRUE)
	{	
		for(i = 0; i == 0;)
		{
			i = chord_down();	
		}
	}

	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(button_5)) == TRUE)
	{	
		for(i = 0; i == 0;)
		{
			i = slash_chord_down();	
		}
	}

	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(button_5)) == TRUE)
	{	
		for(i = 0; i <= 11; i++)
		{				
			if((strcmp(chord, note_sharps[i])) == 0)
			{
				break;				
			}
		}

		if(i > 11)
		{
			for(i = 0; i <= 11; i++)
			{				
				if((strcmp(chord, note_flats[i])) == 0)
				{
					break;				
				}
			}		
		}	
	
		if((strcmp(note_sharps[i], "A")) != 0)
		{			
			gtk_entry_set_text(GTK_ENTRY(entry_key), note_flats[i - 1]);
		}
		else 
		{
			gtk_entry_set_text(GTK_ENTRY(entry_key), note_flats[11]);
		}
	
		g_free(chord);
	}
}