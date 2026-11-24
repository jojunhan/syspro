#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    char command[1024];
    char *args[100];
    char *saveptr;
    char *token;

    int count;
    int background;
    int pid;

    while (1)
    {
        printf("Pls input cmd : ");

        if (fgets(command, sizeof(command), stdin) == NULL)
            break;

        if (strcmp(command, "exit\n") == 0)
            break;

        count = 0;
        background = 0;

        token = strtok_r(command, " \t\n", &saveptr);

        while (token != NULL && count < 99)
        {
            if (strcmp(token, "&") == 0)
                background = 1;
            else
                args[count++] = token;

            token = strtok_r(NULL, " \t\n", &saveptr);
        }

        args[count] = NULL;

        if (count == 0)
            continue;

        printf("Parent process start\n");

        pid = fork();

        if (pid == 0)
        {
            execvp(args[0], args);

            fprintf(stderr, "Command execution failed\n");
            exit(1);
        }
        else if (pid > 0)
        {
            if (background == 0)
            {
                wait(NULL);
                printf("Child process end\n");
            }

            printf("SUCCESS\n");
        }
        else
        {
            perror("fork");
        }
    }

    return 0;
}

