#include <stdio.h>

// Constants
#define START_ID 1
#define MAX_NAME_LENGTH 100
#define MAX_CATEGORY_LENGTH 100

// Struct to store product information
struct Product {
    int id;
    char name[MAX_NAME_LENGTH];
    char category[MAX_CATEGORY_LENGTH];
    int date;
    int count;
};

int main(int argc, char* argv[]) {
    struct Product product;
    int command; // Command number
    FILE* file;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s file\n", argv[0]);
        return 1;
    }

    printf("Input command and product ID >> ");
    scanf("%d %d", &command, &product.id);

    file = fopen(argv[1], "rb+");

    if (command == 0) { // Input
        printf("Enter name, category, date, and count >> ");
        while (scanf("%s %s %d %d", product.name, product.category, &product.date, &product.count) == 4) {
            fseek(file, (product.id - START_ID) * sizeof(product), SEEK_SET);
            fwrite(&product, sizeof(product), 1, file);
        }
        printf("Input completed.\n");
    } else { // Deletion
        fseek(file, (product.id - START_ID) * sizeof(product), SEEK_SET);
        if ((fread(&product, sizeof(product), 1, file) > 0) && (product.id != 0)) {
            fwrite(&product, sizeof(product), 1, file);
        } else {
            printf("Product with ID %d not found or out of stock.\n", product.id);
        }
    }

    fclose(file);
    return 0;
}

