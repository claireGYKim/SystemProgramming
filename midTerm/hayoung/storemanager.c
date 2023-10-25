//storemannager.c

#include <stdio.h>

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

int main(int argc, char*argv[]) {
    struct store rec;
    int cmd; //상품 등록 or 삭제 번호
    FILE* fp;

    if (argc < 2) {
        fprintf(stderr, "사용법 : %s file\n", argv[0]);
        return 1;
    }

    printf("Input command, ID number >> ");
    scanf("%d %d", &cmd, &rec.id); //동작 번호, ID번호

    fp = fopen(argv[1], "rb+");
    if (cmd == 0) { //입력
        printf("상품번호, 이름, 종류, 기한, 재고 입력 >> ");
        while(scanf("%s %s %d %d", rec.name, rec.category, &rec.date, &rec.count) == 5) {
            fseek(fp, (rec.id - STARTID)*sizeof(rec), SEEK_SET);
            fwrite(&rec, sizeof(rec), 1, fp);
        }
        printf("입력이 완료되었습니다.\n");
    }
    else { //삭제
        fseek(fp, (rec.id - STARTID)*sizeof(rec), SEEK_SET);
        if ((fread(&rec, sizeof(rec), 1, fp) > 0) && (rec.id!=0)){
            fwrite(" ", 2, 1, fp);
        }
        else {
            printf("레코드 %d 없음\n", rec.id);
        }
    }
    fclose(fp);
    return 0;
}