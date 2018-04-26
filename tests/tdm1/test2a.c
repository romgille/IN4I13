#include "../../libs/file.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv)
{
    char* chars;
    int fd;

    if (argc < 2)
    {
        printf("donner un fichier\n");
        exit(1);
    }

    fd = open(argv[1], O_RDONLY);

    if (fd == -1)
    {
        perror("problème d'ouverture");
        exit(1);
    }

    chars = readLine(fd);

    if (chars == NULL) exit(1);

    printf("%s\n", chars);

    free(chars);
    close(fd);

    return 0;
}
