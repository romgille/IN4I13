#ifndef FILE_MANAGEMENT_H
#define FILE_MANAGEMENT_H

#define TAILLEBUF 8191

/*
 * Read one line from fd
 *
 * Create an allocation, remember to free
 */
char * readLine(int fd);


/*
 * Write chaine on one line in fd
 */
int writeLine(char* chaine, int fd);


/**
 * Read fdI and write it in fdO
 */
int copy(int fdI, int fdO);

#endif
