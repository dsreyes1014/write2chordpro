// Author: Andrew Reyes.
// Date Last Modified: 11-25-2013.

#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>

#include "menu.h"

GtkWidget *menu_bar;
extern GtkWidget *window;
const gchar *file_menu_titles[] = {"Open", "Save", "Quit"}; // Declared for 'menu_item_file' named "File".

void file_menu_callback(GtkMenuItem *item, gpointer data)
{
	GtkWidget *dialog;	
	
	char option[20];
	
	sprintf(option, "%s", gtk_menu_item_get_label(item));
	
	if(strcmp(option,"Open") == 0)    // If option clicked is 'Open'
	{
		dialog = gtk_file_chooser_dialog_new("Choose file to open",
                                             GTK_WINDOW(window),
                                             GTK_FILE_CHOOSER_ACTION_OPEN,
                                             ("_Cancel"), GTK_RESPONSE_CANCEL,
                                             ("_Open"), GTK_RESPONSE_ACCEPT,
                                             NULL);
		gtk_widget_set_size_request(dialog, 100, 100);
		
		gtk_widget_show_all(dialog);
	
		if(gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT)
		{
			char *filename;
			filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));

			g_free(filename);
		}
		gtk_widget_destroy(dialog);
	}
	if(strcmp(option,"Quit") == 0)
	{
		gtk_main_quit();
	}
}

void menu_function(void)
{
					           // Creates menu
	GtkWidget *file_menu;       // widgets to
	GtkWidget *menu_item_file;   // complete menu.
	
	gint i;    // Used in the next for loop.
	
	menu_bar = gtk_menu_bar_new();     // Instantiates (assigns) 'menu_bar'.                     
	file_menu = gtk_menu_new();           // Instantiates (assigns) 'file_menu'.
	
	menu_item_file = gtk_menu_item_new_with_label("File");    // Instantiate (assigns) 'menu_item_file'
	                                                        // and creates submenu named 'File'. 
	
	// Reads the menu items packed into 'menu_bar' from left to right.	
	gtk_menu_bar_set_pack_direction(GTK_MENU_BAR(menu_bar), GTK_PACK_DIRECTION_LTR);
	
	// Creates menuitem 'File' and its menu for menu_bar. 
	for(i = 0; i < 3; i++)
	{
		GtkWidget *menuItem = gtk_menu_item_new_with_label(file_menu_titles[i]);
		
		gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), menuItem);
		g_signal_connect(menuItem, "activate", G_CALLBACK(file_menu_callback), NULL);
	}
		
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu_item_file), file_menu);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), menu_item_file);
}