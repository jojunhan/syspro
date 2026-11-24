#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int fd;
    char savedText[10][100] = {0};
    char buf;

    int line = 0;
    int col = 0;
    int totalLine = 0;

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

    if (totalLine > 10)
        totalLine = 10;

    close(fd);

    for (int i = totalLine - 1; i >= 0; i--)
    {
        printf("%s\n", savedText[i]);
    }

    return 0;
}

