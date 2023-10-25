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
    int cmd; //명령번호
    FILE* fp;

    if (argc < 2) {
        fprintf(stderr, "사용법˝ : %s file\n", argv[0]);
        return 1;
    }

    printf("Input command, ID number >> ");
    scanf("%d %d", &cmd, &rec.id); //µø¿€ π¯»£, IDπ¯»£

    fp = fopen(argv[1], "rb+");
    if (cmd == 0) { //입력
        printf("이름, 카테고리, 날짜, 제고를 입력하시오. >> ");
        while(scanf("%s %s %d %d", rec.name, rec.category, &rec.date, &rec.count) == 5) {
            fseek(fp, (rec.id - STARTID)*sizeof(rec), SEEK_SET);
            fwrite(&rec, sizeof(rec), 1, fp);
        }
        printf("입력되었습니다.\n");
    }
    else { //삭제
        fseek(fp, (rec.id - STARTID)*sizeof(rec), SEEK_SET);
        if ((fread(&rec, sizeof(rec), 1, fp) > 0) && (rec.id!=0)){
            fwrite(" ", 2, 1, fp);
        }
        else {
            printf("제고가 없습니다.", rec.id);
        }
    }
    fclose(fp);
    return 0;
}







//storeupdate.c

#include <stdio.h>
#include <string.h>

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

void sold(FILE *fp, int n, struct store rec);
void printSold(FILE *fp, struct store rec);

int main(int argc, char* argv[]) {
    FILE* fp;
    char cmd[10];
    struct store rec;
    char* p; //포인터
    int n, m; //n부터 m까지

    if (argc < 2) { //입력값 오류 처리
        fprintf(stderr, "사용법 : %s file", argv[0]);
        return 1;
    }

    if ((fp = fopen(argv[1], "rb+")) == NULL) { //파일 열기 오류 처리 //rb+에서 b를 지우면됨
        fprintf(stderr, "파일 열기 오류\n");
        return 2;
    };

    printf("Input command number >> ");
    fgets(cmd, sizeof(cmd), stdin); //동작 입력

    p = strtok(cmd, ","); //토큰 포인터
    while (p != NULL) { //토큰이 널이 아닌 경우
        if (sscanf(p, "%d-%d", &n, &m) == 2) { //from-to 형태
            while(n <= m) {
                sold(fp, n, rec); //제품 판매
                n++;
            }
        }
        else { //단일 입력, 복수 입력
            if (sscanf(p, "%d", &rec.id) == 1) {
                sold(fp, rec.id, rec); //제품 판매
            }
        }
        p = strtok(NULL, ","); //다음 토큰
    }
    printSold(fp, rec);//변경 사항 출력
    fclose(fp); //파일 닫기
    return 0;
}

//제품 판매
void sold (FILE *fp, int n, struct store rec) {
    fseek(fp, (n - STARTID) * sizeof(rec), SEEK_SET);
    fread(&rec, sizeof(rec), 1, fp);
    if (rec.count == 0) { //재고 없을 시
        printf("%s 재고 없음\n", rec.name);
    }
    else { //재고 있을 시
        rec.count--; //재고 감소
        fseek(fp, -sizeof(rec), SEEK_CUR);
        fwrite(&rec, sizeof(rec), 1, fp);
        printf("%s 판매가 완료되었습니다.\n", rec.name);
    }
}

void printSold(FILE *fp, struct store rec) {
    //변경 사항 출력
    fseek(fp, 0L, SEEK_SET); //rewind
    printf("%-8s %-8s %-8s %-5s %-3s\n", "상품고유번호", "상품이름", "상품종류", "유통기한", "재고");
    while((fread(&rec, sizeof(rec), 1, fp) > 0) && rec.id != 0) {
        printf("%8d %8s %8s %5d %3d\n", rec.id, rec.name, rec.category, rec.date, rec.count);
    }
}
