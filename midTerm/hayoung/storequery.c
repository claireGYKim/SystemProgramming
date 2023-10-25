//storequery.c

#include <stdio.h>
#include <stdlib.h>

//#include "store.h"
#define STARTID 1
struct store {
    int id;
    char name[100];
    char category[100];
    int date;
    int count;
};
//

int main(int argc, char* argv[]) {
    int cmd;
    struct store rec;
    FILE* fp;

    if (argc < 2) { //입력값 오류 처리
        fprintf(stderr, "사용법 : %s file", argv[0]);
        return 1;
    }

    if ((fp = fopen(argv[1], "rb")) == NULL) { //파일 열기 오류 처리
        fprintf(stderr, "파일 열기 오류\n");
        return 2;
    };

    printf("Input command number >> ");
    scanf("%d", &cmd); //동작 번호

    if (cmd == 0) { //모든 상품의 정보 출력
        printf("%-8s %-8s %-8s %-5s %-3s\n", "상품고유번호", "상품이름", "상품 종류", "유통기한", "재고");
        while(fread(&rec, sizeof(rec), 1, fp) > 0) {
            printf("%8d %8s %8s %5d %3d\n", rec.id, rec.name, rec.category, rec.date, rec.count);
        }
    }
    else { //판매 가능한 상품 정보 출력
        printf("%-8s %-8s %-8s %-5s %-3s\n", "상품고유번호", "상품이름", "상품 종류", "유통기한", "재고");
        while(fread(&rec, sizeof(rec), 1, fp) > 0) {
            if (rec.count > 0 && rec.date >= 2023) {
                printf("%8d %8s %8s %5d %3d\n", rec.id, rec.name, rec.category, rec.date, rec.count);
            }
        }
    }

    return 0;
}