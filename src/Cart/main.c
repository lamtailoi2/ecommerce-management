#include <gtk/gtk.h>

static void activate(GtkApplication *app, gpointer data)
{

    GtkWidget *window;

    GtkTextBuffer *buffer;

    GtkWidget *menuLabel;

    GtkWidget *textView, *leftSidevBox, *gridButton, *idDelEntry, *confirmDelButton, *backShowCartButton, *paymentButton;

    GtkWidget *hboxContainer, *hboxSearch, *hboxPage, *boxTop, *vboxContain; //container

    GtkWidget *GridItem;

    GtkWidget *box1, *box2, *box3, *box4, *box5, *box6, *box7, *box8, *box9, *box10; //box_gio_hang

    GtkWidget *img1, *img2, *img3, *img4, *img5, *img6, *img7, *img8, *img9, *img10; //img gio hang

    GtkWidget *searchLabel;
    GtkWidget *searchProducts;
    GtkWidget *searchButton;

    GtkWidget *id1, *id2, *id3, *id4, *id5, *id6, *id7, *id8, *id9, *id10;

    GtkWidget *product1, *product2, *product3, *product4, *product5, *product6, *product7, *product8, *product9, *product10;

    GtkWidget *price1, *price2, *price3, *price4, *price5, *price6, *price7, *price8, *price9, *price10;

    GtkWidget *buttonAdd1, *buttonAdd2, *buttonAdd3, *buttonAdd4, *buttonAdd5, *buttonAdd6, *buttonAdd7, *buttonAdd8, *buttonAdd9, *buttonAdd10;

    GtkWidget *buttonComboSearch, *buttonComboSort, *sortByLabel, *sortBox;

    GtkWidget *nextPage, *previousPage, *scrolled_bar;
    //

    scrolled_bar = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_bar),
                                  GTK_POLICY_AUTOMATIC,
                                  GTK_POLICY_AUTOMATIC);
    //gtk_container_set_border_width (GTK_CONTAINER (scrolled_window), 50);
    //gtk_scrolled_window_set_min_content_width(scrolled_bar, 400);
    //gtk_scrolled_window_set_min_content_height(scrolled_bar, 600);
    sortByLabel = gtk_label_new("Sort by: ");
    buttonComboSort = gtk_combo_box_new();
    gtk_combo_box_text_append_text(buttonComboSort, "A");
    gtk_combo_box_text_append_text(buttonComboSort, "B");
    gtk_combo_box_text_append_text(buttonComboSort, "C");
    gtk_combo_box_text_append_text(buttonComboSort, "D");

    sortBox = gtk_hbox_new(0, 10);
    gtk_box_pack_start(sortBox, sortByLabel, 0, 0, 0);
    gtk_box_pack_start(sortBox, buttonComboSort, 0, 0, 0);

    textView = gtk_text_view_new();
    buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (textView));
    gtk_text_view_set_wrap_mode(textView, GTK_WRAP_WORD);
    gtk_text_buffer_set_text (buffer, "                1                  Book1              $0", -1);
    gtk_text_view_set_editable(textView, FALSE);
    gtk_container_add(GTK_CONTAINER(scrolled_bar), textView);
    gtk_container_set_border_width (GTK_CONTAINER (scrolled_bar), 5);
    //
    searchLabel = gtk_label_new("Search product: ");
    searchButton = gtk_button_new_from_icon_name("system-search", 1);
    searchProducts = gtk_search_entry_new();
    gtk_widget_set_name(buttonComboSearch, "search");


    menuLabel = gtk_label_new("ID               NAME              PRICE");
    gtk_widget_set_name(menuLabel, "menuLabel");
    nextPage = gtk_button_new_with_label(">>>>>");
    previousPage = gtk_button_new_with_label("<<<<<");



    gridButton = gtk_grid_new();
    confirmDelButton = gtk_button_new_with_label("Delete");
    gtk_widget_set_name(confirmDelButton, "Delete");
    backShowCartButton = gtk_button_new_with_label("Back");
    paymentButton = gtk_button_new_with_label("Payment");
    idDelEntry = gtk_entry_new();
    gtk_entry_set_placeholder_text(idDelEntry,"Enter ID that you want to Delete");
    gtk_widget_set_name(idDelEntry, "delId");
    gtk_grid_attach(gridButton, idDelEntry, 0, 0, 2, 1);
    gtk_grid_attach(gridButton, confirmDelButton, 3, 0, 1, 1);
    gtk_grid_attach(gridButton, paymentButton, 0, 1, 1, 1);
    gtk_grid_attach(gridButton, backShowCartButton, 3, 1, 1, 1);
    gtk_grid_set_column_spacing(gridButton, 20);
    gtk_grid_set_row_spacing(gridButton, 20);

    gtk_widget_set_name(textView, "textView");
    leftSidevBox = gtk_vbox_new(0, 0);
    gtk_box_pack_start(leftSidevBox, menuLabel, 0, 0, 0);
    gtk_box_pack_start(leftSidevBox, scrolled_bar, TRUE, TRUE, 20);
    gtk_box_pack_end(leftSidevBox, gridButton, 0, 0, 0);

    gtk_widget_set_name(leftSidevBox, "leftSidevBox");
    gtk_widget_set_name(backShowCartButton, "backCart");
    gtk_widget_set_name(paymentButton, "paymentButton");
    id1 = gtk_label_new("ID1");
    gtk_widget_set_name(id1, "id1");
    id2 = gtk_label_new("ID2");
    gtk_widget_set_name(id2, "id2");
    id3 = gtk_label_new("ID3");
    gtk_widget_set_name(id3, "id3");
    id4 = gtk_label_new("ID4");
    gtk_widget_set_name(id4, "id4");
    id5 = gtk_label_new("ID5");
    gtk_widget_set_name(id5, "id5");
    id6 = gtk_label_new("ID6");
    gtk_widget_set_name(id6, "id6");
    id7 = gtk_label_new("ID7");
    gtk_widget_set_name(id7, "id7");
    id8 = gtk_label_new("ID8");
    gtk_widget_set_name(id8, "id8");
    id9 = gtk_label_new("ID9");
    gtk_widget_set_name(id9, "id9");
    id10 = gtk_label_new("ID10");
    gtk_widget_set_name(id10, "id10");

    product1 = gtk_label_new("product 1");
    product2 = gtk_label_new("product 2");
    product3 = gtk_label_new("product 3");
    product4 = gtk_label_new("product 4");
    product5 = gtk_label_new("product 5");
    product6 = gtk_label_new("product 6");
    product7 = gtk_label_new("product 7");
    product8 = gtk_label_new("product 8");
    product9 = gtk_label_new("product 9");
    product10 = gtk_label_new("product 10");


    price1 = gtk_label_new("$0.00");
    price2 = gtk_label_new("$0.00");
    price3 = gtk_label_new("$0.00");
    price4 = gtk_label_new("$0.00");
    price5 = gtk_label_new("$0.00");
    price6 = gtk_label_new("$0.00");
    price7 = gtk_label_new("$0.00");
    price8 = gtk_label_new("$0.00");
    price9 = gtk_label_new("$0.00");
    price10 = gtk_label_new("$0.00");

    buttonAdd1 = gtk_button_new_from_icon_name("list-add", 0);
    buttonAdd2 = gtk_button_new_from_icon_name("list-add", 0);
    buttonAdd3 = gtk_button_new_from_icon_name("list-add", 0);
    buttonAdd4 = gtk_button_new_from_icon_name("list-add", 0);
    buttonAdd5 = gtk_button_new_from_icon_name("list-add", 0);
    buttonAdd6 = gtk_button_new_from_icon_name("list-add", 0);
    buttonAdd7 = gtk_button_new_from_icon_name("list-add", 0);
    buttonAdd8 = gtk_button_new_from_icon_name("list-add", 0);
    buttonAdd9 = gtk_button_new_from_icon_name("list-add", 0);
    buttonAdd10 = gtk_button_new_from_icon_name("list-add", 0);

    img1 = gtk_image_new_from_file("images/0001.png");
    img2 = gtk_image_new_from_file("images/0001.png");
    img3 = gtk_image_new_from_file("images/0001.png");
    img4 = gtk_image_new_from_file("images/0001.png");
    img5 = gtk_image_new_from_file("images/0001.png");
    img6 = gtk_image_new_from_file("images/0001.png");
    img7 = gtk_image_new_from_file("images/0001.png");
    img8 = gtk_image_new_from_file("images/0001.png");
    img9 = gtk_image_new_from_file("images/0001.png");
    img10 = gtk_image_new_from_file("images/0001.png");

    box1 = gtk_vbox_new(0, 0);
    box2 = gtk_vbox_new(0, 0);
    box3 = gtk_vbox_new(0, 0);
    box4 = gtk_vbox_new(0, 0);
    box5 = gtk_vbox_new(0, 0);
    box6 = gtk_vbox_new(0, 0);
    box7 = gtk_vbox_new(0, 0);
    box8 = gtk_vbox_new(0, 0);
    box9 = gtk_vbox_new(0, 0);
    box10 = gtk_vbox_new(0, 0);

    gtk_box_pack_start(box1, id1, 0, 0, 5);
    gtk_box_pack_start(box1, img1, 0, 0, 5);
    gtk_box_pack_start(box1, product1, 0, 0, 5);
    gtk_box_pack_start(box1, price1, 0, 0, 5);
    gtk_box_pack_end(box1, buttonAdd1, 0, 0, 5);

    gtk_box_pack_start(box2, id2, 0, 0, 5);
    gtk_box_pack_start(box2, img2, 0, 0, 5);
    gtk_box_pack_start(box2, product2, 0, 0, 5);
    gtk_box_pack_start(box2, price2, 0, 0, 5);
    gtk_box_pack_end(box2, buttonAdd2, 0, 0, 5);

    gtk_box_pack_start(box3, id3, 0, 0, 5);
    gtk_box_pack_start(box3, img3, 0, 0, 5);
    gtk_box_pack_start(box3, product3, 0, 0, 5);
    gtk_box_pack_start(box3, price3, 0, 0, 5);
    gtk_box_pack_end(box3, buttonAdd3, 0, 0, 5);

    gtk_box_pack_start(box4, id4, 0, 0, 5);
    gtk_box_pack_start(box4, img4, 0, 0, 5);
    gtk_box_pack_start(box4, product4, 0, 0, 5);
    gtk_box_pack_start(box4, price4, 0, 0, 5);
    gtk_box_pack_end(box4, buttonAdd4, 0, 0, 5);

    gtk_box_pack_start(box5, id5, 0, 0, 5);
    gtk_box_pack_start(box5, img5, 0, 0, 5);
    gtk_box_pack_start(box5, product5, 0, 0, 5);
    gtk_box_pack_start(box5, price5, 0, 0, 5);
    gtk_box_pack_end(box5, buttonAdd5, 0, 0, 5);

    gtk_box_pack_start(box6, id6, 0, 0, 5);
    gtk_box_pack_start(box6, img6, 0, 0, 5);
    gtk_box_pack_start(box6, product6, 0, 0, 5);
    gtk_box_pack_start(box6, price6, 0, 0, 5);
    gtk_box_pack_end(box6, buttonAdd6, 0, 0, 5);


    gtk_box_pack_start(box7, id7, 0, 0, 5);
    gtk_box_pack_start(box7, img7, 0, 0, 5);
    gtk_box_pack_start(box7, product7, 0, 0, 5);
    gtk_box_pack_start(box7, price7, 0, 0, 5);
    gtk_box_pack_end(box7, buttonAdd7, 0, 0, 5);

    gtk_box_pack_start(box8, id8, 0, 0, 5);
    gtk_box_pack_start(box8, img8, 0, 0, 5);
    gtk_box_pack_start(box8, product8, 0, 0, 5);
    gtk_box_pack_start(box8, price8, 0, 0, 5);
    gtk_box_pack_end(box8, buttonAdd8, 0, 0, 5);

    gtk_box_pack_start(box9, id9, 0, 0, 5);
    gtk_box_pack_start(box9, img9, 0, 0, 5);
    gtk_box_pack_start(box9, product9, 0, 0, 5);
    gtk_box_pack_start(box9, price9, 0, 0, 5);
    gtk_box_pack_end(box9, buttonAdd9, 0, 0, 5);

    gtk_box_pack_start(box10, id10, 0, 0, 5);
    gtk_box_pack_start(box10, img10, 0, 0, 5);
    gtk_box_pack_start(box10, product10, 0, 0, 5);
    gtk_box_pack_start(box10, price10, 0, 0, 5);
    gtk_box_pack_end(box10, buttonAdd10, 0, 0, 5);

    gtk_widget_set_name(box1 ,"box1");
    gtk_widget_set_name(box2 ,"box2");
    gtk_widget_set_name(box3 ,"box3");
    gtk_widget_set_name(box4 ,"box4");
    gtk_widget_set_name(box5 ,"box5");
    gtk_widget_set_name(box6 ,"box6");
    gtk_widget_set_name(box7 ,"box7");
    gtk_widget_set_name(box8 ,"box8");
    gtk_widget_set_name(box9 ,"box9");
    gtk_widget_set_name(box10 ,"box10");


    GridItem = gtk_grid_new();
    gtk_grid_attach(GridItem, box1, 0, 0, 1, 1);
    gtk_grid_attach(GridItem, box2, 1, 0, 1, 1);
    gtk_grid_attach(GridItem, box3, 2, 0, 1, 1);
    gtk_grid_attach(GridItem, box4, 3, 0, 1, 1);
    gtk_grid_attach(GridItem, box5, 4, 0, 1, 1);
    gtk_grid_attach(GridItem, box6, 0, 1, 1, 1);
    gtk_grid_attach(GridItem, box7, 1, 1, 1, 1);
    gtk_grid_attach(GridItem, box8, 2, 1, 1, 1);
    gtk_grid_attach(GridItem, box9, 3, 1, 1, 1);
    gtk_grid_attach(GridItem, box10, 4, 1, 1, 1);

    hboxSearch = gtk_hbox_new(0, 0);
    gtk_box_pack_start(hboxSearch, searchLabel, 0, 0, 0);
    gtk_box_pack_start(hboxSearch, searchProducts, 0, 0, 0);
    //gtk_box_pack_start(hboxSearch, buttonComboSearch, 0, 0, 0);
    gtk_box_pack_start(hboxSearch, searchButton, 0, 0, 0);
    gtk_box_pack_start(hboxSearch, sortBox, 0, 0, 0);
    gtk_box_pack_end(hboxSearch, nextPage, 0, 0, 0);
    gtk_box_pack_end(hboxSearch, previousPage, 0, 0, 0);


    vboxContain = gtk_vbox_new(0, 0);
    gtk_box_pack_start(vboxContain, hboxSearch, 0, 0, 0);
    gtk_box_pack_start(vboxContain, GridItem, 0, 0, 0);

    hboxContainer = gtk_hbox_new(0, 0);
    gtk_box_pack_start(hboxContainer, vboxContain, 0, 0, 0);
    gtk_box_pack_start(hboxContainer, leftSidevBox, 0, 0, 0);
    gtk_widget_set_name(hboxSearch, "hboxSearch");
    gtk_widget_set_name(vboxContain, "vboxContain");
    window = gtk_application_window_new(app);
	gtk_window_set_title(GTK_WINDOW(window), "shopping cart");
	gtk_window_set_default_size(GTK_WINDOW(window),1000, 700);
	gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	gtk_container_add(window, hboxContainer);
	gtk_widget_show_all(window);
}
int main(int argc, char **argv)
{
    GtkAllocation *app;
	int status;
	app = gtk_application_new("app.shopping.cart", G_APPLICATION_FLAGS_NONE);
	g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
	status = g_application_run(G_APPLICATION(app), argc, argv);
	g_object_unref(app);
	return status;
}