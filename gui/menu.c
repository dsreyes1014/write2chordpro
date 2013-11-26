// Author: Andrew Reyes.
// Date Last Modified: 11-25-2013.

#include <gtk/gtk.h>
#include <stdio.h>
#include "menu.h"

static const char *fileMenuTitles[] = {"Open", "Save", "Quit"}; // Declared for 'menuItemFile' named "File".

static void fileMenuCallBack(GtkMenuItem *item, gpointer data)
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

void menuFunction(void)
{
	GtkWidget *menuBar;        // Creates menu
	GtkWidget *fileMenu;       // widgets to
	GtkWidget *menuItemFile;   // complete menu.
	
	gint i;    // Used in the next for loop.
	
	menuBar = gtk_menu_bar_new();     // Instantiates (assigns) 'menuBar'.                     
	fileMenu = gtk_menu_new();           // Instantiates (assigns) 'fileMenu'.
	
	menuItemFile = gtk_menu_item_new_with_label("File");    // Instantiate (assigns) 'menuItemFile'
	                                                        // and creates submenu named 'File'. 
	
	// Reads the menu items packed into 'menuBar' from left to right.	
	gtk_menu_bar_set_pack_direction(GTK_MENU_BAR(menuBar), GTK_PACK_DIRECTION_LTR);
	
	// Creates menuitem 'File' and its menu for menuBar. 
	for(i = 0; i < 3; i++)
	{
		GtkWidget *menuItem = gtk_menu_item_new_with_label(fileMenuTitles[i]);
		
		gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu), menuItem);
		g_signal_connect(menuItem, "activate", G_CALLBACK(fileMenuCallBack), NULL);
	}
		
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(menuItemFile), fileMenu);
	gtk_menu_shell_append(GTK_MENU_SHELL(menuBar), menuItemFile);
}