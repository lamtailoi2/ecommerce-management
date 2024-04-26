#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <gdk-pixbuf/gdk-pixbuf.h>
#include <stdbool.h>
#include <gdk-pixbuf/gdk-pixbuf.h>
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
Product cartList[MAX_PRODUCT];
int cartIndex = 0;

void add_to_cart(Product product)
{
    if (cartIndex < MAX_PRODUCT)
    {
        cartList[cartIndex] = product;
        cartIndex++;
    }
    else
    {
        printf("Cart is full\n");
    }
}

Product getSelectedProduct(GtkWidget *button)
{
    GtkWidget *box = gtk_widget_get_parent(button);
    // Get the list of child widgets of the box
    GList *children = gtk_container_get_children(GTK_CONTAINER(box));
    // Get the third child from the list
    GtkWidget *label = GTK_WIDGET(g_list_nth_data(children, 1));
    const char *id = gtk_label_get_text(GTK_LABEL(label));
    g_list_free(children); // Free the list when you're done with it
    FILE *file = fopen("/Users/tranquangsang/Desktop/lamtailoi/shop-management/src/textDB/products.csv", "r");
    if (file != NULL)
    {
        char line[100];
        while (fgets(line, sizeof(line), file))
        {
            char *productId = strtok(line, ",");
            if (strcmp(productId, id) == 0)
            {
                fclose(file);
                Product selectedProduct;
                strcpy(selectedProduct.id, productId);
                strcpy(selectedProduct.name, strtok(NULL, ","));
                selectedProduct.price = atof(strtok(NULL, ","));
                selectedProduct.quantity = atoi(strtok(NULL, ","));
                strcpy(selectedProduct.img, strtok(NULL, ","));
                return selectedProduct;
            }
        }
        fclose(file);
    }
    Product emptyProduct;
    return emptyProduct;
}

void updateProductQuantity(Product product, int newQuantity, const char *id) {
    
     // Read all products from the file into itemsArr
    FILE *file = fopen("/Users/tranquangsang/Desktop/lamtailoi/shop-management/src/textDB/products.csv", "r");
    if (file != NULL)
    {
        Product itemsArr[MAX_PRODUCT];
        int initIndex = 0;
        char line[256];
        while (fgets(line, sizeof(line), file))
        {
            char *token = strtok(line, ",");
            strcpy(itemsArr[initIndex].id, token);
            token = strtok(NULL, ",");
            strcpy(itemsArr[initIndex].name, token);
            token = strtok(NULL, ",");
            itemsArr[initIndex].price = atof(token);
            token = strtok(NULL, ",");
            itemsArr[initIndex].quantity = atoi(token);
            token = strtok(NULL, ",");
            token[strcspn(token, "\n")] = 0; // Remove the newline character from the end of token
            strcpy(itemsArr[initIndex].img, token);
            initIndex++;
        }
        fclose(file);

        // Find the product with the given ID and update its information
        bool found = false;
        for (int i = 0; i < initIndex; i++)
        {
            if (strcmp(itemsArr[i].id, id) == 0)
            {
                // strcpy(itemsArr[i].name, name);
                // itemsArr[i].price = price;
                itemsArr[i].quantity = newQuantity;
                // strcpy(itemsArr[i].img, img);
                found = true;
                break;
            }
        }

        // Write the updated products back to the file
        file = fopen("/Users/tranquangsang/Desktop/lamtailoi/shop-management/src/textDB/products.csv", "w");
        if (file != NULL)
        {
            for (int i = 0; i < initIndex; i++)
            {
                fprintf(file, "%s,%s,%.2f,%d,%s\n", itemsArr[i].id, itemsArr[i].name, itemsArr[i].price, itemsArr[i].quantity, itemsArr[i].img);
            }
            fclose(file);
        }
    }
}

