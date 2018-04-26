#include "../../libs/process.h"
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>

int main() {
    pid_t pid;

    switch(pid = fork()) {
        case -1:
            perror("Issue with fork");
            exit(1);
        case 0:
            print_all("fils\n");
            break;
        default:
            print_all("père\n");
    }

    return 0;
}
