bookcreate.c
#include <stdio.h>

// Constants
#define START_ID 1
#define MAX_NAME_LENGTH 100
#define MAX_CATEGORY_LENGTH 100

// Struct to store product information
struct Product {
    int id;
    char bookname[MAX_NAME_LENGTH];
    char writer[MAX_CATEGORY_LENGTH];
    int date;
    int count;
    int yesno;
};

int main(int argc, char* argv[]) {
    struct Product product;
    int command; // Command number
    FILE* file;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s file\n", argv[0]);
        return 1;
    }

    printf("Input ID : ");
    scanf("%d %d", &command, &product.id);

    file = fopen(argv[1], "rb+");

    if (command == 0) { // Input
        printf("Enter bookname, writer, date, count and yesno : ");
        while (scanf("%s %s %d %d %d", product.bookname, product.writer, &product.date, &product.count, &product.yesno) == 5) {
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



