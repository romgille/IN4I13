#define _POSIX_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>
#include "../../libs/process.h"
#include "../../libs/file.h"

int* time = 0;

void handler(int signal) {
    if (signal == SIGINT) {
        printf("Too Late!\n");
        *time = 0;
    }
}


void serverA (pid_t pid) {
    int cmp = 1;
    char* pass = "1234";
    char* input = 0;

    if (signal(SIGINT, handler) == SIG_ERR) perror("handler error");

    do {
        input = readLine(0);
        cmp = strcmp(pass, input);
        cmp == 0 ? printf("Yeah\n") : printf("You Loose\n");
        break;
    } while (*time);

    kill(pid, SIGKILL);
    free(input);
    free(time);
    wait(NULL);
}


void serverB (pid_t ppid) {
    sleep(5); /* TODO remettre a 10 */
    kill(ppid, SIGINT);
}


int main (int argc, char ** argv) {

    /* shared PIDs */
    pid_t pid = 0;
    pid_t ppid = getpid();

    /* shared variable */
    time = (int*)malloc(sizeof(int));
    *time = 1;

    switch (pid = fork()) {
        case -1:
            perror("issue with fork");
            exit(1);
            break;
        case 0:
            serverB(ppid);
        default:
            serverA(pid);
    }

    return 0;
}
