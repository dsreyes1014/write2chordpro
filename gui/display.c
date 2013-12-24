// Author: Andrew Reye
// Date Last Modified: 11-29-2013

#include <gtk/gtk.h>
#include <stdio.h>

#include "display.h"
#include "editor.h"

gint lineNumC, lineCountC;

extern GtkWidget *entryKey;
extern GtkWidget *entryTitle;
extern GtkWidget *entryArtist;

extern GtkTextBuffer *tBufferEditor;
//-----------------------------------------------------------------------------
gint setChordPosition(GtkWidget *tView, GtkTextBuffer *buffer)
{
	GtkTextTag *tag;	

	GtkTextMark *endChord;
	GtkTextMark *startChord;	

	GtkTextIter ch;	
	GtkTextIter chordS;
	GtkTextIter chordE;
	GtkTextIter matchEnd;
	GtkTextIter matchStart;	
	GtkTextIter startOfLine;
	
	GtkClipboard *clipboard;
		
	gint lineNum1;
	gint lineNum2;
	gint lineCountV;	
	gint lineOffset1;
	gint lineOffset2;

	lineCountV = gtk_text_buffer_get_line_count(buffer);
	clipboard = gtk_clipboard_get(GDK_SELECTION_CLIPBOARD);	
	
	gtk_text_buffer_get_start_iter(buffer, &startOfLine);
	
	if(gtk_text_iter_forward_search(&startOfLine, "[", 1, 
									&matchStart, &matchEnd, NULL))
	{		
		gtk_text_buffer_create_mark(buffer, "startChord", &matchStart, FALSE);
		
		startChord = gtk_text_buffer_get_mark(buffer, "startChord");
	}
	else 
	{
		return -1;
	}
	
	if(gtk_text_iter_forward_search(&startOfLine, "]", 1, 
									&matchStart, &matchEnd, NULL))		
	{		
		gtk_text_buffer_create_mark(buffer, "endChord", &matchEnd, FALSE);
		
		endChord = gtk_text_buffer_get_mark(buffer, "endChord");	
	}	
	else 
	{
		return -1;	
	}

	// Initializes iters at mark.
	gtk_text_buffer_get_iter_at_mark(buffer, &chordS, startChord);
	gtk_text_buffer_get_iter_at_mark(buffer, &chordE, endChord);
	
	// Get line and line offset of iter. If we just obtain the offset 
	// within buffer then chords will not format as desired.
	lineNum1 = gtk_text_iter_get_line(&chordS);
	lineOffset1 = gtk_text_iter_get_line_index(&chordS);	
	lineNum2 = gtk_text_iter_get_line(&chordE);
	lineOffset2 = gtk_text_iter_get_line_index(&chordE);
	
	// This returns with error if end bracket does not have a 
	// matching start bracket.
	if(lineOffset1 > lineOffset2)
	{
		return -1;	
	}
	
	//g_print("Lineoffset of start:end bracket:\n%d\n%d\n", lineOffset1, lineOffset2);
		
	// If chord found is found more than two lines down
	// refresh global values of 'lineCountV' and lineNumC. 
	if(lineNum1 > (lineNumC + 1))	
	{
		lineNumC = lineNum1;
		lineCountC = lineCountV;
	}
	
	// Copy, cut, and add tags to the section between the marks.
	gtk_text_buffer_select_range(buffer, &chordS, &chordE);
	tag = gtk_text_buffer_create_tag(buffer, NULL, "background", "gold",
									 "weight", "500", 
									 "foreground-gdk", "black3", NULL);
	gtk_text_buffer_apply_tag(buffer, tag, &chordS, &chordE);
	gtk_text_buffer_cut_clipboard(buffer, clipboard, TRUE);
	
	// This finds first chord of line.
	if(lineCountV == lineCountC) 
	{	
		gtk_text_buffer_get_iter_at_line(buffer, &startOfLine, lineNum1);
		gtk_text_buffer_insert(buffer, &startOfLine, "\n", -1);
	}

	// This finds the rest of the chords on the same line as the first. 
	if(lineNum1 == (lineNumC + 1))
	{
		lineNum1 = lineNum1 - 1;		
		lineNum2 = lineNum2 - 1;
	}

	gtk_text_buffer_get_iter_at_line(buffer, &ch, lineNum1);
	
	// Insert 110 blank spaces so we can insert chords at higher offsets than 0.
	// GtkTextBuffer does not allow us to insert past a newline character
	// so we move it with spaces to allow us to place chords at offsets 
	// past a newline character.
	if(gtk_text_iter_get_char(&ch) == '\n')
	{	
		gtk_text_buffer_insert(buffer, &ch, 
	    "                                                                                                              ",
							    -1);		
	}
	
	// Place iter at the same offset one line above.
	gtk_text_buffer_get_iter_at_line_index(buffer, &ch, lineNum1, lineOffset1);
	
	//g_print("Position after cut: %d\n", lineOffset1);
	gtk_text_buffer_paste_clipboard(buffer, clipboard, &ch, TRUE);	
	
	gtk_text_buffer_get_iter_at_line_offset(buffer, &ch, lineNum1, lineOffset2);
	// Deletes the end bracket.	
	gtk_text_buffer_backspace(buffer, &ch, FALSE, TRUE);
	gtk_text_buffer_get_iter_at_line_offset(buffer, &ch, lineNum1, lineOffset1 +1);
	// Deletes the start bracket. 	
	gtk_text_buffer_backspace(buffer, &ch, FALSE, TRUE);
	gtk_text_buffer_delete_mark_by_name(buffer, "startChord");
	gtk_text_buffer_delete_mark_by_name(buffer, "endChord");
	
	return 0;
}
//-----------------------------------------------------------------------------
void display(GtkTextBuffer *buffer, GtkWidget *tView)
{		
	GtkTextTag *tag;
	
	GtkTextIter end;
	GtkTextIter start;
	GtkTextIter matchEnd;
	GtkTextIter matchStart;

	gint i; 
	
	gchar *key;
	gchar *body;
	gchar *title;	
	gchar *artist;
	
	const gchar *songSection[] = {"Verse:", "Verse 1", "Verse 2:",
								  "Verse 3:","Bridge:", "Bridge 1:",
								  "Bridge 2:", "Bridge 3:", "Intro:",
								  "End:", "PreChorus:", "Verso:"
								  "Coro:"};
								  
//-----------------------------------------------------------------------------				
	gtk_text_buffer_get_start_iter(buffer, &start);
	gtk_text_buffer_get_end_iter(buffer, &end);	
	
	gtk_text_buffer_delete(buffer, &start, &end);	
	
	gtk_text_view_set_editable(GTK_TEXT_VIEW(tView), FALSE);
//-----------------------------------------------------------------------------	
	// Sets attributes for Title (line 0).	
	title = gtk_editable_get_chars(GTK_EDITABLE(entryTitle), 0, -1);
	
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
	                                 "monospace italic 12", 
		    						 "weight-set", TRUE, 
		    						 "weight", 550, NULL);
		    						 
	gtk_text_buffer_get_iter_at_line(buffer, &start, 0);
	
	gtk_text_iter_forward_to_line_end(&start);
	
	gtk_text_buffer_place_cursor(buffer, &start);
	
	// Have to insert '\n' to create next line
	gtk_text_buffer_insert_at_cursor(buffer, "\n", -1);
	
	gtk_text_buffer_get_iter_at_line(buffer, &start, 1);
	
	gtk_text_buffer_place_cursor(buffer, &start);
	
	gtk_text_buffer_insert_at_cursor(buffer, "artist: ", -1);
	
	gtk_text_buffer_get_iter_at_line(buffer, &start, 1);
	
	gtk_text_buffer_get_iter_at_line(buffer, &end, 1);
	
	gtk_text_iter_forward_to_line_end(&end);
	
	gtk_text_buffer_apply_tag(buffer, tag, &start, &end);
