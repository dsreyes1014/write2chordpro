#include <gtk/gtk.h>
#include <string.h>

GtkWidget *dialog;
GtkWidget *window;

static const char *titles[] = {"Open", "Quit"};

static void menuCallBack(GtkMenuItem *item, gpointer data)
{
	char option[20];
	
	sprintf(option, "%s", gtk_menu_item_get_label(item));
	
	/* printf("%s\n", gtk_menu_item_get_label(item) */
	
	if(strcmp(option,"Open") == 0) /* If option clicked is Open */
	{
		dialog = gtk_file_chooser_dialog_new("Open File",
											GTK_WINDOW(window),
											GTK_FILE_CHOOSER_ACTION_OPEN,
											("_Cancel"), GTK_RESPONSE_CANCEL,
											("_Open"), GTK_RESPONSE_ACCEPT,
											NULL);
		gtk_widget_set_size_request(dialog, 800, 600);
		
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

int main(int argc, char *argv[])
{
	GtkWidget *box1, *box2, *box3;
	GtkWidget *paned;
	GtkWidget *frame1;
	GtkWidget *notebook;
	
	GtkWidget *menuBar;
	GtkWidget *fileMenu;
	GtkWidget *menuItemFile;
		
	gtk_init(&argc, &argv);
	
	box1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 2);
	box2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
	box3 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
	paned = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);
	menuBar = gtk_menu_bar_new();
	fileMenu = gtk_menu_new();
	menuItemFile = gtk_menu_item_new_with_label("File");
	notebook = gtk_notebook_new();
	
	/* This creates main window titled 'Write 2 Chordpro'. */	
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "Write 2 Chordpro");
	
	/* Sizes the paned widget */
	gtk_widget_set_size_request(paned, 800, 600);
	
	gtk_menu_bar_set_pack_direction(GTK_MENU_BAR(menuBar), GTK_PACK_DIRECTION_LTR);
	
	/* Creates menubar */
	for(int i = 0; i < 2; i++)
	{
		GtkWidget *menuItem = gtk_menu_item_new_with_label(titles[i]);
		
		gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu), menuItem);
		g_signal_connect(menuItem, "activate", G_CALLBACK(menuCallBack), NULL);
	}
		
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(menuItemFile), fileMenu);
	gtk_menu_shell_append(GTK_MENU_SHELL(menuBar), menuItemFile);
		
	/* Packs menubar and paned in boxes 1 and 2 respectively of box1 */
	gtk_box_pack_start(GTK_BOX(box1), menuBar, FALSE, FALSE, 2);
	gtk_box_pack_end(GTK_BOX(box1), paned, FALSE, FALSE, 2);
		
	frame1 = gtk_frame_new(NULL);
	
	gtk_frame_set_shadow_type(GTK_FRAME(frame1), GTK_SHADOW_IN);
	
	gtk_notebook_append_page(GTK_NOTEBOOK(notebook), box2, NULL);
	gtk_notebook_append_page(GTK_NOTEBOOK(notebook), box3, NULL);
	
	/* Packs frame 1 & notebook widgets inside panes 1 & 2 respectively */	
	gtk_paned_pack1(GTK_PANED(paned), frame1, FALSE, FALSE);
	gtk_paned_pack2(GTK_PANED(paned), notebook, FALSE, FALSE);
	
	/* Sizes both frame widgets */ 
	gtk_widget_set_size_request(frame1, 20, 150);
	gtk_widget_set_size_request(notebook, 50, 150);
	
	/* This signal terminates main window when the close button is clicked */	
	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	
	/* Adds the paned widget to main window widget */	
	gtk_container_add(GTK_CONTAINER(window), box1);
	
	/* Make main window and it's child windows visible */	
	gtk_widget_show_all(window);
	
	
	gtk_main();
	
	return 0;
}
