#include "product.h"
#include <stdio.h>
#include <string.h>
int main() {
    // Create a new product
    Product p;
    
    // Set the product details
    strcpy(p.id, "12345");
    strcpy(p.name, "Example Product");
    p.price = 9.99;
    
    // Store the product in an Excel file
}