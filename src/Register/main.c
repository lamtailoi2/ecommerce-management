#include <gtk/gtk.h>

// This is your authentication function. It should check the username, email, and password
// against your authentication system and return TRUE if the user is authenticated, FALSE otherwise.
// gboolean authenticate(const char *username, const char *email, const char *password) {
//     // TODO: Implement this function
//     return TRUE;
// }

gboolean validate_registration(const char *username, const char *email, const char *password) {
    // TODO: Implement this function to validate the registration details
    // For now, we'll assume that any non-empty username, email, and password are valid
    return username[0] != '\0' && email[0] != '\0' && password[0] != '\0';
}

void write_user_to_csv(const char *username, const char *email, const char *password) {
    FILE *file = freopen("users.csv", "a", stdout);
    if (file != NULL) {
        fprintf(file, "Username: %s, Email: %s, Password: %s\n", username, email, password);
        fclose(file);
    } else {
        printf("Failed to open users.csv\n");
    }
}

void on_registerButton_clicked(GtkButton *button, gpointer user_data) {
    GtkBuilder *builder = GTK_BUILDER(user_data);
    GtkEntry *usernameEntry = GTK_ENTRY(gtk_builder_get_object(builder, "usernameEntry"));
    GtkEntry *emailEntry = GTK_ENTRY(gtk_builder_get_object(builder, "emailEntry"));
    GtkEntry *passwordEntry = GTK_ENTRY(gtk_builder_get_object(builder, "passwordEntry"));

    const char *username = gtk_entry_get_text(usernameEntry);
    const char *email = gtk_entry_get_text(emailEntry);
    const char *password = gtk_entry_get_text(passwordEntry);
    write_user_to_csv(username, email, password);

    if (validate_registration(username, email, password)) {
        // The registration details are valid. Open the home page.
        GtkWidget *homeWindow;
        GtkBuilder *homeBuilder;
        homeBuilder = gtk_builder_new_from_file("Home.glade");
        homeWindow = GTK_WIDGET(gtk_builder_get_object(homeBuilder, "homeWindow"));
        gtk_widget_show_all(homeWindow);
        gtk_widget_destroy(GTK_WIDGET(gtk_builder_get_object(builder, "registerWindow")));
    } else {
        // The registration details are invalid. Show an error message.
        GtkWidget *dialog;
        dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Invalid registration details!");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }
}

void activate(GtkApplication* app, gpointer user_data) {
    GtkBuilder *builder;
    GtkWidget *window;
    GtkWidget *registerButton;
    
    builder = gtk_builder_new_from_file("Register.glade");
    window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
    registerButton = GTK_WIDGET(gtk_builder_get_object(builder, "registerButton"));

    // Connect the "clicked" signal of the register button to the on_registerButton_clicked function
    g_signal_connect(registerButton, "clicked", G_CALLBACK(on_registerButton_clicked), builder);

    // Connect the "destroy" signal of the window to the g_application_quit function
    g_signal_connect_swapped(window, "destroy", G_CALLBACK(g_application_quit), app);

    gtk_application_add_window(app, GTK_WINDOW(window));
    gtk_widget_show_all(window);
}

int main(int argc, char *argv[]) {
    GtkApplication *app;

    app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}