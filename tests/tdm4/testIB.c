#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include "../../libs/file.h"
#include <semaphore.h>

static char* c;
static sem_t sRead;
static sem_t sWrite;

void* readFile() {
    int fd;
    fd = open("txt/Source.txt", O_RDONLY);

    if (fd == -1) {
        perror("error while opening source file");
        exit(1);
    }

    do {
        sem_wait(&sRead);
        c = readLine(fd);
        sem_post(&sWrite);
    } while (c != NULL);

    close(fd);

    return 0;
}

void* writeFile() {
    int fd;
    fd = open("txt/Destination.txt", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

    if (fd == -1) {
        perror("error while opening destination file");
        exit(1);
    }

    do {
        sem_wait(&sWrite);
        writeLine(c, fd);
        free(c);
        sem_post(&sRead);
    } while (c != NULL);

    close(fd);

    return 0;
}

int main() {
    pthread_t thread1;
    pthread_t thread2;

    if (pthread_create(&thread1, NULL, readFile, (void*) NULL)) {
        perror("ERROR creating thread1.");
    }

    if (pthread_create(&thread2, NULL, writeFile, (void*) NULL)) {
        perror("ERROR creating thread2.");
    }

    sem_init(&sRead, 0, 1);
    sem_init(&sWrite, 0, 0);

    if (pthread_join(thread1, NULL)) {
        perror("ERROR join thread1.");
    }

    if (pthread_join(thread2, NULL)) {
        perror("ERROR join thread2.");
    }

    return 0;
}

