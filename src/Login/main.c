#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "/Users/tranquangsang/Desktop/lamtailoi/shop-management/src/Headers/password.h"

// Compare the encrypted password with the given password
bool compare_password(const char *passwordFromFile, const char *password, int key)
{
    if (passwordFromFile == NULL || password == NULL)
    {
        return false;
    }
    char hash[256];
    int i = 0;
    while (password[i] != '\0')
    {
        hash[i] = password[i] + key;
        i++;
    }
    hash[i] = '\0';
    return strcmp(passwordFromFile, hash) == 0 ? true : false;
}

bool is_match(const char *password)
{
    FILE *file = fopen("/Users/tranquangsang/Desktop/lamtailoi/shop-management/src/textDB/users.csv", "r");
    if (file == NULL)
    {
        printf("Could not open users.csv\n");
        return false;
    }
    char line[256];
    while (fgets(line, sizeof(line), file))
    {
        char *csv_username = strtok(line, ",");
        char *csv_email = strtok(NULL, ",");
        char *csv_password = strtok(NULL, ", ");

        // Remove newline character from csv_password
        csv_password[strcspn(csv_password, "\n")] = 0;

        if (compare_password(csv_password, password, 69))
        {
            fclose(file);
            return true;
        }
    }
    fclose(file);
    return false;
}

// Check if username exists
bool is_username_exists(const char *username)
{
    FILE *file = fopen("/Users/tranquangsang/Desktop/lamtailoi/shop-management/src/textDB/users.csv", "r");
    if (file == NULL)
    {
        printf("Could not open users.csv\n");
        return false;
    }

    char line[256];
    while (fgets(line, sizeof(line), file))
    {
        char *csv_username = strtok(line, ",");
        if (csv_username != NULL)
        {
            if (strcmp(username, csv_username) == 0)
            {
                fclose(file);
                return true;
            }
        }
    }

    fclose(file);
    return false;
}

void on_loginButton_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *homeWindow;
    GtkBuilder *homeBuilder;
    GtkBuilder *builder = GTK_BUILDER(user_data);
    GtkEntry *usernameEntry = GTK_ENTRY(gtk_builder_get_object(builder, "usernameEntry"));
    GtkEntry *passwordEntry = GTK_ENTRY(gtk_builder_get_object(builder, "passwordEntry"));

    if (!usernameEntry || !passwordEntry)
    {
        printf("Username or password entry not found\n");
        return;
    }

    if (!is_username_exists(gtk_entry_get_text(usernameEntry)))
    {
        GtkWidget *dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Username does not exist");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }
    // puts(gtk_entry_get_text(passwordEntry));
    if (!is_match(gtk_entry_get_text(passwordEntry)))
    {
        GtkWidget *dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Password is incorrect");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }
    printf("Login successful\n");

    homeBuilder = gtk_builder_new_from_file("/Users/tranquangsang/Desktop/lamtailoi/shop-management/src/Home/Home.glade");
    homeWindow = GTK_WIDGET(gtk_builder_get_object(homeBuilder, "homeWindow"));

    if (homeWindow == NULL)
    {
        
        printf("Failed to get homeWindow from builder\n");
        return;
    }

    gtk_widget_show_all(homeWindow);
    gtk_main();
    gtk_widget_destroy(GTK_WIDGET(gtk_builder_get_object(builder, "window")));
}

void activate(GtkApplication *app, gpointer user_data)
{
    GtkBuilder *builder;
    GtkWidget *window;
    GtkWidget *loginButton; // Declare loginButton here

    builder = gtk_builder_new_from_file("Login.glade");
    window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
    loginButton = GTK_WIDGET(gtk_builder_get_object(builder, "loginButton"));

    // Connect the "clicked" signal of the login button to the on_loginButton_clicked function
    g_signal_connect(loginButton, "clicked", G_CALLBACK(on_loginButton_clicked), builder);

    // Connect the "destroy" signal of the window to the g_application_quit function
    g_signal_connect_swapped(window, "destroy", G_CALLBACK(g_application_quit), app);

    gtk_application_add_window(app, GTK_WINDOW(window));
    gtk_widget_show_all(window);
}

int main(int argc, char *argv[])
{
    GtkApplication *app;

    app = gtk_application_new("login.gtk.app", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

    return g_application_run(G_APPLICATION(app), argc, argv);
}