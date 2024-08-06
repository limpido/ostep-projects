#include <stdio.h>
#include <stdlib.h>

void unzip(FILE* fp) {
    int count;
    char c;

    while (fread(&count, 4, 1, fp) != 0) {
        if (fread(&c, 1, 1, fp) == 0) {
            if (feof(fp)) {
                printf("wunzip: feof\n");
            } else if (ferror(fp)) {
                printf("wunzip: ferror\n");
            }
        }
        for (int i = 0; i < count; i++) {
            printf("%c", c);
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc <= 1) {
        printf("wunzip: file1 [file2 ...]\n");
        exit(1);
    }

    FILE *fp = NULL;
    for (int i = 1; i < argc; i++) {
        fp = fopen(argv[i], "r");
        if (fp == NULL) {
            printf("wunzip: cannot open file\n");
            exit(1);
        }
        unzip(fp);
        fclose(fp);
    }

    exit(0);
}