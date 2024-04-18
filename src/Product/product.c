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
    FILE *file = fopen("/path/to/excel/file.xlsx", "a");
    if (file != NULL) {
        fprintf(file, "%d,%s,%.2f\n", p.id, p.name, p.price);
        fclose(file);
        printf("Product stored in Excel file successfully.\n");
    } else {
        printf("Failed to open Excel file.\n");
    }
}