// Author: Andrew Reye
// Date Last Modified: 11-29-2013

#include <gtk/gtk.h>
#include <stdio.h>

#include "display.h"
#include "songs.h"

void display(GtkTextBuffer *buffer, gchar *view, gint number)
{	
	GtkTextTag *tag;
	GtkTextIter startOfLine, endOfLine, ch, matchStart, matchEnd;	
	gint lineDisplay;	
	
	gtk_text_buffer_set_text(buffer, view, number);	
	
	// Sets these iters to a range on line 0 to delete and set desired visible text.
	gtk_text_buffer_get_iter_at_line(buffer, &startOfLine, 0);
	gtk_text_buffer_get_iter_at_line_offset(buffer, &ch, 0, 8);
	gtk_text_buffer_delete(buffer, &startOfLine, &ch);		
			
	// Deletes last character of line 0 to output just the title. 
	gtk_text_buffer_get_iter_at_line(buffer, &endOfLine, 0);
	gtk_text_iter_forward_to_line_end(&endOfLine);
	gtk_text_buffer_backspace(buffer, &endOfLine, FALSE, TRUE);
			
	// Sets attributes for Title (line 0).			
	gtk_text_buffer_get_iter_at_line(buffer, &startOfLine, 0);
	gtk_text_buffer_get_iter_at_line(buffer, &endOfLine, 0);
	gtk_text_iter_forward_to_line_end(&endOfLine);			
			
	tag = gtk_text_buffer_create_tag(buffer, 
	  										   NULL, "weight", "850",
												"justification", GTK_JUSTIFY_CENTER, 
												"font", "30", NULL);
												  
	gtk_text_buffer_apply_tag(buffer, tag, &startOfLine, &endOfLine);
			
	// Sets these iters to a range on line 1 to delete and set desired visible text. 				
	gtk_text_buffer_get_iter_at_line(buffer, &startOfLine, 1);
	gtk_text_buffer_get_iter_at_line_offset(buffer, &ch, 1, 11);
	gtk_text_buffer_delete(buffer, &startOfLine, &ch);			
			
	// Deletes last character of line 1 to output just the artist.
	gtk_text_buffer_get_iter_at_line(buffer, &endOfLine, 1);
	gtk_text_iter_forward_to_line_end(&endOfLine);
	gtk_text_buffer_backspace(buffer, &endOfLine, FALSE, TRUE);	
			
	// Inserts text before artist with attributes.
	tag = gtk_text_buffer_create_tag(buffer, NULL, "font", "12", 
		    								 "justification", GTK_JUSTIFY_CENTER, NULL);
	gtk_text_buffer_get_iter_at_line(buffer, &startOfLine, 1);
	gtk_text_buffer_insert_with_tags(buffer, &startOfLine, "by: ", 4, tag, NULL);
			
	// Sets attributes for Artist (line 1).
	gtk_text_buffer_get_iter_at_line_offset(buffer, &startOfLine, 1, 4);
	gtk_text_buffer_get_iter_at_line(buffer, &endOfLine, 1);
	gtk_text_iter_forward_to_line_end(&endOfLine);			
	tag = gtk_text_buffer_create_tag(buffer, 
	  										   NULL, "weight", "600",
												"weight-set", TRUE, 
												"font", "italic 18", NULL);
												  
	gtk_text_buffer_apply_tag(buffer, tag, &startOfLine, &endOfLine);	
			
	// This section is for setting the attributes of the text
	// 'Verse:', 'Chorus:'etc...			
	gtk_text_buffer_get_start_iter(buffer, &startOfLine);		
			
	if(gtk_text_iter_forward_search(&startOfLine, "Verse:", 
	   									  1, 
											  &matchStart, &matchEnd, NULL))
	{
		tag = gtk_text_buffer_create_tag(buffer, NULL, "font", "italic 12", NULL);
		gtk_text_buffer_apply_tag(buffer, tag, &matchStart, &matchEnd);			
	}
				
	if(gtk_text_iter_forward_search(&startOfLine, "Chorus:", 
		 									  1, 
											  &matchStart, &matchEnd, NULL))
	{
		tag = gtk_text_buffer_create_tag(buffer, NULL, "font", "italic 12", NULL);
		gtk_text_buffer_apply_tag(buffer, tag, &matchStart, &matchEnd);			
	}
		
			/*if(gtk_text_iter_forward_search(&matchEnd, "Chorus:", 
											1, 
											&matchStart, &matchEnd, NULL))
			{	
				tag = gtk_text_buffer_create_tag(tBufferDisplay, NULL, "font", "italic 12", NULL);
				gtk_text_buffer_apply_tag(tBufferDisplay, tag, &matchStart, &matchEnd);			
			}*/
						
	if(gtk_text_iter_forward_search(&startOfLine, "Intro:", 
											  1, 
											  &matchStart, &matchEnd, NULL))
	{
		tag = gtk_text_buffer_create_tag(buffer, NULL, "font", "italic 12", NULL);
		gtk_text_buffer_apply_tag(buffer, tag, &matchStart, &matchEnd);			
	}
					
	if(gtk_text_iter_forward_search(&startOfLine, "Bridge:", 
											  1, 
											  &matchStart, &matchEnd, NULL))
	{
		tag = gtk_text_buffer_create_tag(buffer, NULL, "font", "italic 12", NULL);
		gtk_text_buffer_apply_tag(buffer, tag, &matchStart, &matchEnd);			
	}
					
	if(gtk_text_iter_forward_search(&startOfLine, "Verse 1:", 
											  1, 
											  &matchStart, &matchEnd, NULL))
	{
		tag = gtk_text_buffer_create_tag(buffer, NULL, "font", "italic 12", NULL);
		gtk_text_buffer_apply_tag(buffer, tag, &matchStart, &matchEnd);			
	}
					
	if(gtk_text_iter_forward_search(&startOfLine, "Verse 3:", 
											  1, 
											  &matchStart, &matchEnd, NULL))
	{
		tag = gtk_text_buffer_create_tag(buffer, NULL, "font", "italic 12", NULL);
		gtk_text_buffer_apply_tag(buffer, tag, &matchStart, &matchEnd);			
	} 						
			
			//g_print("Chord: %s\n", chord);
			//g_print("Number of \'[\': %d\n", i);
			
	lineDisplay = gtk_text_buffer_get_line_count(buffer);
			
	g_print("Line count for display is: %d\n", lineDisplay);
}