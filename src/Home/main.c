#include <gtk/gtk.h>


void on_tool_but1_clicked(GtkToolButton *button, gpointer user_data){
    
}

// Signal handler for the "clicked" signal of the "Browse Products" button
void on_browseButton_clicked(GtkButton *button, gpointer user_data) {
    //window
    GtkWidget *window;
    //button
    GtkWidget *but1;
    GtkWidget *but2;
    GtkWidget *but3;
    GtkWidget *exit;
    //box
    GtkWidget *box;
    //fixed
    GtkWidget *fixed;

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    // Initialize the size of product window
    gtk_window_set_default_size (GTK_WINDOW (window), 1400, 700);

    fixed = gtk_fixed_new();

    but1 = gtk_button_new_with_label("Add products");
    but2 = gtk_button_new_with_label("Edit products");
    but3 = gtk_button_new_with_label("Delete products");
    exit = gtk_button_new_with_label("Exit");

    gtk_fixed_put(GTK_FIXED(fixed), but1, 25, 550);
    gtk_fixed_put(GTK_FIXED(fixed), but2, 25, 600);
    gtk_fixed_put(GTK_FIXED(fixed), but3, 25, 650);

    gtk_fixed_put(GTK_FIXED(fixed), exit, 1400, 10);
    g_signal_connect(exit, "clicked", G_CALLBACK(gtk_window_close), NULL);

    gtk_container_add(GTK_CONTAINER(window), fixed);

    // Initialize
    gtk_window_set_title (GTK_WINDOW (window), "Showing product");
    
    // Showing the product window
    gtk_widget_show_all(window);

}

int main(int argc, char *argv[]) {
    GtkBuilder *builder;
    GtkWidget *window;
    GObject *browseButton;

    // Initialize GTK
    gtk_init(&argc, &argv);

    // Create a new GtkBuilder instance
    builder = gtk_builder_new();

    // Load the UI definition from the Glade file
    gtk_builder_add_from_file(builder, "Home.glade", NULL);

    // Get the main window widget
    window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));

    // Get the "Browse Products" button
    browseButton = gtk_builder_get_object(builder, "browseButton");

    // Connect the "clicked" signal of the "Browse Products" button to the signal handler
    g_signal_connect(browseButton, "clicked", G_CALLBACK(on_browseButton_clicked), NULL);

    // Close whole program
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Show the main window
    gtk_widget_show_all(window);

    // Start the GTK main loop
    gtk_main();

    return 0;
}