#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define MAXLINE 80
/* 파일 내용을 출력 */
void printFile(FILE *fp, bool lineNumbering) {
    int c;
    int line = 0;
    char buffer[MAXLINE];
    while (fgets(buffer, MAXLINE, fp) != NULL) {
        line++;
        if (lineNumbering) {
            printf("%3d  %s", line, buffer);
        } else {
            printf("%s", buffer);
        }
    }
}
int main(int argc, char *argv[]) {
    FILE *fp;
    bool lineNumbering = false;
    if (argc < 2) {
        fprintf(stderr, "사용법: %s [-n] 파일1 파일2 ... 파일N\n", argv[0]);
        exit(1);
    }
    int fileIndex = 1;
    if (argc > 2 && strcmp(argv[1], "-n") == 0) {
        lineNumbering = true;
        fileIndex = 2;
    }
    for (int i = fileIndex; i < argc; i++) {
        if ( (fp = fopen(argv[i], "r")) == NULL) {
            fprintf(stderr, "파일 열기 오류\n");
            exit(2);
        }
        if (argc > 3 && lineNumbering) {
            printf("==> %s <==\n", argv[i]);
        }
        printFile(fp, lineNumbering);
        fclose(fp);
        if (i < argc - 1) {
            printf("\n");
        }
    }
    exit(0);
}