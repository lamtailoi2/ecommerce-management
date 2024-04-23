#ifndef PRODUCT_H
#define PRODUCT_H
#include <stdio.h>

typedef struct 
{
    char id[100];
    char name[100];
    float price;
    int quantity;
} Product;

void addProduct(Product *p, char id[], char name[], float price, int quantity);
void removeProduct(Product *p, char id[]);
void updateProduct(Product *p, char id[], char name[], float price, int quantity);
void totalPrice(Product *p);
#endif