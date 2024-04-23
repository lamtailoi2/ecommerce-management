#include <gtk/gtk.h>
#include <stdio.h>

void on_cash_button_clicked(GtkButton *button, gpointer user_data)
{
    g_print("Cash button clicked\n");
}

void on_card_button_clicked(GtkButton *button, gpointer user_data)
{
    g_print("Card button clicked\n");
}

void on_order_button_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(user_data), GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "Order successful");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
    gtk_widget_hide(GTK_WIDGET(user_data));
}

void on_back_button_clicked(GtkButton *button, gpointer user_data)
{
    gtk_widget_hide(GTK_WIDGET(user_data));
}

void activate_app(GtkApplication *app, gpointer user_data)
{
    GtkBuilder *builder;
    GtkWidget *window;
    GtkButton *cash_radio_button;
    GtkButton *card_radio_button;
    GtkButton *order_button;
    GtkButton *back_button;

    builder = gtk_builder_new_from_file("Payment3.glade");
    window = GTK_WIDGET(gtk_builder_get_object(builder, "payment"));
    cash_radio_button = GTK_BUTTON(gtk_builder_get_object(builder, "cash"));
    card_radio_button = GTK_BUTTON(gtk_builder_get_object(builder, "card"));
    order_button = GTK_BUTTON(gtk_builder_get_object(builder, "orderButton"));
    back_button = GTK_BUTTON(gtk_builder_get_object(builder, "backButton"));

    g_signal_connect(cash_radio_button, "clicked", G_CALLBACK(on_cash_button_clicked), NULL);
    g_signal_connect(order_button, "clicked", G_CALLBACK(on_order_button_clicked), window);
    g_signal_connect(back_button, "clicked", G_CALLBACK(on_back_button_clicked), window);

    // gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);

    gtk_application_add_window(app, GTK_WINDOW(window));
    gtk_widget_show_all(window);
}

int main(int argc, char *argv[])
{
    GtkApplication *app;

    app = gtk_application_new("payment.gtk.app", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate_app), NULL);
    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}