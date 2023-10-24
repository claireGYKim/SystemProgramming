//#include <stdio.h>
//
//int main(int argc, char *argv[]) {
//    FILE *fp;
//    int c;
//
//    if (argc < 2) {
//        fp = stdin;
//    } else {
//        fp = fopen(argv[1], "r");
//        if (fp == NULL) {
//            perror("Failed to open the file");
//            return 1; // 리턴 코드 1로 프로그램 종료
//        }
//    }
//
//    c = getc(fp);
//    while (c != EOF) {
//        fputc(c, stdout);
//        c = getc(fp);
//    }
//
//    if (argc >= 2) {
//        fclose(fp); // 파일을 열었을 경우에만 닫기
//    }
//
//    return 0;
//}




//#include <stdio.h>
//#include "student.h"
//
//int main(int argc, char* argv[])
//{
//    struct student rec; FILE *fp;
//    if (argc != 2) {
//        fprintf(stderr, "사용법: %s 파일이름\n", argv[0]);
//        return 1; }
//    fp = fopen(argv[1], "w");
//    printf("%-9s %-7s %-4s\n", "학번", "이름", "점수");
//    while (scanf("%d %s %d", &rec.id, rec.name, &rec.score)==3)
//        fprintf(fp, "%d %s %d ", rec.id, rec.name, rec.score); fclose(fp);
//    return 0;
//}




//#include <stdio.h>
//#include "student.h"
///* 텍스트 파일에서 학생 정보를 읽어 프린트한다. */ int main(int argc, char* argv[]) {
//    struct student rec; FILE *fp;
//    if (argc != 2) {
//        fprintf(stderr, "사용법: %s 파일이름\n", argv[0]);
//        return 1; }
//    fp = fopen(argv[1], "r");
//    printf("%-9s %-7s %-4s\n", "학번", "이름", "점수");
//    while (fscanf(fp,"%d %s %d", &rec.id, rec.name, &rec.score)==3)
//        printf("%10d %6s %6d\n", rec.id, rec.name, rec.score);
//    fclose(fp);
//    return 0; }
//





//#include <stdio.h>
//#include <stdlib.h>
//#include "student.h"
//int main(int argc, char* argv[]) {
//    struct student rec;
//    FILE *fp;
//    if (argc != 2) {
//        fprintf(stderr, "사용법: %s 파일이름\n",argv[0]); exit(1);
//    }
//    fp = fopen(argv[1], "wb");
//    printf("%-9s %-7s %-4s\n", "학번", "이름", "점수");
//    while (scanf("%d %s %d", &rec.id, rec.name, &rec.score) == 3)
//        fwrite(&rec, sizeof(rec), 1, fp); fclose(fp);
//    exit(0);
//}


//#include <stdio.h>
//#include "student.h"
///* 파일에 저장된 모든 학생 정보를 읽어서 츨력한다. */ int main(int argc, char* argv[])
//{
//    struct student rec; FILE *fp;
//    if (argc != 2) {
//        fprintf(stderr, "사용법: %s 파일이름\n", argv[0]);
//        return 1; }
//    if ((fp = fopen(argv[1], "rb")) == NULL ) { fprintf(stderr, "파일 열기 오류\n"); return 2;
//    }
//
//    printf("-----------------------------------\n"); printf("%10s %6s %6s\n", "학번", "이름", "점수"); printf("-----------------------------------\n");
//    while (fread(&rec, sizeof(rec), 1, fp) > 0) if (rec.id != 0)
//            printf("%10d %6s %6d\n", rec.id, rec.name, rec.score);
//    printf("-----------------------------------\n");
//    fclose(fp);
//    return 0; }


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    FILE *fp;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file|stdin|stdout|stderr>\n", argv[0]);
        return 1;
    }

    if (!strcmp(argv[1], "stdin")) {
        fp = stdin;
        printf("스트림 = stdin, ");
    } else if (!strcmp(argv[1], "stdout")) {
        fp = stdout;
        printf("스트림 = stdout, ");
    } else if (!strcmp(argv[1], "stderr")) {
        fp = stderr;
        printf("스트림 = stderr, ");
    } else if ((fp = fopen(argv[1], "r")) == NULL) {
        perror("fopen");
        return 1;
    }

    if (setvbuf(fp, NULL, _IONBF, 0) != 0) {
        perror("setvbuf");
        return 1;
    }

    printf("버퍼 미사용, ");

    if (fp == stdin || fp == stdout || fp == stderr) {
        printf("버퍼 크기 = N/A (stdin/stdout/stderr)\n");
    } else {
        fseek(fp, 0, SEEK_END);
        long bufferSize = ftell(fp);
        printf("버퍼 크기 = %ld\n", bufferSize);
    }

    fclose(fp);
    return 0;
}
