#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINES 100
#define MAX_CHARS_PER_LINE 1000

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
    while (fgets(line, sizeof(line), file) != NULL) {
        if (numLines < MAX_LINES) {
            strcpy(savedText[numLines], line);
            numLines++;
        } else {
            printf("저장 공간 부족\n");
            break;
        }
    }

    fclose(file);

    // 거꾸로 출력
    for (int i = numLines - 1; i >= 0; i--) {
        printf("%s", savedText[i]);
    }

    return 0;
}