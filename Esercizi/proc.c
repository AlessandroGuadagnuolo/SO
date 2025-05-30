#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main (int argc, char *argv[]) {
	pid_t childpid = 0;
	int i, n;
	if (argc != 2){ /* controllo argomenti */
		fprintf(stderr, "Uso: %s processi\n", argv[0]);
		return 1;
	}
	n = atoi(argv[1]);
	for (i = 1; i < n; i++)
		if (childpid = fork())
			break;
	printf("i:%d processo ID:%d padre ID:%d figlio ID:%d\n", i,
	getpid(), getppid(), childpid);
	exit(0);
} 
