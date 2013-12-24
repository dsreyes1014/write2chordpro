// Author: Andrew Reyes
// Date: 12-18-2013

#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>

#include "transpose.h"
#include "editor.h"

gchar *noteSharps[] = {"A", "A#", "B", 
                       "C", "C#", "D", 
                       "D#", "E", "F", 
                       "F#", "G", "G#"};
                 
gchar *noteFlats[] = {"A", "Bb", "B",
                      "C", "Db", "D",
                      "Eb", "E", "F",
                      "Gb", "G", "Ab"};

gint pos1, pos2;
extern gchar songPath[];
extern GtkTextBuffer *tBufferEditor;
extern GtkWidget *tViewEditor, *button5, *entryKey;
extern GtkEntryBuffer *entryBuffer;

gint slashChordDown(void)
{
	GtkTextIter ch1;
	GtkTextIter ch2;
	GtkTextIter matchEnd;
	GtkTextIter matchStart;		
	GtkTextIter start;
	
	GtkTextMark *startChord;
	GtkTextMark *endChord;
	
	gchar *chord;
	gchar *accidental;
	
	gint i;	
	
	gtk_text_buffer_get_iter_at_offset(tBufferEditor, &start, pos2);	
	
	// This will find any slash chord and transpose it as well.
	if(gtk_text_iter_forward_search(&start, "/", 1,
	                                &matchStart, &matchEnd, NULL))
	{
		// Get position after first instance of "[". If not it will keep looping 
		// on the first instance. 
		pos2 = gtk_text_iter_get_offset(&matchEnd);	
		
		gtk_text_buffer_create_mark(tBufferEditor, "startChord", &matchStart, FALSE);
		gtk_text_buffer_create_mark(tBufferEditor, "endChord", &matchEnd, FALSE);
		
		startChord = gtk_text_buffer_get_mark(tBufferEditor, "startChord");		
		endChord = gtk_text_buffer_get_mark(tBufferEditor, "endChord");
		
		gtk_text_buffer_get_iter_at_mark(tBufferEditor, &ch1, startChord);
		gtk_text_buffer_get_iter_at_mark(tBufferEditor, &ch2, endChord);		
				
		gtk_text_iter_forward_chars(&ch1, 2);
		gtk_text_iter_forward_chars(&ch2, 2);
		
		accidental = gtk_text_iter_get_slice(&ch1, &ch2);
		 
		if(((strcmp(accidental, "b")) == 0) ||
		   ((strcmp(accidental, "#")) == 0)) 
		{
			gtk_text_iter_backward_chars(&ch1, 1);
			
			chord = gtk_text_iter_get_slice(&ch1, &ch2);
			
			if((strcmp(accidental, "b")) == 0)
			{	
				for(i = 0; i <= 11; i++)
				{				
					if((strcmp(chord, noteFlats[i])) == 0)
					{
						break;				
					}
				}
			}
			else if((strcmp(accidental, "#")) == 0)
			{
				for(i = 0; i <= 11; i++)
				{				
					if((strcmp(chord, noteSharps[i])) == 0)
					{
						break;				
					}
				}			
			}
		
			gtk_text_buffer_place_cursor(tBufferEditor, &ch1);	
			
			gtk_text_buffer_select_range(tBufferEditor, &ch1, &ch2);
			
			gtk_text_buffer_delete_selection(tBufferEditor, FALSE, TRUE);
			
			gtk_text_buffer_insert_at_cursor(tBufferEditor, noteFlats[i - 1], -1);	
			
			g_free(chord);	
			g_free(accidental);
			
			gtk_text_buffer_delete_mark_by_name(tBufferEditor, "startChord");
			gtk_text_buffer_delete_mark_by_name(tBufferEditor, "endChord");			
		}		
		else 
		{
			gtk_text_iter_backward_chars(&ch1, 1);
			gtk_text_iter_backward_chars(&ch2, 1);	
			
			chord = gtk_text_iter_get_slice(&ch1, &ch2);
			
			for(i = 0; i <= 11; i++)
			{				
				if((strcmp(chord, noteFlats[i])) == 0)
				{
					break;				
				}
			}	
			
			gtk_text_buffer_place_cursor(tBufferEditor, &ch1);
			
			gtk_text_buffer_select_range(tBufferEditor, &ch1, &ch2);
			
			gtk_text_buffer_delete_selection(tBufferEditor, FALSE, TRUE);
			
			if((strcmp(noteSharps[i], "A")) != 0)
			{			
				gtk_text_buffer_insert_at_cursor(tBufferEditor, noteFlats[i - 1], -1);
			}
			else 
			{
				gtk_text_buffer_insert_at_cursor(tBufferEditor, noteFlats[11], -1);
			}
			
			g_free(chord);
			g_free(accidental);
			
			gtk_text_buffer_delete_mark_by_name(tBufferEditor, "startChord");
			gtk_text_buffer_delete_mark_by_name(tBufferEditor, "endChord");
		}
	}
	else 
	{
		return -1;	
	}

	return 0;
}

