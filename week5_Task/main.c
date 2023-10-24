#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 10
#define MAX_CHARS_PER_LINE 100

void Read(FILE *file, char *buf, size_t count) {
    for (size_t i = 0; i < count; i++) {
        int ch = fgetc(file);
        if (ch == EOF || ch == '\n') {
            *buf = '\0'; // 문자열 끝에 널 문자 추가
            break;
        } else {
            *buf = (char)ch;
        }
        buf++;
    }
}

int main() {
    char savedText[MAX_LINES][MAX_CHARS_PER_LINE];
    int numLines = 0;

    // 파일에서 데이터를 읽어와서 2차원 배열에 저장
    FILE *file = fopen("/Users/kimgyeong-yeon/CLionProjects/week5_Task/file1.txt", "r");
    if (file == NULL) {
        perror("파일 열기 실패");
        return 1;
    }

    char line[MAX_CHARS_PER_LINE];
    while (numLines < MAX_LINES && !feof(file)) {
        Read(file, line, sizeof(line));
        strcpy(savedText[numLines], line);
        numLines++;
    }

    fclose(file);

    // 총 파일 라인 수 출력
    printf("Total Line : %d\n", numLines);

    // 사용자 입력 받기
    int startLine, endLine;
    printf("You can choose 1 ~ %d Line\n", numLines);
    printf("Pls 'Enter' the line to select : ");
    char input[10];
    fgets(input, sizeof(input), stdin);

    char *token = strtok(input, ",");
    while (token != NULL) {
        if (sscanf(token, "%d~%d", &startLine, &endLine) == 2) {
            if (startLine >= 1 && endLine >= startLine && endLine <= numLines) {
                for (int i = startLine - 1; i < endLine; i++) {
                    printf("%s\n", savedText[i]);
                }
            } else {
                printf("올바른 범위를 입력하세요.\n");
            }
        } else if (strcmp(token, "*\n") == 0) {
            // "*"을 입력하면 모든 라인 출력
            for (int i = 0; i < numLines; i++) {
                printf("%s\n", savedText[i]);
            }
        } else {
            int lineNum;
            if (sscanf(token, "%d", &lineNum) == 1) {
                if (lineNum >= 1 && lineNum <= numLines) {
                    printf("%s\n", savedText[lineNum - 1]);
                } else {
                    printf("올바른 라인 번호를 입력하세요.\n");
                }
            } else {
                printf("올바른 입력 형식이 아닙니다.\n");
            }
        }
        token = strtok(NULL, ",");
    }

    return 0;
}