//-----------------------------------------------------------------------------			
	artist = gtk_editable_get_chars(GTK_EDITABLE(entryArtist), 0, -1);	
	
	gtk_text_buffer_get_iter_at_line_offset(buffer, &start, 1, 8);
	
	gtk_text_buffer_place_cursor(buffer, &start);
	
	gtk_text_buffer_insert_at_cursor(buffer, artist, -1);
	
	g_free(artist);	
	
	// Sets attributes for Artist (line 1).
	gtk_text_buffer_get_iter_at_line_offset(buffer, &start, 1, 8);
	
	gtk_text_buffer_get_iter_at_line(buffer, &end, 1);
	
	gtk_text_iter_forward_to_line_end(&end);			
	
	tag = gtk_text_buffer_create_tag(buffer, NULL, "weight", 600,
									 "weight-set", TRUE, 
									 "font", "monospace 18", NULL);
												  
	gtk_text_buffer_apply_tag(buffer, tag, &start, &end);	
//-----------------------------------------------------------------------------	
	tag = gtk_text_buffer_create_tag(buffer, NULL, "font", 
	                                 "monospace italic 12", 
		    						 "weight", 550, NULL);
	
	gtk_text_buffer_get_iter_at_line(buffer, &start, 1);
	
	gtk_text_iter_forward_to_line_end(&start);
	
	gtk_text_buffer_place_cursor(buffer, &start);
	
	// Have to insert '\n' to create next line
	gtk_text_buffer_insert_at_cursor(buffer, "\n", -1);
	
	gtk_text_buffer_get_iter_at_line(buffer, &start, 2);
	
	gtk_text_buffer_place_cursor(buffer, &start);
	
	gtk_text_buffer_insert_at_cursor(buffer, "key: ", -1);
	
	gtk_text_buffer_get_iter_at_line(buffer, &start, 2);
	
	gtk_text_buffer_get_iter_at_line(buffer, &end, 2);
	
	gtk_text_iter_forward_to_line_end(&end);
	
	gtk_text_buffer_apply_tag(buffer, tag, &start, &end);
