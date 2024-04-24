#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <gdk-pixbuf/gdk-pixbuf.h>
#include <stdbool.h>
#include "/Users/tranquangsang/Desktop/lamtailoi/shop-management/src/Product/product.h"
#define MAX_PRODUCT 100
void create_and_show_window();
void create_and_show_window1();
void showProduct(void);

Product productsArr[MAX_PRODUCT];
int initIndex = 0;
int currentPage = 1;
int totalPages = 1;
int productsPerPage = 8;

bool isIdUnique(const char *id)
{
    for (int i = 0; i < initIndex; i++)
    {
        if (strcmp(productsArr[i].id, id) == 0)
        {
            return false;
        }
    }
    return true;
}

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

void on_next_button_clicked(GtkWidget *button, gpointer data)
{
    GtkWindow *window = GTK_WINDOW(data);
    gtk_window_close(window);
    create_and_show_window();
}

void on_back_button_clicked(GtkWidget *button, gpointer user_data)
{
}

void addProduct(Product productsArr[], const char *id, const char *name, float price, int quantity, const char *img)
{
    // Create a new product
    Product newProduct;
    strcpy(newProduct.id, id);
    strcpy(newProduct.name, name);
    newProduct.price = price;
    newProduct.quantity = quantity;
    strcpy(newProduct.img, img);

    // Add the new product to the array
    productsArr[initIndex] = newProduct;
    initIndex++;

    // Write the new product to the file
    FILE *file = fopen("/Users/tranquangsang/Desktop/lamtailoi/shop-management/src/textDB/products.csv", "a");
    if (file != NULL)
    {
        fprintf(file, "%s,%s,%.2f,%d,%s\n", newProduct.id, newProduct.name, newProduct.price, newProduct.quantity, newProduct.img);
        fclose(file);
    }
    else
    {
        printf("Failed to open file\n");
    }
}

void on_confirmButton_clicked(GtkButton *button, gpointer user_data)
{
    GtkBuilder *builder = (GtkBuilder *)user_data;
    GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(builder, "addProduct"));
    GtkWidget *entryID = GTK_WIDGET(gtk_builder_get_object(builder, "idEntry"));
    GtkWidget *entryName = GTK_WIDGET(gtk_builder_get_object(builder, "nameEntry"));
    GtkWidget *entryPrice = GTK_WIDGET(gtk_builder_get_object(builder, "priceEntry"));
    GtkWidget *entryQuantity = GTK_WIDGET(gtk_builder_get_object(builder, "quantityEntry"));

    if (!GTK_IS_ENTRY(entryID) || !GTK_IS_ENTRY(entryName) || !GTK_IS_ENTRY(entryPrice) || !GTK_IS_ENTRY(entryQuantity))
    {
        g_critical("One or more widgets are not GtkEntry");
        return;
    }

    const char *id = gtk_entry_get_text(GTK_ENTRY(entryID));
    const char *name = gtk_entry_get_text(GTK_ENTRY(entryName));
    const char *priceText = gtk_entry_get_text(GTK_ENTRY(entryPrice));
    const char *quantityText = gtk_entry_get_text(GTK_ENTRY(entryQuantity));

    double price = atof(priceText);
    int quantity = atoi(quantityText);
    if (!isIdUnique(id))
    {
        // Show a dialog to notify that the ID already exists
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "ID already exists!");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }

    addProduct(productsArr, id, name, price, quantity, "images/char/1.jpg");

        // Show a dialog to notify
    GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "Product added successfully!");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);

    // Clear the entry fields after adding the product
    gtk_entry_set_text(GTK_ENTRY(entryID), "");
    gtk_entry_set_text(GTK_ENTRY(entryName), "");
    gtk_entry_set_text(GTK_ENTRY(entryPrice), "");
    gtk_entry_set_text(GTK_ENTRY(entryQuantity), "");

    // Set the focus back to the ID entry field
    gtk_widget_grab_focus(entryID);
}

