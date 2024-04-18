#include <gtk/gtk.h>

// Signal handler for the "clicked" signal of the "Browse Products" button
void on_browseButton_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *dialog;

    // Create a new dialog
    dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "Browse Products clicked!");

    // Show the dialog
    gtk_dialog_run(GTK_DIALOG(dialog));

    // Destroy the dialog after it's closed 
    gtk_widget_destroy(dialog); //comment by Loi
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

    // Show the main window
    gtk_widget_show_all(window);

    // Start the GTK main loop
    gtk_main();

    return 0;
}