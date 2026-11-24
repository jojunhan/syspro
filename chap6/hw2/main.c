
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <grp.h>
#include <pwd.h>
#include <string.h>
#include <dirent.h>

char type(mode_t);
char *perm(mode_t);
void printStat(char *, char *, struct stat *, int, int, int);

int main(int argc, char **argv)
{
    DIR *dp;
    char *dir = ".";
    struct stat st;
    struct dirent *d;
    char path[BUFSIZ + 1];

    int option_i = 0;
    int option_p = 0;
    int option_Q = 0;

    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-i") == 0)
            option_i = 1;
        else if (strcmp(argv[i], "-p") == 0)
            option_p = 1;
        else if (strcmp(argv[i], "-Q") == 0)
            option_Q = 1;
        else
            dir = argv[i];
    }

    if ((dp = opendir(dir)) == NULL)
    {
        perror(dir);
        return 1;
    }

    while ((d = readdir(dp)) != NULL)
    {
        snprintf(path, sizeof(path), "%s/%s", dir, d->d_name);

        if (lstat(path, &st) < 0)
            perror(path);
        else
            printStat(path, d->d_name, &st,
                      option_i, option_p, option_Q);
    }

    closedir(dp);

    return 0;
}

void printStat(char *pathname, char *file, struct stat *st,
               int option_i, int option_p, int option_Q)
{
    char name[BUFSIZ + 1];

    strcpy(name, file);

    if (option_i)
        printf("%10ld ", (long)st->st_ino);

    printf("%5d ", (int)st->st_blocks);
    printf("%c%s ", type(st->st_mode), perm(st->st_mode));
    printf("%3d ", (int)st->st_nlink);

    printf("%s %s ",
           getpwuid(st->st_uid)->pw_name,
           getgrgid(st->st_gid)->gr_name);

    printf("%9ld ", (long)st->st_size);
    printf("%.12s ", ctime(&st->st_mtime) + 4);

    if (option_p && S_ISDIR(st->st_mode))
        strcat(name, "/");

    if (option_Q)
        printf("\"%s\"\n", name);
    else
        printf("%s\n", name);
}

char type(mode_t mode)
{
    if (S_ISREG(mode))
        return '-';
    if (S_ISDIR(mode))
        return 'd';
    if (S_ISCHR(mode))
        return 'c';
    if (S_ISBLK(mode))
        return 'b';
    if (S_ISLNK(mode))
        return 'l';
    if (S_ISFIFO(mode))
        return 'p';
    if (S_ISSOCK(mode))
        return 's';

    return '?';
}

char *perm(mode_t mode)
{
    static char perms[10];

    strcpy(perms, "---------");

    for (int i = 0; i < 3; i++)
    {
        if (mode & (S_IRUSR >> i * 3))
            perms[i * 3] = 'r';

        if (mode & (S_IWUSR >> i * 3))
            perms[i * 3 + 1] = 'w';

        if (mode & (S_IXUSR >> i * 3))
            perms[i * 3 + 2] = 'x';
    }

    return perms;
}

