#include "process.h"
#include <stdio.h>
#include <unistd.h>

int print_pid(char* chaine) { return printf("%d : %s", getpid(), chaine); }

int print_ppid(char* chaine) { return printf("%d : %s", getppid(), chaine); }

int print_all(char* chaine) { return printf("%d > %d : %s", getppid(), getpid(), chaine); }