gint slashChordUp(void)
{
	GtkTextIter ch1;
	GtkTextIter ch2;
	GtkTextIter start;	
	GtkTextIter matchEnd;
	GtkTextIter matchStart;		
	
	GtkTextMark *endChord;
	GtkTextMark *startChord;
	
	gchar *chord;
	gchar *accidental;
	
	gint i;
//-----------------------------------------------------------------------------	
	gtk_text_buffer_get_iter_at_offset(tBufferEditor, &start, pos2);	
	
	// This will find any slash chord and transpose it as well.
	if(gtk_text_iter_forward_search(&start, "/", 1,
	                                &matchStart, &matchEnd, NULL))
	{
		pos2 = gtk_text_iter_get_offset(&matchEnd);	
		
		gtk_text_buffer_create_mark(tBufferEditor, "startChord",
		                            &matchStart, FALSE);
		                            
		gtk_text_buffer_create_mark(tBufferEditor, "endChord",
		                            &matchEnd, FALSE);
		
		startChord = gtk_text_buffer_get_mark(tBufferEditor, "startChord");		
		endChord = gtk_text_buffer_get_mark(tBufferEditor, "endChord");
		
		gtk_text_buffer_get_iter_at_mark(tBufferEditor, &ch1, startChord);
		gtk_text_buffer_get_iter_at_mark(tBufferEditor, &ch2, endChord);		
				
		gtk_text_iter_forward_chars(&ch1, 2);
		gtk_text_iter_forward_chars(&ch2, 2);
		
		accidental = gtk_text_iter_get_slice(&ch1, &ch2);
		 
		if(((strcmp(accidental, "b")) == 0) ||
		   ((strcmp(accidental, "#")) == 0)) 
		{
			gtk_text_iter_backward_chars(&ch1, 1);
			
			chord = gtk_text_iter_get_slice(&ch1, &ch2);
			
			if((strcmp(accidental, "b")) == 0)
			{	
				for(i = 0; i <= 11; i++)
				{				
					if((strcmp(chord, noteFlats[i])) == 0)
					{
						break;				
					}
				}
			}
			else if((strcmp(accidental, "#")) == 0)
			{
				for(i = 0; i <= 11; i++)
				{				
					if((strcmp(chord, noteSharps[i])) == 0)
					{
						break;				
					}
				}			
			}
		
			gtk_text_buffer_place_cursor(tBufferEditor, &ch1);	
			
			gtk_text_buffer_select_range(tBufferEditor, &ch1, &ch2);
		
			gtk_text_buffer_delete_selection(tBufferEditor, FALSE, TRUE);
			
			if((strcmp(noteSharps[i], "G#")) != 0)
			{			
				gtk_text_buffer_insert_at_cursor(tBufferEditor, noteSharps[i + 1], -1);
			}
			else 
			{
				gtk_text_buffer_insert_at_cursor(tBufferEditor, noteSharps[0], -1);
			}
			
			g_free(chord);	
			g_free(accidental);
			
			gtk_text_buffer_delete_mark_by_name(tBufferEditor, "startChord");
			gtk_text_buffer_delete_mark_by_name(tBufferEditor, "endChord");			
		}		
		else 
		{
			gtk_text_iter_backward_chars(&ch1, 1);
			gtk_text_iter_backward_chars(&ch2, 1);	
			
			chord = gtk_text_iter_get_slice(&ch1, &ch2);
						
			for(i = 0; i <= 11; i++)
			{				
				if((strcmp(chord, noteSharps[i])) == 0)
				{
					break;				
				}
			}	
			
			gtk_text_buffer_place_cursor(tBufferEditor, &ch1);
			
			gtk_text_buffer_select_range(tBufferEditor, &ch1, &ch2);
			
			gtk_text_buffer_delete_selection(tBufferEditor, FALSE, TRUE);
			
			gtk_text_buffer_insert_at_cursor(tBufferEditor, noteSharps[i + 1], -1);	
			
			g_free(chord);
			g_free(accidental);
			
			gtk_text_buffer_delete_mark_by_name(tBufferEditor, "startChord");
			gtk_text_buffer_delete_mark_by_name(tBufferEditor, "endChord");
		}
	}
	else 
	{
		return -1;	
	}

	return 0;
}

