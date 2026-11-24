#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLINE 100

int main(int argc, char *argv[])
{
    FILE *fp;
    int line = 0;
    int i = 1;
    int option = 0;
    char buffer[MAXLINE];

    if (argc > 1 && strcmp(argv[1], "-n") == 0) {
        option = 1;
        i = 2;
    }

    if (i == argc) {
        fp = stdin;

        while (fgets(buffer, MAXLINE, fp) != NULL) {
            if (option == 1) {
                line++;
                printf("%3d %s", line, buffer);
            }
            else
                printf("%s", buffer);
        }
    }
    else {
        for (; i < argc; i++) {

            if ((fp = fopen(argv[i], "r")) == NULL) {
                fprintf(stderr, "Error Open File: %s\n", argv[i]);
                continue;
            }
            while (fgets(buffer, MAXLINE, fp) != NULL) {
                if (option == 1) {
                    line++;
                    printf("%3d %s", line, buffer);
                }
                else
                    printf("%s", buffer);
            }

            fclose(fp);
        }
    }

    return 0;
}