//-----------------------------------------------------------------------------
	key = gtk_editable_get_chars(GTK_EDITABLE(entryKey), 0, -1);
	
	gtk_text_buffer_get_iter_at_line_offset(buffer, &start, 2, 5);
	
	gtk_text_buffer_place_cursor(buffer, &start);
	
	gtk_text_buffer_insert_at_cursor(buffer, key, -1);
	
	g_free(key);	
	
	gtk_text_buffer_get_iter_at_line_offset(buffer, &start, 2, 5);
	
	gtk_text_buffer_get_iter_at_line(buffer, &end, 2);
	
	gtk_text_iter_forward_to_line_end(&end);			
	
	tag = gtk_text_buffer_create_tag(buffer, NULL, "weight", 600,
									 "weight-set", TRUE, 
									 "font", "monospace 14", NULL);
												  
	gtk_text_buffer_apply_tag(buffer, tag, &start, &end);
//-----------------------------------------------------------------------------	
	gtk_text_buffer_get_iter_at_line(buffer, &start, 2);
	
	gtk_text_iter_forward_to_line_end(&start);
	
	gtk_text_buffer_place_cursor(buffer, &start);
	
	// Have to insert '\n' to create next line
	gtk_text_buffer_insert_at_cursor(buffer, "\n\n", -1);
	
	gtk_text_buffer_get_start_iter(tBufferEditor, &start);
	gtk_text_buffer_get_end_iter(tBufferEditor, &end);	
	
	body = gtk_text_buffer_get_text(tBufferEditor, &start, &end, FALSE);
	
	gtk_text_buffer_get_iter_at_line(buffer, &start, 4);
	
	gtk_text_buffer_place_cursor(buffer, &start);
	
	gtk_text_buffer_insert_at_cursor(buffer, body, -1);
//-----------------------------------------------------------------------------
	gtk_text_buffer_get_iter_at_line(buffer, &start, 4);
	gtk_text_buffer_get_end_iter(buffer, &end);
	
	tag = gtk_text_buffer_create_tag(buffer, NULL, "font", 
	                                    "monospace", NULL);
	                                    
	gtk_text_buffer_apply_tag(buffer, tag, &start, &end);	
	
	lineCountC = gtk_text_buffer_get_line_count(buffer);
	
	gtk_text_buffer_get_start_iter(buffer, &start);	
	
	if(gtk_text_iter_forward_search(&start, "[", 1, 
								 &matchStart, &matchEnd, NULL))
	{								 
 		lineNumC = gtk_text_iter_get_line(&matchStart);
	}

	for(i = 0; i == 0;)
	{
		i = setChordPosition(tView, buffer);	
	}
//-----------------------------------------------------------------------------			
	// This section is for setting the attributes of the text
	// 'Verse:', 'Chorus:'etc...			
	gtk_text_buffer_get_start_iter(buffer, &start);
	
	for(i = 0; i < 13; i++)
	{
		if(gtk_text_iter_forward_search(&start, songSection[i],
		                                GTK_TEXT_SEARCH_CASE_INSENSITIVE,
										&matchStart, &matchEnd, NULL))
		{
			tag = gtk_text_buffer_create_tag(buffer, NULL, 
										     "font", "italic 12", 
										     "weight", 650, NULL);

			gtk_text_buffer_apply_tag(buffer, tag, &matchStart, &matchEnd);
		}	
	}		
	
	if(gtk_text_iter_forward_search(&start, "Chorus:", 
	   								GTK_TEXT_SEARCH_CASE_INSENSITIVE,
	   								&matchStart, &matchEnd, NULL))
	{
		tag = gtk_text_buffer_create_tag(buffer, NULL, 
										 "font", "italic 12", 
										 "weight", 650, NULL);

		gtk_text_buffer_apply_tag(buffer, tag, &matchStart, &matchEnd);			
	
		gtk_text_iter_forward_search(&matchEnd, "Chorus:",
									 GTK_TEXT_SEARCH_CASE_INSENSITIVE,
									 &matchStart, &matchEnd,
									 NULL);
									 
		tag = gtk_text_buffer_create_tag(buffer, NULL, 
									     "font", "italic 12", 
									     "weight", 650, NULL);

		gtk_text_buffer_apply_tag(buffer, tag, &matchStart, &matchEnd);			
	}
//-----------------------------------------------------------------------------
	//g_print("Function return: %d\n", setChordPosition(tView, buffer));
	//g_print("Line number of chord: %d\n", lineNumC);*/	
}