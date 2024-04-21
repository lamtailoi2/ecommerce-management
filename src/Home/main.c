#include <gtk/gtk.h>
#include <pthread.h>




void create_and_show_window() {
    GtkBuilder *builder;
    GtkWidget *window;

    builder = gtk_builder_new_from_file("/Users/tranquangsang/Desktop/lamtailoi/shop-management/src/Home/Home.glade");
    window = GTK_WIDGET(gtk_builder_get_object(builder, "homeWindow"));

    initialize_ui(builder);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_widget_show_all(window);
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    create_and_show_window();

    gtk_main();

    return 0;
}