void removeProduct(Product productsArr[], char id[])
{
    // Find the product with the given ID
    int index = -1;
    for (int i = 0; i < initIndex; i++)
    {
        if (strcmp(productsArr[i].id, id) == 0)
        {
            index = i;
            break;
        }
    }

    // If the product is found
    if (index != -1)
    {
        // Remove the product from the array
        for (int i = index; i < initIndex - 1; i++)
        {
            productsArr[i] = productsArr[i + 1];
        }
        initIndex--;

        // Write the updated products to the file
        FILE *file = fopen("/Users/tranquangsang/Desktop/lamtailoi/shop-management/src/textDB/products.csv", "w");
        if (file != NULL)
        {
            for (int i = 0; i < initIndex; i++)
            {
                fprintf(file, "%s,%s,%.2f,%d,%s\n", productsArr[i].id, productsArr[i].name, productsArr[i].price, productsArr[i].quantity, productsArr[i].img);
            }
            fclose(file);
        }
        else
        {
            printf("Failed to open file\n");
        }
    }
}

void on_delete_clicked(GtkButton *button, gpointer user_data)
{
    GtkBuilder *builder = (GtkBuilder *)user_data;
    GtkWidget *entryID = GTK_WIDGET(gtk_builder_get_object(builder, "productId"));
    if (!GTK_IS_ENTRY(entryID))
    {
        g_critical("Widget is not GtkEntry");
        return;
    }
    char *idCopy = g_strdup(gtk_entry_get_text(GTK_ENTRY(entryID)));
    removeProduct(productsArr, idCopy);
    g_free(idCopy);
    GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(builder, "deleteProduct"));
    GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "Product deleted successfully!");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

void on_but3_clicked(GtkButton *button, gpointer user_data)
{
    GtkBuilder *builder;
    GtkWidget *window;
    GtkButton *confirmButton;

    builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, "/Users/tranquangsang/Desktop/lamtailoi/shop-management/src/Shop/deleteProduct.glade", NULL);
    window = GTK_WIDGET(gtk_builder_get_object(builder, "deleteProduct"));
    confirmButton = GTK_BUTTON(gtk_builder_get_object(builder, "confirmButton"));
    g_signal_connect(G_OBJECT(confirmButton), "clicked", G_CALLBACK(on_delete_clicked), builder);

    gtk_builder_connect_signals(builder, NULL);

    gtk_widget_show_all(window);
}

void editProduct(Product productsArr[], const char *id, const char *name, float price, int quantity, const char *img)
{
    // Find the product with the given ID
    int index = -1;
    for (int i = 0; i < initIndex; i++)
    {
        if (strcmp(productsArr[i].id, id) == 0)
        {
            index = i;
            break;
        }
    }

    if (index != -1)
    {
        // Update the product's information
        strcpy(productsArr[index].name, name);
        productsArr[index].price = price;
        productsArr[index].quantity = quantity;
        strcpy(productsArr[index].img, img);

        // Write the updated products to the file
        FILE *file = fopen("/Users/tranquangsang/Desktop/lamtailoi/shop-management/src/textDB/products.csv", "w");
        if (file != NULL)
        {
            for (int i = 0; i < initIndex; i++)
            {
                if (strcmp(productsArr[i].id, id) == 0)
                {
                    fprintf(file, "%s,%s,%.2f,%d,%s\n", id, name, price, quantity, "images/char/1.jpg");
                }
                else
                {
                    fprintf(file, "%s,%s,%.2f,%d,%s\n", productsArr[i].id, productsArr[i].name, productsArr[i].price, productsArr[i].quantity, productsArr[i].img);
                }
            }
            fclose(file);
        }
        else
        {
            printf("Failed to open file\n");
        }
    }
}

