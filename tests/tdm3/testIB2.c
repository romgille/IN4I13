#include "../../libs/file.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char* argv[]) {
    pid_t pid;
    int fd;
    int fildes[2];

    if (pipe(fildes) == -1) {
        perror("Issue while creating pipe");
        exit(1);
    }

    switch(pid = fork()) {
        case -1:
            perror("Issue with fork");
            exit(1);

        case 0:
            /* Dans le fils */

            close(fildes[1]);

            fd = open("txt/Destination.txt",
                    O_WRONLY | O_CREAT,
                    S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

            if (fd == -1) {
                perror("error while opening destination file");
                close(fildes[0]);
                close(fd);
                exit(1);
            }

            copy(fildes[0], fd);

            exit(EXIT_SUCCESS);

            break;

        default:
            /* Dans le père */

            close(fildes[0]);

            fd = open("txt/Source.txt", O_RDONLY);

            if (fd == -1) {
                perror("error while opening source file");
                close(fildes[1]);
                close(fd);
                exit(1);
            }

            copy(fd, fildes[1]);

            exit(EXIT_SUCCESS);
            break;
    }

    return 0;
}
