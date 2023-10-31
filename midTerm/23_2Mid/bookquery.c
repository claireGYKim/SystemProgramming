bookquery.c
#include <stdio.h>
#include <stdlib.h>

// Define constants
#define START_ID 1
#define MAX_NAME_LENGTH 100
#define MAX_CATEGORY_LENGTH 100

// Define a struct to store product information
struct Product {
    int id;
    char bookname[MAX_NAME_LENGTH];
    char writer[MAX_CATEGORY_LENGTH];
    int date;
    int count;
    int yesno;
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

    printf("Input command number : ");
    scanf("%d", &command); // Enter the command number

    if (command == 0) { // Display information for all products
        printf("%-8s %-8s %-8s %-5s %-3s %-3s\n", "ID", "Book Name", "Writer", "Date", "Count", "Stock");
        while (fread(&product, sizeof(product), 1, file) > 0) {
            printf("%8d %8s %8s %5d %3d %3d\n", product.id, product.bookname, product.writer, product.date,
                   product.count, product.yesno);
        }

    } else { // Display information for products available for loan
        printf("%-8s %-8s %-8s %-5s %-3s %-3s\n", "ID", "Book Name", "Writer", "Date", "Count", "Stock");
        while (fread(&product, sizeof(product), 1, file) > 0) {
            if (product.count > 0 && product.date >= 2023) {
                printf("%8d %8s %8s %5d %3d %3d\n", product.id, product.bookname, product.writer, product.date,
                       product.count, product.yesno);
            }
        }
    }

    // Close the file
    fclose(file);

    return 0;
}

