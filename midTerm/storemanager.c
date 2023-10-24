#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "productInformation.h"

int main(int argc, char *argv[])
{
    int fd;
    int inputValue;
    struct information record;
    if (argc < 2) {
        fprintf(stderr, "사용법 : %s file\n", argv[0]);
        exit(1);
    }

    if ((fd = open(argv[1], O_WRONLY|O_CREAT|O_EXCL, 0640)) == -1) {
        perror(argv[1]);
        exit(2);
    }
    printf("%-9s %-9s %-9s %-6s %-4s\n", "고유번호", "상품이름", "상품종류","유통기한","재고");
    while (scanf("%d %d %s %d", &inputValue, &record.id, record.name, record.productType,
                 &record.expirationDate, &record.stock) == 5) {
        if(inputValue==0){
            lseek(fd, (record.id - START_ID) * sizeof(record), SEEK_SET);
            write(fd, (char *) &record, sizeof(record) );
        }
        else if(inputValue==1){ // 고유번호 항 삭제목
            continue;
        }

    }
    close(fd);
    exit(0);
}