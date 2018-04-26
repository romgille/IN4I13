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
            execlp("./tdm2_testIB1.o", "tdm2_testIB1.o", (char *)NULL);
            perror("issue with exec");
            exit(1);
        default:
            print_all("je suis le père\n");
            wait(NULL);
    }

    return 0;
}
