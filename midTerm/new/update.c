#include <stdio.h>
#include <string.h>

struct Store {
    int id;
    char name[100];
    char category[100];
    int date;
    int count;
};

#define START_ID 1

void sellProduct(FILE *fp, int productId, struct Store *rec);
void printInventory(FILE *fp, struct Store *rec);

int main(int argc, char* argv[]) {
    FILE *fp;
    char cmd[10];
    struct Store rec;
    char *token;
    int n, m;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s file\n", argv[0]);
        return 1;
    }

    if ((fp = fopen(argv[1], "rb+")) == NULL) {
        fprintf(stderr, "File open error\n");
        return 2;
    }

    printf("Input command number >> ");
    fgets(cmd, sizeof(cmd), stdin);

    token = strtok(cmd, ",");
    while (token != NULL) {
        if (sscanf(token, "%d-%d", &n, &m) == 2) {
            while (n <= m) {
                sellProduct(fp, n, &rec);
                n++;
            }
        } else {
            if (sscanf(token, "%d", &rec.id) == 1) {
                sellProduct(fp, rec.id, &rec);
            }
        }
        token = strtok(NULL, ",");
    }
    printInventory(fp, &rec);
    fclose(fp);
    return 0;
}

void sellProduct(FILE *fp, int productId, struct Store *rec) {
    fseek(fp, (productId - START_ID) * sizeof(struct Store), SEEK_SET);
    fread(rec, sizeof(struct Store), 1, fp);
    if (rec->count == 0) {
        printf("%s out of stock\n", rec->name);
    } else {
        rec->count--;
        fseek(fp, -sizeof(struct Store), SEEK_CUR);
        fwrite(rec, sizeof(struct Store), 1, fp);
        printf("%s sold successfully.\n", rec->name);
    }
}

void printInventory(FILE *fp, struct Store *rec) {
    fseek(fp, 0L, SEEK_SET);
    printf("%-8s %-8s %-8s %-5s %-3s\n", "Product ID", "Product Name", "Category", "Expiry Date", "Stock");
    while (fread(rec, sizeof(struct Store), 1, fp) > 0) {
        if (rec->id == 0) {
            continue;
        }
        printf("%8d %8s %8s %5d %3d\n", rec->id, rec->name, rec->category, rec->date, rec->count);
    }
}

