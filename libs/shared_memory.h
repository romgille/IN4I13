#ifndef SHARED_MEMORY
#define SHARED_MEMORY

struct shared_memory {
    int fd;
    int* buffer;
    sem_t* s_read;
    sem_t* s_write;
};

#endif
