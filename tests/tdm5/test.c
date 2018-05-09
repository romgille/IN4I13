#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>

#define MAX_FILE 5
#define MAX_RAND 10
#define SHM_NAME "/os_esiee-tdm5"
#define SEM1 "sem1"
#define SEM2 "sem2"

struct shared_memory {
    int fd;
    int* buffer;
    sem_t* s_read;
    sem_t* s_write;
};

int init(struct shared_memory* memory) {
    if ((memory->fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0644)) == -1) {
        fprintf(stderr, "shm_open failed");
        return 1;
    }

    ftruncate(memory->fd, MAX_FILE * sizeof(int));

    memory->s_read = sem_open(SEM1, O_CREAT, 0644, MAX_FILE);
    memory->s_write = sem_open(SEM2, O_CREAT, 0644, 0);

    memory->buffer = (int*) mmap(
            NULL,
            sizeof(int),
            PROT_READ | PROT_WRITE,
            MAP_SHARED,
            memory->fd,
            0);

    return 0;
}

void reset() {
    if (shm_unlink(SHM_NAME) == -1)
        fprintf(stderr, "shm_unlink %s failed\n", SHM_NAME);

    if (sem_unlink(SEM1) == -1)
        fprintf(stderr, "sem_unlink %s failed\n", SEM1);

    if (sem_unlink(SEM2) == -1)
        fprintf(stderr, "sem_unlink %s failed\n", SEM2);

    printf("reset done\n");
}

void readMemory() {
    struct shared_memory memory;
    int i = 0;
    int j = 0;

    srand(time(NULL));

    if (init(&memory)) {
        fprintf(stderr, "init failed");
        return;
    }

    while(1) {
        sem_wait(memory.s_read);
        memory.buffer[i] = rand();
        fprintf(stdout,
                "read : j %d; i %d; buffer %d\n", j, i, memory.buffer[i]);

        i = (i + 1) % MAX_FILE;
        j++;
        sem_post(memory.s_write);
    }
}

void writeMemory() {
    struct shared_memory memory;
    int i = 0;
    int j = 0;

    srand(time(NULL));

    if (init(&memory)) {
        fprintf(stderr, "init failed");
        return;
    }

    while(1) {
        sem_wait(memory.s_write);
        memory.buffer[i] = rand();
        fprintf(stdout,
                "write : j %d; i %d; buffer %d\n", j, i, memory.buffer[i]);
        i = (i + 1) % MAX_FILE;
        j++;
        sem_post(memory.s_read);
    }
}


int main(int argc, char* argv[]) {
    if (argc < 2) {
        perror("You must provide an argument like 'read', 'write' or 'reset'");
        exit(1);
    }

    if (strcmp(argv[1], "read")== 0) {
        readMemory();
    } else if (strcmp(argv[1], "write") == 0) {
        writeMemory();
    } else if (strcmp(argv[1], "reset") == 0){
        reset();
    } else {
        perror("Wrong Argument. You must provide an argument like 'read', \
                'write' or 'reset'");
        exit(1);
    }
    return 0;
}
