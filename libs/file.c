#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "file.h"


char * readLine(int fd)
{
	int i, nbr;
	char buf[TAILLEBUF];
	char * s;

	for(nbr = 0; nbr < TAILLEBUF; nbr++) {
		if(read(fd, buf+nbr, 1) <= 0) return NULL;

		if(buf[nbr] == '\n') break;
	}

	s = (char*) malloc(nbr + 1);

	if(s == NULL) {
		perror("alocation issue in litLigne");
		return NULL;
	}

	for(i = 0; i < nbr; i++) s[i] = buf[i];

	s[i] = '\0';

	return s;
}


int writeLine(char* chaine, int fd)
{
	int size_s = strlen(chaine);
	int nbw = 0;
	int tmp;

	while(nbw != size_s) {
		tmp = write(fd, chaine+nbw, size_s-nbw);
		if(tmp == -1){
			perror("write issue in ecritLigne");
			return -1;
		}
		nbw += tmp;
	}

    tmp = write(fd, "\n", 1);

	if(tmp == -1) {
		perror("write issue in ecritLigne");
		return -1;
	}

	return nbw;
}


/**
 * Read fdI and write it in fdO
 */
int copy(int fdI, int fdO) {
    char* chaine;

    while (1) {
        chaine = readLine(fdI);

        if (chaine == NULL) return 1;

        if (writeLine(chaine, fdO) == -1) {
            free(chaine);
            return -1;
        }

        free(chaine);
    }

    return 0;
}
