#include <gtk/gtk.h>

void on_exitButton_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *window = GTK_WIDGET(user_data);
    if (window != NULL && GTK_IS_WIDGET(window))
    {
        gtk_widget_destroy(window);
    }
    else
    {
        fprintf(stderr, "Error: 'window' is not a valid GtkWidget or is NULL\n");
    }
}

void create_and_show_window()
{
    // gulong handler_id = g_signal_connect(browseButton, "clicked", G_CALLBACK(on_browseButton_clicked), NULL);
    // // if (handler_id == 0)
    // // {
    // //     printf("Failed to connect signal\n");
    // // }
    // window
    GtkWidget *window;
    // button
    GtkWidget *but1;
    GtkWidget *but2;
    GtkWidget *but3;
    GtkWidget *exit;
    // fixed
    GtkWidget *fixed;

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    if (window == NULL)
    {
        printf("Failed to create window\n");
        return;
    }
    // Initialize the size of product window
    gtk_window_set_default_size(GTK_WINDOW(window), 1400, 700);

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

    // Initialize
    gtk_window_set_title(GTK_WINDOW(window), "Showing product");

    // Showing the product window
    gtk_widget_show_all(window);
}

int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);

    create_and_show_window();

    gtk_main();

    return 0;
}