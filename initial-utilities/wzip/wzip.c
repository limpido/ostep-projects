#include <stdio.h>
#include <stdlib.h>

void zip(FILE* fp, char* c, char* c_prev, int* count) {
    while ((*c = fgetc(fp)) != EOF) {
        if (*c_prev == -1) {
            *c_prev = *c;
            (*count)++;
        } else if (*c_prev != *c) {
            fwrite(count, 1, sizeof(int), stdout);
            fwrite(c_prev, 1, sizeof(char), stdout);
            *c_prev = *c;
            *count = 1;
        } else {
            (*count)++;
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc <= 1) {
        printf("wzip: file1 [file2 ...]\n");
        exit(1);
    }

    FILE *fp = NULL;
    char c = -1;
    char c_prev = -1;
    int count = 0;
    for (int i = 1; i < argc; i++) {
        fp = fopen(argv[i], "r");
        if (fp == NULL) {
            printf("wzip: cannot open file\n");
            exit(1);
        }
        zip(fp, &c, &c_prev, &count);
        fclose(fp);
    }
    
    fwrite(&count, 1, sizeof(int), stdout);
    fwrite(&c_prev, 1, sizeof(char), stdout);

    exit(0);
}