#ifndef ORDER_H
#define ORDER_H

#include <stdio.h>


typedef struct 
{
    int quantity;
    char orderID[10];
    float totalPrice;
    char customerName[50];
    char customerAddress[100];
    char customerPhone[10];
    enum paymentMethod {CASH, CARD} paymentMethod;
    int orderStatus;
} Order;

void addOrder(Order *o, int quantity, float totalPrice, char customerName[], char customerAddress[], char customerPhone[], char paymentMethod[], int orderStatus);
void removeOrder(Order *o, int orderID);
void updateOrder(Order *o, int orderID, int quantity, float totalPrice, char customerName[], char customerAddress[], char customerPhone[], char paymentMethod[], int orderStatus);



#endif // ORDER_H