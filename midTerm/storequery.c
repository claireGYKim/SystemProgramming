#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "product.h"

int main() {
    int inputValue, i;
    struct information record;
    scanf("%d", &inputValue);



    printf("상품이름\t상품종류\t유통기한\t재고\n ");
    if(inputValue==0){
        for(i=0;i<6;i++){
            printf("%-9s %-9s %-5d %-4d", record.name, record.productType,
                   record.expirationDate,record.stock);
        }
    }


    return 0;
}