void on_updateButton_clicked(GtkButton *button, gpointer user_data)
{
    GtkBuilder *builder = (GtkBuilder *)user_data;

    GtkWidget *entryID = GTK_WIDGET(gtk_builder_get_object(builder, "productId"));
    GtkWidget *entryName = GTK_WIDGET(gtk_builder_get_object(builder, "entryName"));
    GtkWidget *entryPrice = GTK_WIDGET(gtk_builder_get_object(builder, "entryPrice"));
    GtkWidget *entryQuantity = GTK_WIDGET(gtk_builder_get_object(builder, "entryQuantity"));
    puts(gtk_entry_get_text(GTK_ENTRY(entryID)));
    puts(gtk_entry_get_text(GTK_ENTRY(entryName)));
    puts(gtk_entry_get_text(GTK_ENTRY(entryPrice)));
    puts(gtk_entry_get_text(GTK_ENTRY(entryQuantity)));
    if (!GTK_IS_ENTRY(entryID) || !GTK_IS_ENTRY(entryName) || !GTK_IS_ENTRY(entryPrice) || !GTK_IS_ENTRY(entryQuantity))
    {
        g_critical("One or more widgets are not GtkEntry");
        return;
    }

    const char *id = gtk_entry_get_text(GTK_ENTRY(entryID));
    const char *name = gtk_entry_get_text(GTK_ENTRY(entryName));
    const char *priceText = gtk_entry_get_text(GTK_ENTRY(entryPrice));
    const char *quantityText = gtk_entry_get_text(GTK_ENTRY(entryQuantity));

    double price = atof(priceText);
    int quantity = atoi(quantityText);

    editProduct(productsArr, id, name, price, quantity, "images/char/1.jpg");

    GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(builder, "editProduct"));

    GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "Product updated successfully!");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);

    gtk_entry_set_text(GTK_ENTRY(entryID), "");
    gtk_entry_set_text(GTK_ENTRY(entryName), "");
    gtk_entry_set_text(GTK_ENTRY(entryPrice), "");
    gtk_entry_set_text(GTK_ENTRY(entryQuantity), "");

    gtk_widget_grab_focus(entryID);
}

void on_but2_clicked(GtkButton *button, gpointer user_data)
{
    GtkBuilder *builder;
    GtkWidget *window;
    GtkButton *updateButton;

    builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, "/Users/tranquangsang/Desktop/lamtailoi/shop-management/src/Shop/editProduct.glade", NULL);

    window = GTK_WIDGET(gtk_builder_get_object(builder, "editProduct"));

    updateButton = GTK_BUTTON(gtk_builder_get_object(builder, "updateButton"));

    if (updateButton == NULL)
    {
        g_critical("updateButton is NULL");
        return;
    }

    g_signal_connect(G_OBJECT(updateButton), "clicked", G_CALLBACK(on_updateButton_clicked), builder);

    gtk_builder_connect_signals(builder, NULL);

    gtk_widget_show_all(window);
}

void on_but1_clicked(GtkButton *button, gpointer user_data)
{
    GtkBuilder *builder;
    GtkWidget *window;
    GtkButton *confirmButton;

    builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, "/Users/tranquangsang/Desktop/lamtailoi/shop-management/src/Shop/addProduct.glade", NULL);

    window = GTK_WIDGET(gtk_builder_get_object(builder, "addProduct"));

    confirmButton = GTK_BUTTON(gtk_builder_get_object(builder, "confirmButton"));
    g_signal_connect(G_OBJECT(confirmButton), "clicked", G_CALLBACK(on_confirmButton_clicked), builder);

    gtk_builder_connect_signals(builder, NULL);

    gtk_widget_show_all(window);
}


