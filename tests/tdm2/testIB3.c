#include "../../libs/process.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

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
            wait(NULL);
    }

    return 0;
}
