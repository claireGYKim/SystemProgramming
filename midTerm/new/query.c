#include <stdio.h>
#include <stdlib.h>

// Define constants
#define START_ID 1
#define MAX_NAME_LENGTH 100
#define MAX_CATEGORY_LENGTH 100

// Define a struct to store product information
struct Product {
    int id;
    char name[MAX_NAME_LENGTH];
    char category[MAX_CATEGORY_LENGTH];
    int date;
    int count;
};

int main(int argc, char* argv[]) {
    int command;
    struct Product product;
    FILE* file;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s file\n", argv[0]);
        return 1;
    }

    // Open the file for reading
    if ((file = fopen(argv[1], "rb")) == NULL) {
        fprintf(stderr, "Error opening the file\n");
        return 2;
    }

    printf("Input command number >> ");
    scanf("%d", &command); // Enter the command number

    if (command == 0) { // Display information for all products
        printf("%-8s %-8s %-8s %-5s %-3s\n", "Product ID", "Product Name", "Category", "Expiry Date", "Stock");
        while (fread(&product, sizeof(product), 1, file) > 0) {
            printf("%8d %8s %8s %5d %3d\n", product.id, product.name, product.category, product.date, 
product.count);
        }
    } else { // Display information for products available for sale
        printf("%-8s %-8s %-8s %-5s %-3s\n", "Product ID", "Product Name", "Category", "Expiry Date", "Stock");
        while (fread(&product, sizeof(product), 1, file) > 0) {
            if (product.count > 0 && product.date >= 2023) {
                printf("%8d %8s %8s %5d %3d\n", product.id, product.name, product.category, product.date, 
product.count);
            }
        }
    }

    // Close the file
    fclose(file);

    return 0;
}

