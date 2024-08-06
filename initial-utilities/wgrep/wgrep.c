#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define bufSize 100

void grep(FILE* fp, char* term) {
    ssize_t nread;
    char *line = NULL;
    size_t len = 0;
    while ((nread = getline(&line, &len, fp)) != -1) {
        if (strstr(line, term) != NULL) {
            printf("%s", line);
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc <= 1) {
        printf("wgrep: searchterm [file ...]\n");
        exit(1);
    }

    if (strlen(argv[1]) == 0) {
        exit(0);
    }

    char *term = argv[1];
    if (argc == 2) {
        grep(stdin, term);
    }

    FILE *fp = NULL;
    for (int i = 2; i < argc; i++) {
        fp = fopen(argv[i], "r");
        if (fp == NULL) {
            printf("wgrep: cannot open file\n");
            exit(1);
        }
        grep(fp, term);
        fclose(fp);
    }

    exit(0);
}