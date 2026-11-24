
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int fd;
    char savedText[10][100] = {0};
    char buf;
    char input[100];

    int line = 0;
    int col = 0;
    int totalLine;

    if (argc < 2)
    {
        printf("File open error\n");
        return 1;
    }

    fd = open(argv[1], O_RDONLY);

    if (fd == -1)
    {
        printf("File open error\n");
        return 1;
    }

    while (read(fd, &buf, 1) > 0)
    {
        if (buf == '\n')
        {
            if (line < 10)
                savedText[line][col] = '\0';

            line++;
            col = 0;
        }
        else if (buf != '\r')
        {
            if (line < 10 && col < 99)
            {
                savedText[line][col] = buf;
                col++;
            }
        }
    }

    if (line < 10)
        savedText[line][col] = '\0';

    totalLine = line;

    if (col > 0)
        totalLine++;

    close(fd);

    printf("File read success\n");
    printf("Total Line : %d\n", totalLine);
    printf("You can choose 1 ~ %d Line\n", totalLine);

    printf("Pls 'Enter' the line to select : ");
    scanf("%99s", input);

    if (strcmp(input, "*") == 0)
    {
        for (int i = 0; i < totalLine; i++)
        {
            printf("%s\n", savedText[i]);
        }
    }
    else
    {
        int n = 0;
        int start = 0;
        int end = 0;
        int i = 0;

        while (input[i] != '\0')
        {
            n = 0;

            while (input[i] >= '0' && input[i] <= '9')
            {
                n = n * 10 + (input[i] - '0');
                i++;
            }

            if (input[i] == '-')
            {
                start = n;
                i++;

                end = 0;

                while (input[i] >= '0' && input[i] <= '9')
                {
                    end = end * 10 + (input[i] - '0');
                    i++;
                }

                if (start >= 1 && end <= totalLine && start <= end)
                {
                    for (int j = start; j <= end; j++)
                    {
                        printf("%s\n", savedText[j - 1]);
                    }
                }
            }
            else
            {
                if (n >= 1 && n <= totalLine)
                {
                    printf("%s\n", savedText[n - 1]);
                }
            }

            if (input[i] == ',')
            {
                i++;
            }
            else
            {
                break;
            }
        }
    }

    return 0;
}