void on_refreshButton_clicked( GtkWidget *button, gpointer user_data)
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
    create_and_show_window();

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
    // exit
    GtkWidget *exit;
    // pages
    GtkWidget *next, *back;
    GtkWidget *pagenum;
    // fixed
    GtkWidget *fixed;
    // box
    GtkWidget *box1, *box2, *box3, *box4, *box5, *box6, *box7, *box8;
    // buttonAdd
    GtkWidget *buttonAdd1, *buttonAdd2, *buttonAdd3, *buttonAdd4, *buttonAdd5, *buttonAdd6, *buttonAdd7, *buttonAdd8;
    // label
    GtkWidget *label1, *label2, *label3, *label4, *label5, *label6, *label7, *label8;
    // products images
    GtkWidget *img1, *img2, *img3, *img4, *img5, *img6, *img7, *img8;
    // products
    GtkWidget *product1, *product2, *product3, *product4, *product5, *product6, *product7, *product8;
    // price
    GtkWidget *gia1, *gia2, *gia3, *gia4, *gia5, *gia6, *gia7, *gia8;

    // menu, search bar, verticalbox_left
    GtkWidget *menu, *VerticalBox_Left, *hboxsear;

    GtkWidget *searchLabel;
    GtkWidget *searchProducts;
    GtkWidget *searchButton;

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
    g_signal_connect(G_OBJECT(but1), "clicked", G_CALLBACK(on_but1_clicked), NULL);

    but2 = gtk_button_new_with_label("Edit products");
    if (but2 == NULL)
    {
        printf("Failed to create but2\n");
        return;
    }
    g_signal_connect(but2, "clicked", G_CALLBACK(on_but2_clicked), NULL);

    but3 = gtk_button_new_with_label("Delete products");
    if (but3 == NULL)
    {
        printf("Failed to create but3\n");
        return;
    }
    g_signal_connect(but3, "clicked", G_CALLBACK(on_but3_clicked), NULL);

    exit = gtk_button_new_with_label("Exit");
    if (exit == NULL)
    {
        printf("Failed to create exit button\n");
        return;
    }
    gtk_fixed_put(GTK_FIXED(fixed), exit, 1300, 25);
    g_signal_connect(exit, "clicked", G_CALLBACK(on_exitButton_clicked), window);

    gtk_fixed_put(GTK_FIXED(fixed), but1, 25, 550);
    gtk_fixed_put(GTK_FIXED(fixed), but2, 25, 600);
    gtk_fixed_put(GTK_FIXED(fixed), but3, 25, 650);

    g_signal_connect(exit, "clicked", G_CALLBACK(gtk_widget_destroy), window);

    gtk_container_add(GTK_CONTAINER(window), fixed);

    searchLabel = gtk_label_new("Search product: ");
    searchButton = gtk_button_new_from_icon_name("system-search", 1);
    searchProducts = gtk_search_entry_new();

    hboxsear = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_pack_start(GTK_BOX(hboxsear), searchLabel, 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(hboxsear), searchProducts, 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(hboxsear), searchButton, 0, 0, 0);

    gtk_fixed_put(GTK_FIXED(fixed), hboxsear, 650, 50);

    menu = gtk_label_new("ID       NAME      PRICE");
    gtk_widget_set_name(menu, "menu");
    VerticalBox_Left = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    gtk_box_pack_start(GTK_BOX(VerticalBox_Left), menu, TRUE, 0, 0);

    gtk_widget_set_name(VerticalBox_Left, "VerticalBox_Left");

    gtk_fixed_put(GTK_FIXED(fixed), VerticalBox_Left, 35, 50);

    pagenum = gtk_label_new("Page : 1");
    gtk_fixed_put(GTK_FIXED(fixed), pagenum, 1300, 150);


    /////////////////////////////-//////////////////////////////

    // Read products from products.csv
    FILE *file = fopen("/Users/tranquangsang/Desktop/lamtailoi/shop-management/src/textDB/products.csv", "r");
    if (file == NULL) {
        printf("Failed to open file\n");
        return;
    }

    char line[100];
    int count = 0;

    while (fgets(line, sizeof(line), file)) {
        // Parse the line to get product details
        char *id = strtok(line, ",");
        char *name = strtok(NULL, ",");
        char *price = strtok(NULL, ",");

        // Create box for each product
        GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

        // Create button, image, label, and price for the product
        GtkWidget *button = gtk_button_new_with_label("Select");
        GtkWidget *img = gtk_image_new_from_file("images/char/1.jpg");
        GtkWidget *label = gtk_label_new(name);
        GtkWidget *priceLabel = gtk_label_new(price);

        // Set name for label
        gtk_widget_set_name(label, id);

        // Pack the widgets into the box
        gtk_box_pack_start(GTK_BOX(box), button, 0, 0, 5);
        gtk_box_pack_start(GTK_BOX(box), img, TRUE, TRUE, 5);
        gtk_box_pack_start(GTK_BOX(box), label, 0, 0, 5);
        gtk_box_pack_start(GTK_BOX(box), priceLabel, 0, 0, 5);

        // Set spacing and name for the box
        gtk_box_set_spacing(GTK_BOX(box), 10);
        gtk_widget_set_name(box, id);

        // Set size request for the box
        gtk_widget_set_size_request(box, 100, 100);

        // Calculate the position to put the box
        int x = 400 + (count % 4) * 200;
        int y = 120 + (count / 4) * 200;

        // Put the box into the fixed container
        gtk_fixed_put(GTK_FIXED(fixed), box, x, y);

        count++;
    }
    fclose(file);

    // Refresh button
    GtkWidget *refreshButton;
    refreshButton = gtk_button_new_with_label("Refresh");
    g_signal_connect(refreshButton, "clicked", G_CALLBACK(on_refreshButton_clicked), window);
    gtk_fixed_put(GTK_FIXED(fixed), refreshButton, 1300, 550);

    /////////////////////////////-//////////////////////////////

    // box2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    // img2 = gtk_image_new_from_file("images/char/2.png");
    // label2 = gtk_label_new("ID2");
    // gtk_widget_set_name(label2, "id2");
    // buttonAdd2 = gtk_button_new_with_label("Select");

    // gtk_box_pack_start(GTK_BOX(box2), buttonAdd2, 0, 0, 5);

    // gtk_box_pack_start(GTK_BOX(box2), img2, 0, 0, 5);

    // gtk_box_pack_start(GTK_BOX(box2), label2, 0, 0, 5);

    // gtk_box_pack_start(GTK_BOX(box2), gia2, 0, 0, 5);

    // gtk_box_set_spacing(GTK_BOX(box2), 10);

    // gtk_widget_set_name(box2, "box2");

    // gtk_fixed_put(GTK_FIXED(fixed), box2, 600, 120);

    // /////////////////////////////-//////////////////////////////

    // box3 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    // img3 = gtk_image_new_from_file("images/char/3.png");
    // label3 = gtk_label_new("ID3");
    // gtk_widget_set_name(label3, "id3");
    // buttonAdd3 = gtk_button_new_with_label("Select");

    // gtk_box_pack_start(GTK_BOX(box3), buttonAdd3, 0, 0, 5);

    // gtk_box_pack_start(GTK_BOX(box3), img3, 0, 0, 5);

    // gtk_box_pack_start(GTK_BOX(box3), label3, 0, 0, 5);

    // gtk_box_pack_start(GTK_BOX(box3), gia3, 0, 0, 5);

    // gtk_box_set_spacing(GTK_BOX(box3), 10);

    // gtk_widget_set_name(box3, "box3");

    // gtk_fixed_put(GTK_FIXED(fixed), box3, 800, 120);

    // /////////////////////////////-//////////////////////////////

    // box4 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    // img4 = gtk_image_new_from_file("images/char/4.png");
    // label4 = gtk_label_new("ID4");
    // gtk_widget_set_name(label4, "id4");
    // buttonAdd4 = gtk_button_new_with_label("Select");

    // gtk_box_pack_start(GTK_BOX(box4), buttonAdd4, 0, 0, 5);

    // gtk_box_pack_start(GTK_BOX(box4), img4, 0, 0, 5);

    // gtk_box_pack_start(GTK_BOX(box4), label4, 0, 0, 5);

    // gtk_box_pack_start(GTK_BOX(box4), gia4, 0, 0, 5);

    // gtk_box_set_spacing(GTK_BOX(box4), 10);

    // gtk_widget_set_name(box4, "box4");

    // gtk_fixed_put(GTK_FIXED(fixed), box4, 1000, 120);

    // /////////////////////////////-//////////////////////////////

    // box5 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    // buttonAdd5 = gtk_button_new_with_label("Select");
    // img5 = gtk_image_new_from_file("images/char/5.png");
    // label5 = gtk_label_new("ID5");
    // gtk_widget_set_name(label5, "id5");

    // gtk_box_pack_start(GTK_BOX(box5), buttonAdd5, 0, 0, 5);

    // gtk_box_pack_start(GTK_BOX(box5), img5, 0, 0, 5);

    // gtk_box_pack_start(GTK_BOX(box5), label5, 0, 0, 5);

    // gtk_box_pack_start(GTK_BOX(box5), gia5, 0, 0, 5);

    // gtk_box_set_spacing(GTK_BOX(box5), 10);

    // gtk_widget_set_name(box5, "box5");

    // gtk_fixed_put(GTK_FIXED(fixed), box5, 400, 400);

    // /////////////////////////////-//////////////////////////////

    // box6 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    // buttonAdd6 = gtk_button_new_with_label("Select");
    // img6 = gtk_image_new_from_file("images/char/6.png");
    // label6 = gtk_label_new("ID6");
    // gtk_widget_set_name(label6, "id6");

    // gtk_box_pack_start(GTK_BOX(box6), buttonAdd6, 0, 0, 5);

    // gtk_box_pack_start(GTK_BOX(box6), img6, 0, 0, 5);

    // gtk_box_pack_start(GTK_BOX(box6), label6, 0, 0, 5);

    // gtk_box_pack_start(GTK_BOX(box6), gia6, 0, 0, 5);

    // gtk_box_set_spacing(GTK_BOX(box6), 10);

    // gtk_widget_set_name(box6, "box6");

    // gtk_fixed_put(GTK_FIXED(fixed), box6, 600, 400);

    // /////////////////////////////-//////////////////////////////

    // box7 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    // buttonAdd7 = gtk_button_new_with_label("Select");
    // img7 = gtk_image_new_from_file("images/char/7.png");
    // label7 = gtk_label_new("ID7");
    // gtk_widget_set_name(label6, "id7");

    // gtk_box_pack_start(GTK_BOX(box7), buttonAdd7, 0, 0, 5);

    // gtk_box_pack_start(GTK_BOX(box7), img7, 0, 0, 5);

    // gtk_box_pack_start(GTK_BOX(box7), label7, 0, 0, 5);

    // gtk_box_pack_start(GTK_BOX(box7), gia7, 0, 0, 5);

    // gtk_box_set_spacing(GTK_BOX(box7), 10);

    // gtk_widget_set_name(box7, "box7");

    // gtk_fixed_put(GTK_FIXED(fixed), box7, 800, 400);

    // /////////////////////////////-//////////////////////////////

    // box8 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    // buttonAdd8 = gtk_button_new_with_label("Select");
    // img8 = gtk_image_new_from_file("images/char/8.png");
    // label8 = gtk_label_new("ID8");
    // gtk_widget_set_name(label6, "id8");

    // gtk_box_pack_start(GTK_BOX(box8), buttonAdd8, 0, 0, 5);

    // gtk_box_pack_start(GTK_BOX(box8), img8, 0, 0, 5);

    // gtk_box_pack_start(GTK_BOX(box8), label8, 0, 0, 5);

    // gtk_box_pack_start(GTK_BOX(box8), gia8, 0, 0, 5);

    // gtk_box_set_spacing(GTK_BOX(box8), 10);

    // gtk_widget_set_name(box8, "box8");

    // gtk_fixed_put(GTK_FIXED(fixed), box8, 1000, 400);

    back = gtk_button_new_with_label("Back");
    g_signal_connect(G_OBJECT(back), "clicked", G_CALLBACK(on_back_button_clicked), window);

    next = gtk_button_new_with_label("Next");
    g_signal_connect(G_OBJECT(next), "clicked", G_CALLBACK(on_next_button_clicked), window);

    // g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_fixed_put(GTK_FIXED(fixed), next, 1300, 600);
    gtk_fixed_put(GTK_FIXED(fixed), back, 1300, 650);

    // Initialize
    gtk_window_set_title(GTK_WINDOW(window), "Showing product");

    // Showing the product window
    gtk_widget_show_all(window);
}

