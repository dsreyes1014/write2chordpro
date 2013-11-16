#include <gtk/gtk.h>
#include <string.h>
#include <stdio.h>

GtkWidget *dialog;
GtkWidget *window;
GtkWidget *entryTitle, *entryArtist;
GtkWidget *textView;
GtkTextBuffer *buffer;

static const char *fileMenuTitles[] = {"Open", "Save", "Quit"};

static void fileMenuCallBack(GtkMenuItem *item, gpointer data)
{
	char option[20];
	
	sprintf(option, "%s", gtk_menu_item_get_label(item));
	
	/* printf("%s\n", gtk_menu_item_get_label(item) */
	
	if(strcmp(option,"Open") == 0) /* If option clicked is Open */
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

static void insertChord(GtkWidget *widget, gpointer data)
{	
	GtkTextMark *cursor;	
	GtkWidget *listBox;
	GtkTextIter iter;
		
	cursor = gtk_text_buffer_get_insert(GTK_TEXT_BUFFER(buffer));   /* Assigns cursor variable to the actual cursor within buffer */
	listBox = gtk_list_box_new();
	
	gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(textView), TRUE);
	
	/* Inserts string inside "..." at cursor location */
	gtk_text_buffer_insert_at_cursor(GTK_TEXT_BUFFER(buffer), "[]", 2);
	
	/* Initializes variable 'iter' */	
	gtk_text_buffer_get_iter_at_mark(GTK_TEXT_BUFFER(buffer), &iter, cursor);
	
	/* Moves cursor back one space */
	gtk_text_iter_backward_chars(&iter, 1);	
	gtk_text_buffer_place_cursor(GTK_TEXT_BUFFER(buffer), &iter);
		
	gtk_widget_show(listBox);
}

int main(int argc, char *argv[])
{
	GtkWidget *box1, *box2, *box3;
	GtkWidget *paned;
	GtkWidget *frame1, *frame2;
	GtkWidget *notebook;
	GtkWidget *grid;
	GtkWidget *label1, *label2;
	GtkWidget *menuBar;
	GtkWidget *fileMenu;
	GtkWidget *menuItemFile;
	GtkWidget *tabLabel;
	GtkWidget *scrolledWindow;
	GtkWidget *button1, *button2;
		
	gtk_init(&argc, &argv);
	
	box1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 2);
	box2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
	box3 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 2);
	paned = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);
	menuBar = gtk_menu_bar_new();
	fileMenu = gtk_menu_new();
	menuItemFile = gtk_menu_item_new_with_label("File");
	notebook = gtk_notebook_new();
	grid = gtk_grid_new();
	label1 = gtk_label_new("Title:");
	label2 = gtk_label_new("Artist:");
	entryTitle = gtk_entry_new();
	entryArtist = gtk_entry_new();
	frame1 = gtk_frame_new(NULL);	
	frame2 = gtk_frame_new(NULL);
	scrolledWindow = gtk_scrolled_window_new(NULL, NULL);
	button1 = gtk_button_new_with_label("Insert Chord");
	button2 = gtk_button_new_with_label("Transpose");
	textView = gtk_text_view_new();	
	buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textView));
	
	
	/* This creates main window titled 'Write 2 Chordpro'. */	
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "Write 2 Chordpro");
	
	/* Sizes the paned widget */
	//gtk_widget_set_size_request(paned, 800, 600);
	
	gtk_menu_bar_set_pack_direction(GTK_MENU_BAR(menuBar), GTK_PACK_DIRECTION_LTR);
	
	/* Creates menuitem 'File' and its menu for menuBar */
	for(int i = 0; i < 3; i++)
	{
		GtkWidget *menuItem = gtk_menu_item_new_with_label(fileMenuTitles[i]);
		
		gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu), menuItem);
		g_signal_connect(menuItem, "activate", G_CALLBACK(fileMenuCallBack), NULL);
	}
		
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(menuItemFile), fileMenu);
	gtk_menu_shell_append(GTK_MENU_SHELL(menuBar), menuItemFile);
		
	/* Packs menubar and paned in box1 */
	gtk_box_pack_start(GTK_BOX(box1), menuBar, FALSE, FALSE, 2);
	gtk_box_pack_start(GTK_BOX(box1), paned, FALSE, FALSE, 2);
	
	gtk_frame_set_shadow_type(GTK_FRAME(frame1), GTK_SHADOW_IN);
	gtk_frame_set_shadow_type(GTK_FRAME(frame2), GTK_SHADOW_ETCHED_IN);

	/* Sizes frame2 */	
	gtk_widget_set_size_request(GTK_WIDGET(frame2), 100, 100);
	
	/* Packs textView inside of scrolledWindow */	
	gtk_container_add(GTK_CONTAINER(scrolledWindow), textView);
	
	/* Packs scrolledWindow into frame2 */
	gtk_container_add(GTK_CONTAINER(frame2), scrolledWindow);
	
	//gtk_button_set_alignment(GTK_BUTTON(button1), 0.5, 0.2);
	
	/* Places button1 & button2 into box3 */
	gtk_box_pack_start(GTK_BOX(box3), button1, FALSE, FALSE, 2);
	gtk_box_pack_start(GTK_BOX(box3), button2, FALSE, FALSE, 2);
	
	g_signal_connect(button1, "clicked", G_CALLBACK(insertChord), NULL);
		
	/* Attaches widgets to widget grid */	
	gtk_grid_attach(GTK_GRID(grid), label1, 0, 0, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), label2, 0, 10, 1, 1);	
	gtk_grid_attach_next_to(GTK_GRID(grid), entryTitle, label1, GTK_POS_RIGHT, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(grid), entryArtist, label2, GTK_POS_RIGHT, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), frame2, 0, 14, 130, 150);
	gtk_grid_attach_next_to(GTK_GRID(grid), box3, frame2, GTK_POS_RIGHT, 1, 1);
	
	/* Sets row & column spacing between widgets inside grid */
	gtk_grid_set_row_spacing(GTK_GRID(grid), 3);
	gtk_grid_set_column_spacing(GTK_GRID(grid), 3);
	
	/* Creates tabs for notebook */	
	gtk_notebook_append_page(GTK_NOTEBOOK(notebook), box2, NULL);
	gtk_notebook_append_page(GTK_NOTEBOOK(notebook), grid, NULL);
	
	/* Sets labels for notebook tabs */	
	tabLabel = gtk_label_new("Display");	
	gtk_notebook_set_tab_label(GTK_NOTEBOOK(notebook), box2, tabLabel);	
	tabLabel = gtk_label_new("Song Editor");	
	gtk_notebook_set_tab_label(GTK_NOTEBOOK(notebook), grid, tabLabel);
	
	/* Packs frame1 & notebook widgets inside panes 1 & 2 respectively */	
	gtk_paned_pack1(GTK_PANED(paned), frame1, FALSE, FALSE);
	gtk_paned_pack2(GTK_PANED(paned), notebook, FALSE, FALSE);
	
	/* Sizes both frame widgets */ 
	gtk_widget_set_size_request(frame1, 200, 75);
	gtk_widget_set_size_request(notebook, 300, 150);
	
	/* This signal terminates main window when the close button is clicked */	
	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	
	/* Adds the paned widget to main window widget */	
	gtk_container_add(GTK_CONTAINER(window), box1);
	
	/* Make main window and it's child windows visible */	
	gtk_widget_show_all(window);
	
	
	gtk_main();
	
	return 0;
}
