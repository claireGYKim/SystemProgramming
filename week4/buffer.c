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