// void create_and_show_window1()
// {
//     showProduct();
//     GtkWidget *window;
//     // button
//     GtkWidget *but1;
//     GtkWidget *but2;
//     GtkWidget *but3;
//     // exit
//     GtkWidget *exit;
//     // pages
//     GtkWidget *next, *back;
//     // fixed
//     GtkWidget *fixed;
//     // box
//     GtkWidget *box1, *box2, *box3, *box4, *box5, *box6, *box7, *box8;
//     // buttonAdd
//     GtkWidget *buttonAdd1, *buttonAdd2, *buttonAdd3, *buttonAdd4, *buttonAdd5, *buttonAdd6, *buttonAdd7, *buttonAdd8;
//     // label
//     GtkWidget *label1, *label2, *label3, *label4, *label5, *label6, *label7, *label8;
//     // products images
//     GtkWidget *img1, *img2, *img3, *img4, *img5, *img6, *img7, *img8;

//     // menu, search bar, verticalbox_left
//     GtkWidget *menu, *VerticalBox_Left, *hboxsear;

//     GtkWidget *searchLabel;
//     GtkWidget *searchProducts;
//     GtkWidget *searchButton;

//     window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
//     if (window == NULL)
//     {
//         printf("Failed to create window\n");
//         return;
//     }
//     // Initialize the size of product window
//     gtk_window_set_default_size(GTK_WINDOW(window), 1400, 700);

