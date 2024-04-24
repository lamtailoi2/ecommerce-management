#ifndef PRODUCT_H
#define PRODUCT_H
#include <stdio.h>

typedef struct 
{
    char id[100];
    char name[100];
    float price;
    int quantity;
    char img[100];
} Product;

void addProduct(Product productsArr[], const char *id, const char *name, float price, int quantity, const char *img);
void removeProduct(Product productsArr[], char id[]);
void editProduct(Product productsArr[], const char *id, const char *name, float price, int quantity, const char *img);
void totalPrice(Product *p);
#endif