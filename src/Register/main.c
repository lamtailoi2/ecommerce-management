#include <gtk/gtk.h>
#include <stdio.h>
#include "/Users/tranquangsang/Desktop/lamtailoi/shop-management/src/Headers/password.h"
#include <stdbool.h>
#include <string.h>


gboolean validate_registration(const char *username, const char *email, const char *password)
{

    return username[0] != '\0' && email[0] != '\0' && password[0] != '\0';
}

// Encrypt the password
void encrypt_password(const char *password, char *encryptedPassword, int key)
{
    int i = 0;
    while (password[i] != '\0')
    {
        encryptedPassword[i] = password[i] + key;
        i++;
    }
    encryptedPassword[i] = '\0';
}

// Write the user details to a CSV file
void write_user_to_csv(const char *username, const char *email, const char *password)
{
    FILE *file = freopen("/Users/tranquangsang/Desktop/lamtailoi/shop-management/src/textDB/users.csv", "a", stdout);

    if (file != NULL)
    {
        // Encrypt the password before storing
        char encryptedPassword[256];
        encrypt_password(password, encryptedPassword, 69); // encrypt

        fprintf(file, "%s, %s, %s\n", username, email, encryptedPassword); // store user to csv
        fclose(file);
    }
    else
    {
        printf("Failed to open \n");
    }
}

// check valid email
bool is_valid_email(const char *email)
{
    // Check if the email contains an '@' symbol
    const char *atSymbol = strchr(email, '@');
    if (atSymbol == NULL)
    {
        return false;
    }

    // Check if the email contains a dot after the '@' symbol
    const char *dotSymbol = strchr(atSymbol, '.');
    if (dotSymbol == NULL)
    {
        return false;
    }

    // Check if the dot symbol is not the last character in the email
    if (dotSymbol == email + strlen(email) - 1)
    {
        return false;
    }

    return true;
}

bool is_password_match(const char *password, const char *confirmPassword)
{
    // Compare the password and confirm password
    if (strcmp(password, confirmPassword) == 0)
    {
        return true;
    }
    return false;
}

bool is_valid_username(const char *username)
{
    // Check if the username is empty
    if (username[0] != '\0')
    {
        puts(username);
    }
    if (username[0] == '\0')
    {
        return false;
    }
    return true;
}

bool is_valid_password(const char *password)
{
    // Check if the password is empty
    if (password[0] == '\0')
    {
        return false;
    }
    // Check if the password length is at least 8 characters
    if (strlen(password) < 8)
    {
        return false;
    }
    return true;
}

bool is_unique_username(const char *username)
{
    FILE *file = freopen("/Users/tranquangsang/Desktop/lamtailoi/shop-management/src/textDB/users.csv", "r", stdin);
    if (file != NULL)
    {
        char line[256];
        while (fgets(line, sizeof(line), file))
        {
            char storedUsername[256];
            sscanf(line, "%[^,],", storedUsername);
            if (strcmp(username, storedUsername) == 0)
            {
                fclose(file);
                return false;
            }
        }
        fclose(file);
    }
    return true;
}

bool is_unique_email(const char *email)
{
    FILE *file = freopen("/Users/tranquangsang/Desktop/lamtailoi/shop-management/src/textDB/users.csv", "r", stdin);
    if (file != NULL)
    {
        char line[256];
        while (fgets(line, sizeof(line), file))
        {
            char storedEmail[256];
            sscanf(line, "%*[^,], %[^,]", storedEmail);
            if (strcmp(email, storedEmail) == 0)
            {
                fclose(file);
                return false;
            }
        }
        fclose(file);
    }
    return true;
}

