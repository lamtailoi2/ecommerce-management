#include <gtk/gtk.h>
#include <stdio.h>


// void on_registerButton_clicked(GtkButton *button, gpointer user_data)
// {
//     GtkBuilder *registerBuilder;
//     GtkWidget *registerWindow;

//     registerBuilder = gtk_builder_new_from_file("/Users/tranquangsang/Desktop/lamtailoi/shop-management/src/Register/Register.glade");
//     registerWindow = GTK_WIDGET(gtk_builder_get_object(registerBuilder, "window"));
    
//     // set title
//     gtk_window_set_title(GTK_WINDOW(registerWindow), "Register");

//     // Connect the "destroy" signal of the window to the g_application_quit function
//     g_signal_connect_swapped(registerWindow, "destroy", G_CALLBACK(g_application_quit), NULL);

//     gtk_widget_show_all(registerWindow);
// }

void on_registerButton_clicked(GtkButton *button, gpointer user_data)
{
    int result = system("/Users/tranquangsang/Desktop/lamtailoi/shop-management/src/Register/register");
    if (result == -1) {
        perror("system");
    }
    result = system("/Users/tranquangsang/Desktop/lamtailoi/shop-management/src/Home/myHome");
    if (result == -1) {
        perror("system");
    }
}

void on_loginButton_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *welcomeWindow = GTK_WIDGET(user_data);
    int result = system("/Users/tranquangsang/Desktop/lamtailoi/shop-management/src/Login/login");
    if (result == -1) {
        perror("system");
        return;
    }
    
}

void activate_app(GtkApplication *app, gpointer user_data)
{
    GtkBuilder *builder;
    GtkWidget *window;
    GtkWidget *registerButton;
    GtkWidget *loginButton;

    builder = gtk_builder_new_from_file("Welcome.glade");
    window = GTK_WIDGET(gtk_builder_get_object(builder, "mainWindow"));
    registerButton = GTK_WIDGET(gtk_builder_get_object(builder, "registerButton"));
    loginButton = GTK_WIDGET(gtk_builder_get_object(builder, "loginButton"));

    //set title
    gtk_window_set_title(GTK_WINDOW(window), "Welcome");

    // Connect the "clicked" signal of the register button to the on_registerButton_clicked function
    g_signal_connect(registerButton, "clicked", G_CALLBACK(on_registerButton_clicked), NULL);

    // Connect the "clicked" signal of the login button to the on_loginButton_clicked function
    g_signal_connect(loginButton, "clicked", G_CALLBACK(on_loginButton_clicked), NULL);

    // Connect the "destroy" signal of the window to the g_application_quit function
    g_signal_connect_swapped(window, "destroy", G_CALLBACK(g_application_quit), app);

    gtk_application_add_window(app, GTK_WINDOW(window));
    gtk_widget_show_all(window);
}

int main(int argc, char *argv[])
{
    GtkApplication *app;

    app = gtk_application_new("welcome.gtk.app", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate_app), NULL);
    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}