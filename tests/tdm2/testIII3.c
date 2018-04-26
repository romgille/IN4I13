#include "../../libs/process.h"
#include "../../libs/file.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

int main(int argc, char* argv[]) {
    pid_t pid;
    int fd;
    char* chaine;

    if (argc < 2)
    {
        printf("donner un fichier\n");
        exit(1);
    }

    fd = open(argv[1], O_RDONLY);

    if ((pid = fork()) == -1) {
        perror("Issue with fork");
        exit(1);
    }

    if (pid == 0) wait(NULL);

    if (fd != -1) {
        chaine = readLine(fd);
        print_all(chaine);
        printf("\n");
        free(chaine);
    }
    close(fd);

    return 0;
}