gint chordUp(void)
{		
	GtkTextIter ch1;
	GtkTextIter ch2;
	GtkTextIter matchEnd;
	GtkTextIter matchStart;		
	GtkTextIter start;
	
	GtkTextMark *startChord;
	GtkTextMark *endChord;
	
	gchar *chord;
	gchar *accidental;
	
	gint i;	
	
	gtk_text_buffer_get_iter_at_offset(tBufferEditor, &start, pos1);	

	if(gtk_text_iter_forward_search(&start, "[", 1,
	                                &matchStart, &matchEnd, NULL))
	{
		pos1 = gtk_text_iter_get_offset(&matchEnd);	
		
		gtk_text_buffer_create_mark(tBufferEditor, "startChord", &matchStart, FALSE);
		gtk_text_buffer_create_mark(tBufferEditor, "endChord", &matchEnd, FALSE);
		
		startChord = gtk_text_buffer_get_mark(tBufferEditor, "startChord");		
		endChord = gtk_text_buffer_get_mark(tBufferEditor, "endChord");
		
		gtk_text_buffer_get_iter_at_mark(tBufferEditor, &ch1, startChord);
		gtk_text_buffer_get_iter_at_mark(tBufferEditor, &ch2, endChord);		
				
		gtk_text_iter_forward_chars(&ch1, 2);
		gtk_text_iter_forward_chars(&ch2, 2);
		
		accidental = gtk_text_iter_get_slice(&ch1, &ch2);
		 
		if(((strcmp(accidental, "b")) == 0) ||
		   ((strcmp(accidental, "#")) == 0)) 
		{
			gtk_text_iter_backward_chars(&ch1, 1);
			
			chord = gtk_text_iter_get_slice(&ch1, &ch2);
			
			if((strcmp(accidental, "b")) == 0)
			{	
				for(i = 0; i <= 11; i++)
				{				
					if((strcmp(chord, noteFlats[i])) == 0)
					{
						break;				
					}
				}
			}
			else if((strcmp(accidental, "#")) == 0)
			{
				for(i = 0; i <= 11; i++)
				{				
					if((strcmp(chord, noteSharps[i])) == 0)
					{
						break;				
					}
				}			
			}
		
			gtk_text_buffer_place_cursor(tBufferEditor, &ch1);	
			
			gtk_text_buffer_select_range(tBufferEditor, &ch1, &ch2);
			
			gtk_text_buffer_delete_selection(tBufferEditor, FALSE, TRUE);
			
			if((strcmp(noteSharps[i], "G#")) != 0)
			{			
				gtk_text_buffer_insert_at_cursor(tBufferEditor, noteSharps[i + 1], -1);
			}
			else 
			{
				gtk_text_buffer_insert_at_cursor(tBufferEditor, noteSharps[0], -1);
			}
					
			g_free(chord);	
			g_free(accidental);
			
			gtk_text_buffer_delete_mark_by_name(tBufferEditor, "startChord");
			gtk_text_buffer_delete_mark_by_name(tBufferEditor, "endChord");			
		}		
		else 
		{
			gtk_text_iter_backward_chars(&ch1, 1);
			gtk_text_iter_backward_chars(&ch2, 1);	
			
			chord = gtk_text_iter_get_slice(&ch1, &ch2);
			
			for(i = 0; i <= 11; i++)
			{				
				if((strcmp(chord, noteSharps[i])) == 0)
				{
					break;				
				}
			}	
			
			gtk_text_buffer_place_cursor(tBufferEditor, &ch1);
			
			gtk_text_buffer_select_range(tBufferEditor, &ch1, &ch2);
			
			gtk_text_buffer_delete_selection(tBufferEditor, FALSE, TRUE);
			
			gtk_text_buffer_insert_at_cursor(tBufferEditor, noteSharps[i + 1], -1);
						
			g_free(chord);
			g_free(accidental);
			
			gtk_text_buffer_delete_mark_by_name(tBufferEditor, "startChord");
			gtk_text_buffer_delete_mark_by_name(tBufferEditor, "endChord");
		}
	}
	else 
	{
		return -1;	
	}

	return 0;
}

