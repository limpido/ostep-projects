#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE 100

void cat(FILE* fp) {
    char *buf = malloc(sizeof(char) * BUFSIZE);
    while (fgets(buf, BUFSIZE, fp) != NULL) {
        printf("%s", buf);
    }
}

int main(int argc, char* argv[]) {
    if (argc <= 1) {
        // printf("usage: wcat <file>\n");
        return 0;
    }

    FILE *fp = NULL;

    for (int i = 1; i < argc; i++) {
        fp = fopen(argv[i], "r");
        if (fp == NULL) {
            printf("wcat: cannot open file\n");
            exit(1);
        }
        cat(fp);
        fclose(fp);
    }

    exit(0);
}