void on_registerButton_clicked(GtkButton *button, gpointer user_data)
{
    // get value from user
    GtkBuilder *builder = GTK_BUILDER(user_data);
    GtkEntry *usernameEntry = GTK_ENTRY(gtk_builder_get_object(builder, "usernameEntry"));
    GtkEntry *emailEntry = GTK_ENTRY(gtk_builder_get_object(builder, "emailEntry"));
    GtkEntry *passwordEntry = GTK_ENTRY(gtk_builder_get_object(builder, "passwordEntry"));
    GtkEntry *confirmPasswordEntry = GTK_ENTRY(gtk_builder_get_object(builder, "confirmPasswordEntry"));

    if (!is_valid_username(gtk_entry_get_text(passwordEntry)))
    {
        // The username is not valid. Show an error message.
        GtkWidget *dialog;
        dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Invalid username!");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }

    if (!is_unique_username(gtk_entry_get_text(usernameEntry)))
    {
        // The username is already taken. Show an error message.
        GtkWidget *dialog;
        dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Username is already taken!");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }

    if (!is_valid_password(gtk_entry_get_text(passwordEntry)))
    {
        // The password is not valid. Show an error message.
        GtkWidget *dialog;
        dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Invalid password!");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }
    if (!is_valid_email(gtk_entry_get_text(emailEntry)))
    {
        // The email is not valid. Show an error message.
        GtkWidget *dialog;
        dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Invalid email!");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }

    if (!is_unique_email(gtk_entry_get_text(emailEntry)))
    {
        // The email is already taken. Show an error message.
        GtkWidget *dialog;
        dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Email is already taken!");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }

    if (!is_password_match(gtk_entry_get_text(passwordEntry), gtk_entry_get_text(confirmPasswordEntry)))
    {
        // The passwords do not match. Show an error message.
        GtkWidget *dialog;
        dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Passwords do not match!");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }
    // The registration is successful. Show a success message.
    GtkWidget *dialog;
    dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "Registration successful!");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
    const char *username = gtk_entry_get_text(usernameEntry); // get value from user
    const char *email = gtk_entry_get_text(emailEntry);
    const char *password = gtk_entry_get_text(passwordEntry);
    write_user_to_csv(username, email, password);
    
    // if (validate_registration(username, email, password))
    // {
    //     // The registration details are valid. Open the home page.
    //     gtk_widget_destroy(register);
    // }
    // else
    // {
    //     // The registration details are invalid. Show an error message.
    //     GtkWidget *dialog;
    //     dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Invalid registration details!");
    //     gtk_dialog_run(GTK_DIALOG(dialog));
    //     gtk_widget_destroy(dialog);
    // }
    
    

    // if (validate_registration(username, email, password))
    // {
    //     // The registration details are valid. Open the home page.
    //     gtk_widget_destroy(register);
    // }
    // else
    // {
    //     // The registration details are invalid. Show an error message.
    //     GtkWidget *dialog;
    //     dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Invalid registration details!");
    //     gtk_dialog_run(GTK_DIALOG(dialog));
    //     gtk_widget_destroy(dialog);
    // }
}

void activate(GtkApplication *app, gpointer user_data)
{
    GtkBuilder *builder;
    GtkWidget *window;
    GtkWidget *registerButton;

    builder = gtk_builder_new_from_file("/Users/tranquangsang/Desktop/lamtailoi/shop-management/src/Register/Register.glade");
    window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
    registerButton = GTK_WIDGET(gtk_builder_get_object(builder, "registerButton"));

    // set title
    gtk_window_set_title(GTK_WINDOW(window), "Register");

    // Connect the "clicked" signal of the register button to the on_registerButton_clicked function
    g_signal_connect(registerButton, "clicked", G_CALLBACK(on_registerButton_clicked), builder);

    // Connect the "destroy" signal of the window to the g_application_quit function
    g_signal_connect_swapped(window, "destroy", G_CALLBACK(g_application_quit), app);

    gtk_application_add_window(app, GTK_WINDOW(window));
    gtk_widget_show_all(window);
}

int main(int argc, char *argv[])
{
    GtkApplication *app;

    app = gtk_application_new("register.gtk.app", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}
