#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>

static sem_t s1;
static sem_t s2;
static sem_t s3;
static sem_t mutex;

void* fnct1() {
    int i;
    for (i = 0; i < 10; ++i) {
        sem_wait(&s1);
        sem_wait(&mutex);
        printf("Affichage %d du thread %d\n", i + 1, 1);
        sem_post(&mutex);
        sem_post(&s2);
    }

    return 0;
}


void* fnct2() {
    int i;
    for (i = 0; i < 10; ++i) {
        sem_wait(&s2);
        sem_wait(&mutex);
        printf("Affichage %d du thread %d\n", i + 1, 2);
        sem_post(&mutex);
        sem_post(&s3);
    }

    return 0;
}


void* fnct3() {
    int i;
    for (i = 0; i < 10; ++i) {
        sem_wait(&s3);
        sem_wait(&mutex);
        printf("Affichage %d du thread %d\n", i + 1, 3);
        sem_post(&mutex);
        sem_post(&s1);
    }

    return 0;
}

int main() {
    pthread_t thread1;
    pthread_t thread2;
    pthread_t thread3;

    sem_init(&s1, 0, 1);
    sem_init(&s2, 0, 0);
    sem_init(&s3, 0, 0);
    sem_init(&mutex, 0, 1);

    if (pthread_create(&thread1, NULL, fnct1, (void*) NULL)) {
        perror("ERROR creating thread1.");
    }

    if (pthread_create(&thread2, NULL, fnct2, (void*) NULL)) {
        perror("ERROR creating thread2.");
    }

    if (pthread_create(&thread3, NULL, fnct3, (void*) NULL)) {
        perror("ERROR creating thread2.");
    }

    if (pthread_join(thread1, NULL)) {
        perror("ERROR join thread1.");
    }

    if (pthread_join(thread2, NULL)) {
        perror("ERROR join thread2.");
    }

    if (pthread_join(thread3, NULL)) {
        perror("ERROR join thread3.");
    }

    return 0;
}

