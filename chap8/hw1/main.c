#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <string.h>

extern char **environ;

int main(int argc, char *argv[])
{
    int i;

    if (argc < 2)
    {
        printf("Usage: ./main [-e [NAME]] [-u] [-g] [-i] [-p]\n");
        return 1;
    }

    for (i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-e") == 0)
        {
            if (i + 1 < argc && argv[i + 1][0] != '-')
            {
                char *value = getenv(argv[i + 1]);

                if (value != NULL)
                    printf("%s=%s\n", argv[i + 1], value);
                else
                    printf("%s: Not found\n", argv[i + 1]);

                i++;
            }
            else
            {
                for (int j = 0; environ[j] != NULL; j++)
                {
                    printf("%s\n", environ[j]);
                }
            }
        }
        else if (strcmp(argv[i], "-u") == 0)
        {
            struct passwd *realUser = getpwuid(getuid());
            struct passwd *validUser = getpwuid(geteuid());

            printf("My Realistic User ID : %d(%s)\n",
                   getuid(),
                   realUser != NULL ? realUser->pw_name : "Unknown");

            printf("My Valid User ID : %d(%s)\n",
                   geteuid(),
                   validUser != NULL ? validUser->pw_name : "Unknown");
        }
        else if (strcmp(argv[i], "-g") == 0)
        {
            struct group *realGroup = getgrgid(getgid());
            struct group *validGroup = getgrgid(getegid());

            printf("My Realistic Group ID : %d(%s)\n",
                   getgid(),
                   realGroup != NULL ? realGroup->gr_name : "Unknown");

            printf("My Valid Group ID : %d(%s)\n",
                   getegid(),
                   validGroup != NULL ? validGroup->gr_name : "Unknown");
        }
        else if (strcmp(argv[i], "-i") == 0)
        {
            printf("my process number : [%d]\n", getpid());
        }
        else if (strcmp(argv[i], "-p") == 0)
        {
            printf("my parent's process number : [%d]\n", getppid());
        }
        else
        {
            printf("Invalid option: %s\n", argv[i]);
        }
    }

    return 0;
}