gint chordDown(void)
{
	GtkTextIter ch1;
	GtkTextIter ch2;
	GtkTextIter matchEnd;
	GtkTextIter matchStart;		
	GtkTextIter start;
	
	GtkTextMark *startChord;
	GtkTextMark *endChord;
	
	gchar *chord;
	gchar *accidental;
	
	gint i;	
	
	gtk_text_buffer_get_iter_at_offset(tBufferEditor, &start, pos1);	

	if(gtk_text_iter_forward_search(&start, "[", 1,
	                                &matchStart, &matchEnd, NULL))
	{
		// Get position after first instance of "[". If not it will keep looping 
		// on the first instance. 
		pos1 = gtk_text_iter_get_offset(&matchEnd);	
		
		gtk_text_buffer_create_mark(tBufferEditor, "startChord", &matchStart, FALSE);
		gtk_text_buffer_create_mark(tBufferEditor, "endChord", &matchEnd, FALSE);
		
		startChord = gtk_text_buffer_get_mark(tBufferEditor, "startChord");		
		endChord = gtk_text_buffer_get_mark(tBufferEditor, "endChord");
		
		gtk_text_buffer_get_iter_at_mark(tBufferEditor, &ch1, startChord);
		gtk_text_buffer_get_iter_at_mark(tBufferEditor, &ch2, endChord);		
				
		gtk_text_iter_forward_chars(&ch1, 2);
		gtk_text_iter_forward_chars(&ch2, 2);
		
		accidental = gtk_text_iter_get_slice(&ch1, &ch2);
		 
		if(((strcmp(accidental, "b")) == 0) ||
		   ((strcmp(accidental, "#")) == 0)) 
		{
			gtk_text_iter_backward_chars(&ch1, 1);
			
			chord = gtk_text_iter_get_slice(&ch1, &ch2);
			
			if((strcmp(accidental, "b")) == 0)
			{	
				for(i = 0; i <= 11; i++)
				{				
					if((strcmp(chord, noteFlats[i])) == 0)
					{
						break;				
					}
				}
			}
			else if((strcmp(accidental, "#")) == 0)
			{
				for(i = 0; i <= 11; i++)
				{				
					if((strcmp(chord, noteSharps[i])) == 0)
					{
						break;				
					}
				}			
			}
		
			gtk_text_buffer_place_cursor(tBufferEditor, &ch1);	
			
			gtk_text_buffer_select_range(tBufferEditor, &ch1, &ch2);
			
			gtk_text_buffer_delete_selection(tBufferEditor, FALSE, TRUE);
			
			gtk_text_buffer_insert_at_cursor(tBufferEditor, noteFlats[i - 1], -1);	
			
			g_free(chord);	
			g_free(accidental);
			
			gtk_text_buffer_delete_mark_by_name(tBufferEditor, "startChord");
			gtk_text_buffer_delete_mark_by_name(tBufferEditor, "endChord");			
		}		
		else 
		{
			gtk_text_iter_backward_chars(&ch1, 1);
			gtk_text_iter_backward_chars(&ch2, 1);	
			
			chord = gtk_text_iter_get_slice(&ch1, &ch2);
						
			for(i = 0; i <= 11; i++)
			{				
				if((strcmp(chord, noteFlats[i])) == 0)
				{
					break;				
				}
			}	
			
			gtk_text_buffer_place_cursor(tBufferEditor, &ch1);
			
			gtk_text_buffer_select_range(tBufferEditor, &ch1, &ch2);
			
			gtk_text_buffer_delete_selection(tBufferEditor, FALSE, TRUE);
			
			if((strcmp(noteSharps[i], "A")) != 0)
			{			
				gtk_text_buffer_insert_at_cursor(tBufferEditor, noteFlats[i - 1], -1);
			}
			else 
			{
				gtk_text_buffer_insert_at_cursor(tBufferEditor, noteFlats[11], -1);
			}
						
			g_free(chord);
			g_free(accidental);
			
			gtk_text_buffer_delete_mark_by_name(tBufferEditor, "startChord");
			gtk_text_buffer_delete_mark_by_name(tBufferEditor, "endChord");
		}
	}
	else 
	{
		return -1;	
	}

	return 0;
}
/*---------------------------------------------------------------------------*/
void transposeUp(GtkWidget *button, gpointer data)
{	
	gchar *chord;
	gint i;	
	
	// Initializes pos. 
	pos1 = 0;	                            
	pos2 = 0;
	chord = gtk_editable_get_chars(GTK_EDITABLE(entryKey), 0, -1);	
	    
	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(button5)) == TRUE)
	{                        
		for(i = 0; i == 0;)
		{
			i = chordUp();	
		}
	}
	
	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(button5)) == TRUE)
	{                        
		for(i = 0; i == 0;)
		{
			i = slashChordUp();	
		}
	}		
	
	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(button5)) == TRUE)
	{	
		for(i = 0; i <= 11; i++)
		{				
			if((strcmp(chord, noteSharps[i])) == 0)
			{
				break;				
			}
		}

		if(i > 11)
		{
			for(i = 0; i <= 11; i++)
			{				
				if((strcmp(chord, noteFlats[i])) == 0)
				{
					break;				
				}
			}		
		}	
	
		if((strcmp(noteSharps[i], "G#")) != 0)
		{			
			gtk_entry_set_text(GTK_ENTRY(entryKey), noteSharps[i + 1]);
		}
		else 
		{
			gtk_entry_set_text(GTK_ENTRY(entryKey), noteSharps[0]);
		}
	
		g_free(chord);
	}
}

void transposeDown(GtkWidget *button, gpointer data)
{
	gchar *chord;
	gint i;
	
	pos1 = 0;
	pos2 = 0;	                                
	chord = gtk_editable_get_chars(GTK_EDITABLE(entryKey), 0, -1);	
	
	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(button5)) == TRUE)
	{	
		for(i = 0; i == 0;)
		{
			i = chordDown();	
		}
	}

	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(button5)) == TRUE)
	{	
		for(i = 0; i == 0;)
		{
			i = slashChordDown();	
		}
	}

	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(button5)) == TRUE)
	{	
		for(i = 0; i <= 11; i++)
		{				
			if((strcmp(chord, noteSharps[i])) == 0)
			{
				break;				
			}
		}

		if(i > 11)
		{
			for(i = 0; i <= 11; i++)
			{				
				if((strcmp(chord, noteFlats[i])) == 0)
				{
					break;				
				}
			}		
		}	
	
		if((strcmp(noteSharps[i], "A")) != 0)
		{			
			gtk_entry_set_text(GTK_ENTRY(entryKey), noteFlats[i - 1]);
		}
		else 
		{
			gtk_entry_set_text(GTK_ENTRY(entryKey), noteFlats[11]);
		}
	
		g_free(chord);
	}
}