#include <gtk/gtk.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>


void on_browse_button_clicked(GtkButton *button, gpointer user_data)
{
    gtk_widget_hide(GTK_WIDGET(user_data));
    int result = system("/Users/tranquangsang/Desktop/lamtailoi/shop-management/src/Shop/shop");
    if(result == -1)
    {
        perror("system");
    }
}

void create_and_show_window() {
    GtkBuilder *builder;
    GtkWidget *window;
    GtkButton *browse_button;

    builder = gtk_builder_new_from_file("/Users/tranquangsang/Desktop/lamtailoi/shop-management/src/Home/Home.glade");
    window = GTK_WIDGET(gtk_builder_get_object(builder, "homeWindow"));
    browse_button = GTK_BUTTON(gtk_builder_get_object(builder, "browseButton"));

    g_signal_connect(browse_button, "clicked", G_CALLBACK(on_browse_button_clicked), NULL);

    // initialize_ui(builder);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_widget_show_all(window);
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    create_and_show_window();

    gtk_main();

    return 0;
}