// Author: Andrew Reye
// Date Last Modified: 11-29-2013

#include <gtk/gtk.h>
#include <stdio.h>

#include "display.h"
#include "songs.h"
//-----------------------------------------------------------------------------
gint setChordPosition(GtkTextBuffer *buffer, gint constNum)
{
	GtkTextMark *startChord, *endChord;
	GtkClipboard *clipboard = gtk_clipboard_get(GDK_SELECTION_CLIPBOARD);
	GtkTextIter chordS, chordE, startOfLine, matchStart, matchEnd, ch;
	const gchar blankChar[] = " ";	
	gint lineCountV, lineNum1, lineNum2, lineOffset1, lineOffset2, i;

	lineCountV = gtk_text_buffer_get_line_count(buffer);
	
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
	// Get line offset of iter.	
	lineNum1 = gtk_text_iter_get_line(&chordS);
	lineOffset1 = gtk_text_iter_get_line_offset(&chordS);	
	lineNum2 = gtk_text_iter_get_line(&chordE);
	lineOffset2 = gtk_text_iter_get_line_offset(&chordE);
	
	gtk_text_buffer_select_range(buffer, &chordS, &chordE);
	gtk_text_buffer_cut_clipboard(buffer, clipboard, TRUE);
	
	if(lineCountV == constNum)
	{	
		gtk_text_buffer_get_iter_at_line(buffer, &startOfLine, lineNum1);
		gtk_text_buffer_insert(buffer, &startOfLine, "\n", -1);
		lineCountV = gtk_text_buffer_get_line_count(buffer);
	}
	/*if(lineCountV == (constNum + 1))
	{
		lineNum1 = lineNum1 - 1;		
		lineNum2 = lineNum2 - 1;
		lineCountV = gtk_text_buffer_get_line_count(buffer);
		
		gtk_text_buffer_get_iter_at_line(buffer, &ch, lineNum1);
		gtk_text_iter_forward_to_line_end(&ch);
		
		gtk_text_buffer_paste_clipboard(buffer, clipboard, &ch, TRUE);
		gtk_text_iter_forward_cursor_positions(&ch, lineOffset1);
	}*/
	gtk_text_buffer_get_iter_at_line_offset(buffer, &ch, lineNum1, lineOffset1);
	
	for(i = 0;i < 75;i++)
	{
		gtk_text_buffer_insert(buffer, &ch, blankChar[i], 75);	
	}

	gtk_text_buffer_paste_clipboard(buffer, clipboard, &ch, TRUE);	
	gtk_text_buffer_get_iter_at_line_offset(buffer, &ch, lineNum1, lineOffset2);
	gtk_text_buffer_backspace(buffer, &ch, FALSE, TRUE);
	gtk_text_buffer_get_iter_at_line_offset(buffer, &ch, lineNum1, lineOffset1 +1);
	gtk_text_buffer_backspace(buffer, &ch, FALSE, TRUE);
	gtk_text_buffer_delete_mark_by_name(buffer, "startChord");
	gtk_text_buffer_delete_mark_by_name(buffer, "endChord");
	
	return 0;
}
//-----------------------------------------------------------------------------
gint searchCharPos(gchar body[], gchar ch)
{	
	gint i;	
	
	for(i = 0; body[i] != '\0'; i++)
 	{
		if(body[i] == ch)
		{
			return i;
		}	
	}

	return -1;
}
//-----------------------------------------------------------------------------
gint charCount(gchar body[], gchar ch)
{
	gint i, count = 0;
	
	for(i = 0; body[i] != '\0'; i++)
	{
		if(body[i] == ch)
		{
			count++;		
		}	
	}
	
	return count;
}
//-----------------------------------------------------------------------------
void display(GtkTextBuffer *buffer, GtkWidget *tView, gchar *view, gint number)
{	
	GtkTextTag *tag;
	GtkTextIter startOfLine, endOfLine, ch, matchStart, matchEnd;	
	gint i, bracketS, bracketE, positionS, positionE;
	gint lineCountC;	
	const gchar *songSection[] = {"Verse:", "Verse 1", "Verse 2:",
								  "Verse 3:","Bridge:", "Bridge 1:",
								  "Bridge 2:", "Bridge 3:", "Intro:",
								  "End", "Pre"};
//-----------------------------------------------------------------------------		
	gtk_text_buffer_set_text(buffer, view, number);	
	
	lineCountC = gtk_text_buffer_get_line_count(buffer);
	
	gtk_text_view_set_editable(GTK_TEXT_VIEW(tView), FALSE);
//-----------------------------------------------------------------------------	
	// Sets these iters to a range on line 0 to delete and set 
	// desired visible text.
	gtk_text_buffer_get_iter_at_line(buffer, &startOfLine, 0);

	gtk_text_buffer_get_iter_at_line_offset(buffer, &ch, 0, 8);

	gtk_text_buffer_delete(buffer, &startOfLine, &ch);		
//-----------------------------------------------------------------------------			
	// Deletes last character of line 0 to output just the title. 
	gtk_text_buffer_get_iter_at_line(buffer, &endOfLine, 0);

	gtk_text_iter_forward_to_line_end(&endOfLine);
	
	gtk_text_buffer_backspace(buffer, &endOfLine, FALSE, TRUE);
//-----------------------------------------------------------------------------			
	// Sets attributes for Title (line 0).			
	gtk_text_buffer_get_iter_at_line(buffer, &startOfLine, 0);
	
	gtk_text_buffer_get_iter_at_line(buffer, &endOfLine, 0);
	
	gtk_text_iter_forward_to_line_end(&endOfLine);			
			
	tag = gtk_text_buffer_create_tag(buffer, 
	  								 NULL, "weight", "850",
									 "justification", GTK_JUSTIFY_CENTER, 
									 "font", "30", NULL);
												  
	gtk_text_buffer_apply_tag(buffer, tag, &startOfLine, &endOfLine);
//-----------------------------------------------------------------------------			
	// Sets these iters to a range on line 1 
	// to delete and set desired visible text. 				
	gtk_text_buffer_get_iter_at_line(buffer, &startOfLine, 1);
	
	gtk_text_buffer_get_iter_at_line_offset(buffer, &ch, 1, 11);
	
	gtk_text_buffer_delete(buffer, &startOfLine, &ch);			
//-----------------------------------------------------------------------------			
	// Deletes last character of line 1 to output just the artist.
	gtk_text_buffer_get_iter_at_line(buffer, &endOfLine, 1);
	
	gtk_text_iter_forward_to_line_end(&endOfLine);
	
	gtk_text_buffer_backspace(buffer, &endOfLine, FALSE, TRUE);	
//-----------------------------------------------------------------------------			
	// Inserts text before artist with attributes.
	tag = gtk_text_buffer_create_tag(buffer, NULL, "font", "12", 
		    						 "justification", GTK_JUSTIFY_CENTER, 
		    						 "weight", "850", NULL);
	gtk_text_buffer_get_iter_at_line(buffer, &startOfLine, 1);
	
	gtk_text_buffer_insert_with_tags(buffer, &startOfLine, 
									 "by: ", 4, tag, NULL);
//-----------------------------------------------------------------------------			
	// Sets attributes for Artist (line 1).
	gtk_text_buffer_get_iter_at_line_offset(buffer, &startOfLine, 1, 4);
	
	gtk_text_buffer_get_iter_at_line(buffer, &endOfLine, 1);
	
	gtk_text_iter_forward_to_line_end(&endOfLine);			
	
	tag = gtk_text_buffer_create_tag(buffer, 
	  								 NULL, "weight", "600",
									 "weight-set", TRUE, 
									 "font", "italic 18", NULL);
												  
	gtk_text_buffer_apply_tag(buffer, tag, &startOfLine, &endOfLine);	
//-----------------------------------------------------------------------------			
	// This section is for setting the attributes of the text
	// 'Verse:', 'Chorus:'etc...			
	gtk_text_buffer_get_start_iter(buffer, &startOfLine);
	
	for(i = 0; i < 11; i++)
	{
		if(gtk_text_iter_forward_search(&startOfLine, songSection[i], 1,
										&matchStart, &matchEnd, NULL))
		{
			tag = gtk_text_buffer_create_tag(buffer, NULL, 
										     "font", "italic 12", NULL);

			gtk_text_buffer_apply_tag(buffer, tag, &matchStart, &matchEnd);
		}	
	}		
	
	if(gtk_text_iter_forward_search(&startOfLine, "Chorus:", 
	   								1, &matchStart, &matchEnd, NULL))
	{
		tag = gtk_text_buffer_create_tag(buffer, NULL, 
										 "font", "italic 12", NULL);

		gtk_text_buffer_apply_tag(buffer, tag, &matchStart, &matchEnd);			
	
		gtk_text_iter_forward_search(&matchEnd, "Chorus:",
									 1, &matchStart, &matchEnd,
									 NULL);
									 
		tag = gtk_text_buffer_create_tag(buffer, NULL, 
									     "font", "italic 12", NULL);

		gtk_text_buffer_apply_tag(buffer, tag, &matchStart, &matchEnd);			
	}	
//-----------------------------------------------------------------------------			
	/*if(gtk_text_iter_forward_search(&startOfLine, "[", 1, 
									&matchStart, &matchEnd, NULL))
	{
		i = gtk_text_iter_get_line(&matchStart);
		
		j = gtk_text_iter_get_line_offset(&matchStart);	
		
		gtk_text_buffer_select_range(buffer, &matchStart, &matchEnd);
		
		gtk_text_buffer_cut_clipboard(buffer, clipboard, TRUE);		
		
		gtk_text_buffer_get_iter_at_line(buffer, &startOfLine, i);		
		
		gtk_text_buffer_insert(buffer, &startOfLine, "\n", -1);
		
		gtk_text_buffer_get_iter_at_line_offset(buffer, &ch, i, j);
		
		gtk_text_buffer_paste_clipboard(buffer, clipboard, &ch, TRUE);		
	}*/	
//-----------------------------------------------------------------------------
	/*GtkTextMark *startChord, *endChord;
	GtkTextIter chordS, chordE;	

	lineCountV = gtk_text_buffer_get_line_count(buffer);
	
	
	if(gtk_text_iter_forward_search(&startOfLine, "[", 1, 
									&matchStart, &matchEnd, NULL))
	{		
		gtk_text_buffer_create_mark(buffer, "startChord", &matchStart, FALSE);
		
		startChord = gtk_text_buffer_get_mark(buffer, "startChord");
	}
	
	if(gtk_text_iter_forward_search(&startOfLine, "]", 1, 
									&matchStart, &matchEnd, NULL))		
	{		
		gtk_text_buffer_create_mark(buffer, "endChord", &matchEnd, FALSE);
		
		endChord = gtk_text_buffer_get_mark(buffer, "endChord");	
	}	
	
	gtk_text_buffer_get_iter_at_mark(buffer, &chordS, startChord);
	gtk_text_buffer_get_iter_at_mark(buffer, &chordE, endChord);
	lineNum1 = gtk_text_iter_get_line(&chordS);
	lineOffset1 = gtk_text_iter_get_line_offset(&chordS);	
	lineNum2 = gtk_text_iter_get_line(&chordE);
	lineOffset2 = gtk_text_iter_get_line_offset(&chordE);
	gtk_text_buffer_select_range(buffer, &chordS, &chordE);
	gtk_text_buffer_cut_clipboard(buffer, clipboard, TRUE);
	
	if(lineCountV == lineCountC)
	{	
		gtk_text_buffer_get_iter_at_line(buffer, &startOfLine, lineNum1);
		gtk_text_buffer_insert(buffer, &startOfLine, "\n", -1);
		lineCountV = gtk_text_buffer_get_line_count(buffer);
	}

	gtk_text_buffer_get_iter_at_line_offset(buffer, &ch, lineNum1, lineOffset1);
	gtk_text_buffer_paste_clipboard(buffer, clipboard, &ch, TRUE);	
	gtk_text_buffer_get_iter_at_line_offset(buffer, &ch, lineNum1, lineOffset2);
	gtk_text_buffer_backspace(buffer, &ch, FALSE, TRUE);
	gtk_text_buffer_get_iter_at_line_offset(buffer, &ch, lineNum1, lineOffset1 +1);
	gtk_text_buffer_backspace(buffer, &ch, FALSE, TRUE);
	gtk_text_buffer_delete_mark_by_name(buffer, "startChord");
	gtk_text_buffer_delete_mark_by_name(buffer, "endChord");*/
	//setChordPosition(buffer, lineCountC);
	for(;setChordPosition(buffer, lineCountC) == 0;)
	{
		setChordPosition(buffer,lineCountC);	
	}
	g_print("Function return: %d\n", setChordPosition(buffer, lineCountC));
//-----------------------------------------------------------------------------
	positionS = searchCharPos(view, '[');		
	positionE = searchCharPos(view, ']');		
	
	bracketS = charCount(view, '[');
	bracketE = charCount(view, ']');	
			
			
	g_print("Line count for display is: %d\n", lineCountC);
	g_print("Count for '[' and ']' characters: \n%d:%d\n", bracketS, bracketE);
	g_print("Position for the first '[' and ']' ");
	g_print("characters: \n%d:%d\n", positionS, positionE);
}