void on_selectButton_clicked(GtkWidget *button, gpointer user_data)
{
    Product selected_product = getSelectedProduct(button);
    int cnt = 0;
    printf("Selected Product:\n");
    printf("Product ID: %s\n", selected_product.id);
    printf("Product Name: %s\n", selected_product.name);
    printf("Product Price: %.2f\n", selected_product.price);
    printf("Product Quantity: %d\n", selected_product.quantity);
    printf("Product Image: %s\n", selected_product.img);
    if (cartIndex < 100)
    {
        
    if (selected_product.quantity > 0)
    {
        // Check if the cart is not full
        printf("Current Quantity: %d\n", selected_product.quantity);
        cartList[cartIndex] = selected_product;
        int current = selected_product.quantity -= 1;
        cartIndex++;
        updateProductQuantity(selected_product, current, selected_product.id);  // Update quantity in products.csv
    }
        else
        {
            GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(user_data), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Product is out of stock!");
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
        }
    }
    else
    {
        g_print("Cart is full\n");
    }
    printf("Current Quantity: %d\n", selected_product.quantity);
}

bool isIdUnique(const char *id)
{
    FILE *file = fopen("/Users/tranquangsang/Desktop/lamtailoi/shop-management/src/textDB/products.csv", "r");
    if (file != NULL)
    {
        char line[100];
        while (fgets(line, sizeof(line), file))
        {
            char *token = strtok(line, ",");
            if (token != NULL && strcmp(token, id) == 0)
            {
                fclose(file);
                return false;
            }
        }
        fclose(file);
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

// Added function for Payment button
void on_Payment_button_clicked(GtkWidget *button, gpointer user_data)
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

void removeProduct(const char *id)
{
    Product itemsArr[100];
    int initIndex = 0;

    // Read all products from the file into itemsArr
    FILE *file = fopen("/Users/tranquangsang/Desktop/lamtailoi/shop-management/src/textDB/products.csv", "r");
    if (file != NULL)
    {
        char line[100];
        while (fgets(line, sizeof(line), file))
        {
            char *productId = strtok(line, ",");
            char *name = strtok(NULL, ",");
            char *price = strtok(NULL, ",");
            char *quantity = strtok(NULL, ",");
            char *img = strtok(NULL, ",");
            if (productId != NULL && name != NULL && price != NULL && quantity != NULL && img != NULL)
            {
                strcpy(itemsArr[initIndex].id, productId);
                strcpy(itemsArr[initIndex].name, name);
                itemsArr[initIndex].price = atof(price);
                itemsArr[initIndex].quantity = atoi(quantity);
                img[strcspn(img, "\n")] = 0; // Remove the newline character from the end of img
                strcpy(itemsArr[initIndex].img, img);
                initIndex++;
            }
        }
        fclose(file);
    }
    // Find the product with the given ID and remove it from itemsArr
    for (int i = 0; i < initIndex; i++)
    {
        if (strcmp(itemsArr[i].id, id) == 0)
        {
            for (int j = i; j < initIndex - 1; j++)
            {
                itemsArr[j] = itemsArr[j + 1];
            }
            initIndex--;
            break;
        }
    }

    // Write the remaining products back to the file
    file = fopen("/Users/tranquangsang/Desktop/lamtailoi/shop-management/src/textDB/products.csv", "w");
    if (file != NULL)
    {
        for (int i = 0; i < initIndex; i++)
        {
            if (i != 0)
            {
                fprintf(file, "\n");
            }
            fprintf(file, "%s,%s,%.2f,%d,%s", itemsArr[i].id, itemsArr[i].name, itemsArr[i].price, itemsArr[i].quantity, itemsArr[i].img);
        }
        fclose(file);
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
    removeProduct(idCopy);
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

void editProduct(const char *id, const char *name, float price, int quantity, const char *img)
{
    // Read all products from the file into itemsArr
    FILE *file = fopen("/Users/tranquangsang/Desktop/lamtailoi/shop-management/src/textDB/products.csv", "r");
    if (file != NULL)
    {
        Product itemsArr[MAX_PRODUCT];
        int initIndex = 0;
        char line[256];
        while (fgets(line, sizeof(line), file))
        {
            char *token = strtok(line, ",");
            strcpy(itemsArr[initIndex].id, token);
            token = strtok(NULL, ",");
            strcpy(itemsArr[initIndex].name, token);
            token = strtok(NULL, ",");
            itemsArr[initIndex].price = atof(token);
            token = strtok(NULL, ",");
            itemsArr[initIndex].quantity = atoi(token);
            token = strtok(NULL, ",");
            token[strcspn(token, "\n")] = 0; // Remove the newline character from the end of token
            strcpy(itemsArr[initIndex].img, token);
            initIndex++;
        }
        fclose(file);

        // Find the product with the given ID and update its information
        bool found = false;
        for (int i = 0; i < initIndex; i++)
        {
            if (strcmp(itemsArr[i].id, id) == 0)
            {
                strcpy(itemsArr[i].name, name);
                itemsArr[i].price = price;
                itemsArr[i].quantity = quantity;
                strcpy(itemsArr[i].img, img);
                found = true;
                break;
            }
        }

        // Write the updated products back to the file
        file = fopen("/Users/tranquangsang/Desktop/lamtailoi/shop-management/src/textDB/products.csv", "w");
        if (file != NULL)
        {
            for (int i = 0; i < initIndex; i++)
            {
                fprintf(file, "%s,%s,%.2f,%d,%s\n", itemsArr[i].id, itemsArr[i].name, itemsArr[i].price, itemsArr[i].quantity, itemsArr[i].img);
            }
            fclose(file);
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

    editProduct(id, name, price, quantity, "images/char/1.jpg");

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

void on_refreshButton_clicked(GtkWidget *button, gpointer user_data)
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

void on_deleteCart_clicked(GtkWidget *widget, gpointer user_data)
{
    int indexToRemove = atoi(gtk_entry_get_text(GTK_ENTRY(user_data))); // Assuming user_data is a GtkEntry widget where the user inputs the index to remove

    if (indexToRemove >= 0 && indexToRemove < cartIndex)
    {
        // Shift elements to the left
        for (int i = indexToRemove; i < cartIndex - 1; i++)
        {
            cartList[i] = cartList[i + 1];
        }
        cartIndex--;
        create_and_show_window();
        // Refresh the display of cartList
    }
}

void on_cash_button_clicked(GtkButton *button, gpointer user_data)
{
    g_print("Cash button clicked\n");
}

void on_card_button_clicked(GtkButton *button, gpointer user_data)
{
    g_print("Card button clicked\n");
}

void printOrders(const char *customerNameText, const char *customerPhoneText, const char *customerAddressText, const char *paymentMethod, double totalPrice)
{
    FILE *file = fopen("/Users/tranquangsang/Desktop/lamtailoi/shop-management/src/textDB/orders.csv", "a");
    if (file == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    fprintf(file, "%s,%s,%s,%s,%.2f\n", customerNameText, customerPhoneText, customerAddressText, paymentMethod, totalPrice);
    fclose(file);
}

void on_order_button_clicked(GtkButton *button, gpointer user_data)
{

    for (int i = 0; i < cartIndex; i++)
    {
        cartList[i] = (Product){0}; // Clear each element of the cartList array
    }
    cartIndex = 0; // Reset the cartIndex to 0
    create_and_show_window();
    GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(user_data), GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "Order successful");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
    gtk_widget_hide(GTK_WIDGET(user_data));
}

// void on_paymentButton_clicked(GtkWidget *widget, gpointer user_data) {
//     GtkBuilder *builder;
//     GtkWidget *window;

//     builder = gtk_builder_new();
//     gtk_builder_add_from_file(builder, "/Users/tranquangsang/Desktop/lamtailoi/shop-management/src/Shop/Payment.glade", NULL);

//     window = GTK_WIDGET(gtk_builder_get_object(builder, "payment"));

//     gtk_builder_connect_signals(builder, NULL);

//     gtk_widget_show_all(window);
// }

void on_paymentButton_clicked(GtkWidget *widget, gpointer user_data)
{
    GtkBuilder *builder;
    GtkWidget *window;

    builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, "/Users/tranquangsang/Desktop/lamtailoi/shop-management/src/Shop/Payment.glade", NULL);

    window = GTK_WIDGET(gtk_builder_get_object(builder, "payment"));

    GtkButton *cash_radio_button = GTK_BUTTON(gtk_builder_get_object(builder, "cash"));
    GtkButton *card_radio_button = GTK_BUTTON(gtk_builder_get_object(builder, "card"));
    GtkButton *order_button;

    GtkWidget *totalPriceLabel;
    totalPriceLabel = GTK_WIDGET(gtk_builder_get_object(builder, "totalLabel"));
    GtkTextView *textView = GTK_TEXT_VIEW(gtk_builder_get_object(builder, "totalPrice"));
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(textView);
    char totalPriceText[100];
    float totalPrice = 0;
    for (int i = 0; i < cartIndex; i++)
    {
        totalPrice += cartList[i].price;
    }
    sprintf(totalPriceText, "Total Price: %.2f", totalPrice);
    gtk_label_set_text(GTK_LABEL(totalPriceLabel), totalPriceText);
    gtk_text_buffer_set_text(buffer, totalPriceText, -1);

    GtkEntry *customerName = GTK_ENTRY(gtk_builder_get_object(builder, "customerName"));
    GtkEntry *customerPhone = GTK_ENTRY(gtk_builder_get_object(builder, "phoneNumber"));
    GtkEntry *customerAddress = GTK_ENTRY(gtk_builder_get_object(builder, "address"));

    if (customerName == NULL)
    {
        g_printerr("customerName is NULL\n");
    }
    if (customerPhone == NULL)
    {
        g_printerr("customerPhone is NULL\n");
    }
    if (customerAddress == NULL)
    {
        g_printerr("customerAddress is NULL\n");
    }
    const char *paymentMethod;
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(cash_radio_button)))
    {
        paymentMethod = "Cash";
    }
    else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(card_radio_button)))
    {
        paymentMethod = "Card";
    }
    else
    {
        paymentMethod = "Cash";
    }

    const char *customerNameText = gtk_entry_get_text(customerName);
    const char *customerPhoneText = gtk_entry_get_text(customerPhone);
    const char *customerAddressText = gtk_entry_get_text(customerAddress);
    puts(customerNameText);
    printOrders(gtk_entry_get_text(customerName), customerPhoneText, customerAddressText, paymentMethod, totalPrice);

    order_button = GTK_BUTTON(gtk_builder_get_object(builder, "orderButton"));

    g_signal_connect(cash_radio_button, "clicked", G_CALLBACK(on_cash_button_clicked), NULL);
    g_signal_connect(order_button, "clicked", G_CALLBACK(on_order_button_clicked), window);

    gtk_builder_connect_signals(builder, NULL);

    gtk_widget_show_all(window);
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
    // Exit button position fixed
    gtk_fixed_put(GTK_FIXED(fixed), exit, 25, 25);
    g_signal_connect(exit, "clicked", G_CALLBACK(on_exitButton_clicked), window);

    gtk_fixed_put(GTK_FIXED(fixed), but1, 25, 550);
    gtk_fixed_put(GTK_FIXED(fixed), but2, 25, 600);
    gtk_fixed_put(GTK_FIXED(fixed), but3, 25, 650);

    g_signal_connect(exit, "clicked", G_CALLBACK(gtk_widget_destroy), window);

    gtk_container_add(GTK_CONTAINER(window), fixed);

    // Search label position fixed to the middle of products review
    searchLabel = gtk_label_new("Search product: ");
    searchButton = gtk_button_new_from_icon_name("system-search", 1);
    searchProducts = gtk_search_entry_new();

    hboxsear = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_pack_start(GTK_BOX(hboxsear), searchLabel, 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(hboxsear), searchProducts, 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(hboxsear), searchButton, 0, 0, 0);

    gtk_fixed_put(GTK_FIXED(fixed), hboxsear, 593, 50);

    // Added ID search label
    GtkWidget *searchIDLabel = gtk_label_new("Delete: ");
    GtkWidget *deleteCart = gtk_button_new_from_icon_name("edit-delete", 1);
    GtkWidget *productIndex = gtk_entry_new();
    g_signal_connect(deleteCart, "clicked", G_CALLBACK(on_deleteCart_clicked), productIndex);

    GtkWidget *hboxsear1 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_pack_start(GTK_BOX(hboxsear1), searchIDLabel, 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(hboxsear1), productIndex, 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(hboxsear1), deleteCart, 0, 0, 0);

    gtk_fixed_put(GTK_FIXED(fixed), hboxsear1, 1150, 550);

    // Added Payment button
    GtkWidget *payment = gtk_button_new_with_label("Payment");
    g_signal_connect(payment, "clicked", G_CALLBACK(on_paymentButton_clicked), payment);
    gtk_fixed_put(GTK_FIXED(fixed), payment, 1250, 600);

    // Cart with position fixed to the right of window
    // Create a label for the menu
    menu = gtk_label_new("");
    gtk_widget_set_name(menu, "menu");

    // Create a vertical box
    VerticalBox_Left = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    // Add the menu to the vertical box
    gtk_box_pack_start(GTK_BOX(VerticalBox_Left), menu, TRUE, 0, 0);

    // Create a TreeView and a ListStore for the cart items
    GtkListStore *liststore = gtk_list_store_new(3, G_TYPE_INT, G_TYPE_STRING, G_TYPE_DOUBLE);
    GtkTreeView *treeview = GTK_TREE_VIEW(gtk_tree_view_new_with_model(GTK_TREE_MODEL(liststore)));

    // Create the TreeView columns
    GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
    GtkTreeViewColumn *column = gtk_tree_view_column_new_with_attributes("Index", renderer, "text", 0, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);
    column = gtk_tree_view_column_new_with_attributes("Name", renderer, "text", 1, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);
    column = gtk_tree_view_column_new_with_attributes("Price", renderer, "text", 2, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    // Add the TreeView to the vertical box
    gtk_box_pack_start(GTK_BOX(VerticalBox_Left), GTK_WIDGET(treeview), TRUE, TRUE, 0);

    // Populate the ListStore with items from the cartList array
    GtkTreeIter iter;
    for (int i = 0; i < cartIndex; i++)
    {
        gtk_list_store_append(liststore, &iter);
        gtk_list_store_set(liststore, &iter, 0, i, 1, cartList[i].name, 2, cartList[i].price, -1);
    }

    // Set the name of the vertical box and add it to the fixed container
    gtk_widget_set_name(VerticalBox_Left, "VerticalBox_Left");
    gtk_fixed_put(GTK_FIXED(fixed), VerticalBox_Left, 1230, 100);

    /////////////////////////////-//////////////////////////////

    // Read products from products.csv
    FILE *file = fopen("/Users/tranquangsang/Desktop/lamtailoi/shop-management/src/textDB/products.csv", "r");
    if (file == NULL)
    {
        printf("Failed to open file\n");
        return;
    }

    char line[100];
    int count = 0;

    while (fgets(line, sizeof(line), file))
    {
        // Parse the line to get product details
        char *id = strtok(line, ",");
        char *name = strtok(NULL, ",");
        char *price = strtok(NULL, ",");
        char *quantity = strtok(NULL, ",");

        // Create box for each product
        GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

        // Create button, image, label, and price for the product
        GtkWidget *button = gtk_button_new_with_label("Select");
        g_signal_connect(button, "clicked", G_CALLBACK(on_selectButton_clicked), NULL);
        GtkWidget *img = gtk_image_new_from_file("images/char/1.jpg");
        GtkWidget *label = gtk_label_new(g_strdup_printf("Name: %s", name));
        GtkWidget *idLabel = gtk_label_new(g_strdup_printf("%s", id));
        GtkWidget *priceLabel = gtk_label_new(g_strdup_printf("Price: %s", price));
        GtkWidget *quantityLabel = gtk_label_new(g_strdup_printf("Quantity: %s", quantity));
        // Set name for label
        gtk_widget_set_name(label, id);

        // Pack the widgets into the box
        gtk_box_pack_start(GTK_BOX(box), button, 0, 0, 5);
        gtk_box_pack_start(GTK_BOX(box), idLabel, 0, 0, 5);
        gtk_box_pack_start(GTK_BOX(box), img, TRUE, TRUE, 5);
        gtk_box_pack_start(GTK_BOX(box), label, 0, 0, 5);
        gtk_box_pack_start(GTK_BOX(box), quantityLabel, 0, 0, 5);
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
    gtk_fixed_put(GTK_FIXED(fixed), refreshButton, 1300, 25);

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

    // Back and next button position fixed to the top of products list
    gtk_fixed_put(GTK_FIXED(fixed), next, 1035, 50);
    gtk_fixed_put(GTK_FIXED(fixed), back, 400, 50);

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

int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);

    create_and_show_window();

    gtk_main();

    return 0;
}