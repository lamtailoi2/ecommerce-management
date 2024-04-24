#include <gtk/gtk.h>

void on_exitButton_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *window = GTK_WIDGET(user_data);
    if (window != NULL)
    {
        gtk_widget_destroy(window);
    }
    else {
        printf("Failed to get parent window\n");
    }
     
}

void create_and_show_window()
{
    GtkWidget *window;
    GtkWidget *but1;
    GtkWidget *but2;
    GtkWidget *but3;
    GtkWidget *exit;
    GtkWidget *fixed;
    GtkWidget *header_bar;

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    if (window == NULL)
    {
        printf("Failed to create window\n");
        return;
    }

    gtk_window_set_default_size(GTK_WINDOW(window), 1400, 700);

    header_bar = gtk_header_bar_new();
    gtk_header_bar_set_show_close_button(GTK_HEADER_BAR(header_bar), TRUE);
    gtk_window_set_titlebar(GTK_WINDOW(window), header_bar);

    fixed = gtk_fixed_new();
    if (fixed == NULL)
    {
        printf("Failed to create fixed\n");
        return;
    }

    but1 = gtk_button_new_with_label("Add products");
    if (but1 == NULL)
    {
        printf("Failed to create but1\n");
        return;
    }
    but2 = gtk_button_new_with_label("Edit products");
    if (but2 == NULL)
    {
        printf("Failed to create but2\n");
        return;
    }
    but3 = gtk_button_new_with_label("Delete products");
    if (but3 == NULL)
    {
        printf("Failed to create but3\n");
        return;
    }
    exit = gtk_button_new_with_label("Exit");
    if (exit == NULL)
    {
        printf("Failed to create exit button\n");
        return;
    }
    gtk_fixed_put(GTK_FIXED(fixed), exit, 650, 350);
    g_signal_connect(exit, "clicked", G_CALLBACK(on_exitButton_clicked), window);

    gtk_fixed_put(GTK_FIXED(fixed), but1, 25, 550);
    gtk_fixed_put(GTK_FIXED(fixed), but2, 25, 600);
    gtk_fixed_put(GTK_FIXED(fixed), but3, 25, 650);

    gtk_fixed_put(GTK_FIXED(fixed), exit, 1400, 10);
    g_signal_connect(exit, "clicked", G_CALLBACK(gtk_widget_destroy), window);

    gtk_container_add(GTK_CONTAINER(window), fixed);

    gtk_window_set_title(GTK_WINDOW(window), "Showing product");

    gtk_widget_show_all(window);
}

int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);

    create_and_show_window();

    gtk_main();

    return 0;
}