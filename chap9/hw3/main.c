#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

void execute(char *command)
{
    char storage[1024];
    char *args[100];
    char inputFile[100];
    char outputFile[100];

    int i = 0;
    int pos = 0;
    int count = 0;
    int background = 0;
    int pid;

    inputFile[0] = '\0';
    outputFile[0] = '\0';

    while (command[i] != '\0')
    {
        while (command[i] == ' ' || command[i] == '\t')
            i++;

        if (command[i] == '\0')
            break;

        if (command[i] == '&')
        {
            background = 1;
            i++;
        }
        else if (command[i] == '>')
        {
            i++;

            while (command[i] == ' ' || command[i] == '\t')
                i++;

            int j = 0;

            while (command[i] != '\0' &&
                   command[i] != ' ' &&
                   command[i] != '\t' &&
                   command[i] != '&')
            {
                outputFile[j++] = command[i++];
            }

            outputFile[j] = '\0';
        }
        else if (command[i] == '<')
        {
            i++;

            while (command[i] == ' ' || command[i] == '\t')
                i++;

            int j = 0;

            while (command[i] != '\0' &&
                   command[i] != ' ' &&
                   command[i] != '\t' &&
                   command[i] != '&')
            {
                inputFile[j++] = command[i++];
            }

            inputFile[j] = '\0';
        }
        else
        {
            args[count++] = &storage[pos];

            while (command[i] != '\0' &&
                   command[i] != ' ' &&
                   command[i] != '\t' &&
                   command[i] != '<' &&
                   command[i] != '>' &&
                   command[i] != '&')
            {
                storage[pos++] = command[i++];
            }

            storage[pos++] = '\0';
        }
    }

    args[count] = NULL;

    if (count == 0)
        return;

    pid = fork();

    if (pid < 0)
    {
        perror("fork");
        return;
    }

    if (pid == 0)
    {
        if (inputFile[0] != '\0')
        {
            int fd = open(inputFile, O_RDONLY);

            if (fd < 0)
            {
                perror("open");
                exit(1);
            }

            dup2(fd, STDIN_FILENO);
            close(fd);
        }

        if (outputFile[0] != '\0')
        {
            int fd = open(outputFile,
                          O_WRONLY | O_CREAT | O_TRUNC, 0644);

            if (fd < 0)
            {
                perror("open");
                exit(1);
            }

            dup2(fd, STDOUT_FILENO);
            close(fd);
        }

        execvp(args[0], args);

        perror("execvp");
        exit(1);
    }
    else
    {
        if (background == 0)
            waitpid(pid, NULL, 0);
    }
}

int main()
{
    char command[1024];

    while (1)
    {
        printf("[shell] ");

        if (fgets(command, sizeof(command), stdin) == NULL)
            break;

        if (strcmp(command, "exit\n") == 0)
            break;

        int i = 0;
        int start = 0;

        while (1)
        {
            if (command[i] == ';' ||
                command[i] == '\n' ||
                command[i] == '\0')
            {
                char temp = command[i];
                command[i] = '\0';

                execute(&command[start]);

                if (temp == '\0' || temp == '\n')
                    break;

                start = i + 1;
            }

            i++;
        }
    }

    return 0;
}

