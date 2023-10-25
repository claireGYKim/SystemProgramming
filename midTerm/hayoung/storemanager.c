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
    int cmd; //��ǰ ��� or ���� ��ȣ
    FILE* fp;

    if (argc < 2) {
        fprintf(stderr, "���� : %s file\n", argv[0]);
        return 1;
    }

    printf("Input command, ID number >> ");
    scanf("%d %d", &cmd, &rec.id); //���� ��ȣ, ID��ȣ

    fp = fopen(argv[1], "rb+");
    if (cmd == 0) { //�Է�
        printf("��ǰ��ȣ, �̸�, ����, ����, ��� �Է� >> ");
        while(scanf("%s %s %d %d", rec.name, rec.category, &rec.date, &rec.count) == 5) {
            fseek(fp, (rec.id - STARTID)*sizeof(rec), SEEK_SET);
            fwrite(&rec, sizeof(rec), 1, fp);
        }
        printf("�Է��� �Ϸ�Ǿ����ϴ�.\n");
    }
    else { //����
        fseek(fp, (rec.id - STARTID)*sizeof(rec), SEEK_SET);
        if ((fread(&rec, sizeof(rec), 1, fp) > 0) && (rec.id!=0)){
            fwrite(" ", 2, 1, fp);
        }
        else {
            printf("���ڵ� %d ����\n", rec.id);
        }
    }
    fclose(fp);
    return 0;
}