//     fixed = gtk_fixed_new();
//     if (fixed == NULL)
//     {
//         printf("Failed to create fixed\n");
//         return;
//     }

//     but1 = gtk_button_new_with_label("Add products");
//     if (but1 == NULL)
//     {
//         printf("Failed to create but1\n");
//         return;
//     }
//     but2 = gtk_button_new_with_label("Edit products");
//     if (but2 == NULL)
//     {
//         printf("Failed to create but2\n");
//         return;
//     }
//     but3 = gtk_button_new_with_label("Delete products");
//     if (but3 == NULL)
//     {
//         printf("Failed to create but3\n");
//         return;
//     }
//     exit = gtk_button_new_with_label("Exit");
//     if (exit == NULL)
//     {
//         printf("Failed to create exit button\n");
//         return;
//     }
//     gtk_fixed_put(GTK_FIXED(fixed), exit, 1300, 25);
//     g_signal_connect(exit, "clicked", G_CALLBACK(on_exitButton_clicked), window);

//     gtk_fixed_put(GTK_FIXED(fixed), but1, 25, 550);
//     gtk_fixed_put(GTK_FIXED(fixed), but2, 25, 600);
//     gtk_fixed_put(GTK_FIXED(fixed), but3, 25, 650);

//     g_signal_connect(window, "delete-event", G_CALLBACK(gtk_main_quit), NULL);

