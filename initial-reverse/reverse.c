#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char *s;
    struct Node *prev;
    struct Node *next;
};

int main(int argc, char* argv[]) {
    if (argc > 3) {
        fprintf(stderr, "usage: reverse <input> <output>\n");
        exit(1);
    }

    FILE *fin = NULL;
    FILE *fout = NULL;
    struct Node *cur, *pre;
    cur = malloc(sizeof(struct Node));
    if (cur == NULL) {
        fprintf(stderr, "malloc failed\n");
        exit(1);
    }

    if (argc <= 1) {
        fin = stdin;
    } else {
        fin = fopen(argv[1], "r");
        if (fin == NULL) {
            fprintf(stderr, "reverse: cannot open file '%s'\n", argv[1]);
            exit(1);
        }
    }

    size_t len = 0;

    while (getline(&(cur->s), &len, fin) != -1) {
        pre = cur;
        cur = malloc(sizeof(struct Node));
        if (cur == NULL) {
            fprintf(stderr, "malloc failed\n");
            exit(1);
        }
        pre->next = cur;
        cur->prev = pre;
    }
    fclose(fin);

    if (argc <= 2) {
        fout = stdout;
    } else {
        if (strcmp(argv[1], argv[2]) == 0) {
            fprintf(stderr, "reverse: input and output file must differ\n");
            exit(1);
        }
        fout = fopen(argv[2], "w+");
        if (fout == NULL) {
            fprintf(stderr, "reverse: cannot open file '%s'\n", argv[2]);
            exit(1);
        }
    }
    
    struct Node *head = cur->prev;
    while (head != NULL) {
        fprintf(fout, "%s", head->s);
        head = head->prev;
    }
    fclose(fout);

    exit(0);
}