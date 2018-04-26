#include "../../libs/process.h"
#include "../../libs/file.h"
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

int main() {
    pid_t pid;
    int fd;
    char* chaine;

    fd = open("txt/fichierTest.txt", O_RDONLY);

    if ((pid = fork()) == -1) {
        perror("Issue with fork");
        exit(1);
    }

    if (fd != -1) {
        chaine = readLine(fd);
        print_all(chaine);
        free(chaine);
    }
    close(fd);

    return 0;
}