//     gtk_container_add(GTK_CONTAINER(window), fixed);

//     // Initialize
//     gtk_window_set_title(GTK_WINDOW(window), "Showing product");

//     // Showing the product window
//     gtk_widget_show_all(window);
// }

void showProduct() {
    GtkWidget *tree_view;
    GtkListStore *list_store;
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;

    // Create a new GtkTreeView and a GtkListStore
    tree_view = gtk_tree_view_new();
    list_store = gtk_list_store_new(3, G_TYPE_STRING, G_TYPE_STRING, GDK_TYPE_PIXBUF);

    // Set up the columns
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Product ID", renderer, "text", 0, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column);

    column = gtk_tree_view_column_new_with_attributes("Product Name", renderer, "text", 1, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column);

    column = gtk_tree_view_column_new_with_attributes("Product Price", renderer, "text", 2, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column);

    // Connect the model to the view
    gtk_tree_view_set_model(GTK_TREE_VIEW(tree_view), GTK_TREE_MODEL(list_store));

    //grid
    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 10);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 10);

    FILE *file = fopen("/Users/tranquangsang/Desktop/lamtailoi/shop-management/src/textDB/products.csv", "r");
    if (file != NULL) {
        char line[128];
        int row = 0;
        while (fgets(line, sizeof line, file) != NULL) {
        char *id, *name, *price;
        GtkWidget *box, *label;

        // Parse the CSV line
        id = strtok(line, ",");
        name = strtok(NULL, ",");
        price = strtok(NULL, ",");

        // Create a GtkBox for the product
        box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
        label = gtk_label_new(name);
        gtk_box_pack_start(GTK_BOX(box), label, TRUE, TRUE, 0);
        label = gtk_label_new(price);
        gtk_box_pack_start(GTK_BOX(box), label, TRUE, TRUE, 0);

        // Add the GtkBox to the GtkGrid
        gtk_grid_attach(GTK_GRID(grid), box, row % 3, row / 3, 1, 1);
        row++;
    }
    fclose(file);
    }
}


int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);

    create_and_show_window();


    gtk_main();

    return 0;
}