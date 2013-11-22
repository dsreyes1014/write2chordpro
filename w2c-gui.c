/* Description: Tool to help create chordpro text files for apps like Onsong for ipad or Songbook for Android 
 * Author: Andrew Reyes
 * Date : 11-19-2013
 */

#include <gtk/gtk.h>
#include <string.h>
#include <stdio.h>

GtkWidget *dialog, *chordDialog;
GtkWidget *window;
GtkWidget *entryTitle, *entryArtist;
GtkWidget *textView;
GtkTextBuffer *buffer;
GtkWidget *treeView;
GtkTreeStore *treeStore;
GtkTreeSelection *selection;
GtkTreeViewColumn *column;
GtkTreeModel *model;
GtkTextMark *cursor;
/* GtkListStore *listStore; */

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

void rowChange(GtkWidget *widget, gpointer data)
{
	GtkTreeIter selChord;
	GtkTextIter iter; 
	gchar *getChord;
	
	if(gtk_tree_selection_get_selected(GTK_TREE_SELECTION(widget), &model, &selChord))
	{		
		gtk_tree_model_get(model, &selChord, 0, &getChord, -1);		

		g_print("%s\n", getChord);		
		
		gtk_text_buffer_insert_at_cursor(GTK_TEXT_BUFFER(buffer), getChord, -1);
		
		g_free(getChord);
		
		gtk_text_buffer_get_iter_at_mark(GTK_TEXT_BUFFER(buffer), &iter, cursor);
		
		/* Move cursor forward one space out of brackets */
		gtk_text_iter_forward_chars(&iter, 1);
		gtk_text_buffer_place_cursor(GTK_TEXT_BUFFER(buffer), &iter);	
		
		/* Hides dialog window from screen */ 
		gtk_widget_hide(chordDialog);
	}
}

static void insertChord(GtkWidget *widget, gpointer data)
{	
	GtkWidget *scrolledWindow;
	GtkWidget *frame, *topHalf, *bottomHalf, *label;
	GtkTreeViewColumn *column;
	GtkCellRenderer *cell; 
	GtkTextIter iter;
	GtkTreeIter parent, child1, child2;
	GtkTreeSelection *selection;
	GtkTreeStore *treeStore;
	gchar *brackets;
	
	brackets = "[]";					
	cell = gtk_cell_renderer_text_new(); 
	treeStore = gtk_tree_store_new(1, G_TYPE_STRING); 
	treeView = gtk_tree_view_new_with_model(GTK_TREE_MODEL(treeStore));	
	cursor = gtk_text_buffer_get_insert(GTK_TEXT_BUFFER(buffer));   /* Assigns cursor variable to the actual cursor within buffer */
	scrolledWindow = gtk_scrolled_window_new(NULL, NULL);	
	column = gtk_tree_view_column_new_with_attributes(NULL, cell, "text", 0, NULL); 
	frame = gtk_frame_new("Chord");		
	chordDialog = gtk_dialog_new();
	topHalf = gtk_dialog_get_content_area(GTK_DIALOG(chordDialog));
	bottomHalf = gtk_dialog_get_action_area(GTK_DIALOG(chordDialog));	
	label = gtk_label_new("Choose Chord");
	selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(treeView));	
	model = gtk_tree_view_get_model(GTK_TREE_VIEW(treeView));	
	
	/* Sets cursor to visible. I think it's set by default but adding it to make sure */
	gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(textView), TRUE);	
	
	/* Inserts string inside "..." at cursor location */
	gtk_text_buffer_insert_at_cursor(GTK_TEXT_BUFFER(buffer), brackets, 2);	
	
	/* Initializes variable 'iter' */	
	gtk_text_buffer_get_iter_at_mark(GTK_TEXT_BUFFER(buffer), &iter, cursor);	
	
	/* Moves cursor back one space */
	gtk_text_iter_backward_chars(&iter, 1);	
	gtk_text_buffer_place_cursor(GTK_TEXT_BUFFER(buffer), &iter);		
	
	/* Sets properties of frame & dialog widgets */	
	gtk_frame_set_shadow_type(GTK_FRAME(frame), GTK_SHADOW_ETCHED_IN);
	gtk_widget_set_size_request(frame, 490, 490);
		
	/* Pack widgets */
	gtk_container_add(GTK_CONTAINER(scrolledWindow), treeView);
	gtk_container_add(GTK_CONTAINER(frame), scrolledWindow);
	gtk_container_add(GTK_CONTAINER(topHalf), label);
	gtk_container_add(GTK_CONTAINER(bottomHalf), frame);	
	
	gtk_tree_view_set_activate_on_single_click(GTK_TREE_VIEW(treeView), TRUE);	
	
	gtk_widget_show_all(chordDialog);	
	
	g_object_unref(treeStore);	
	
	
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &parent, NULL);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &parent, 0, "A", -1);	
	
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child1, &parent);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child1, 0, "A#", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child2, &child1);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child2, 0, "A#", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child2, &child1);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child2, 0, "A#m", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child2, &child1);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child2, 0, "A#7", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child2, &child1);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child2, 0, "A#M7", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child2, &child1);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child2, 0, "A#m7", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child2, &child1);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child2, 0, "A#sus2", -1);	
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child2, &child1);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child2, 0, "A#sus4", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child1, &parent);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child1, 0, "Ab", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child2, &child1);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child2, 0, "Ab", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child2, &child1);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child2, 0, "Abm", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child2, &child1);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child2, 0, "Ab7", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child2, &child1);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child2, 0, "AbM7", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child2, &child1);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child2, 0, "Abm7", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child2, &child1);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child2, 0, "Absus2", -1);	
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child2, &child1);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child2, 0, "Absus4", -1);	
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child1, &parent);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child1, 0, "A", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child1, &parent);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child1, 0, "Am", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child1, &parent);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child1, 0, "A7", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child1, &parent);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child1, 0, "AM7", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child1, &parent);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child1, 0, "Am7", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child1, &parent);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child1, 0, "Asus2", -1);
	gtk_tree_store_append(GTK_TREE_STORE(treeStore), &child1, &parent);
	gtk_tree_store_set(GTK_TREE_STORE(treeStore), &child1, 0, "Asus4", -1);	
	
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeView), column);
		
	/* Sets properties for chordDialog widget */	
	gtk_window_set_modal(GTK_WINDOW(chordDialog), TRUE);
	gtk_widget_set_size_request(chordDialog, 500, 500);	
	gtk_widget_set_size_request(frame, 490, 490);
	
	gtk_tree_selection_set_mode(GTK_TREE_SELECTION(selection), GTK_SELECTION_BROWSE);
	
	g_signal_connect(selection, "changed", G_CALLBACK(rowChange), NULL);			
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
	GtkWidget *button1, *button2; //*button3;
		
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
	frame1 = gtk_frame_new("Songs");	
	frame2 = gtk_frame_new(NULL);
	scrolledWindow = gtk_scrolled_window_new(NULL, NULL);
	button1 = gtk_button_new_with_label("Insert Chord");
	button2 = gtk_button_new_with_label("Transpose");
	//button3 = gtk_button_new_with_label("Edit Song");
	textView = gtk_text_view_new();	
	buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textView));
	
	/* This creates main window titled 'Write 2 Chordpro'. */	
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "Write 2 Chordpro");
	
	/* Sizes the paned widget 
	gtk_widget_set_size_request(paned, 800, 600); */
	
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
	
	gtk_frame_set_shadow_type(GTK_FRAME(frame1), GTK_SHADOW_ETCHED_IN);
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
	
	/* Packs frame1 & notebook widgets inside pane 1 & 2 respectively */	
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
