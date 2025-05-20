/*2. 6 punti (PER CFU 12 e 10)
Scrivere un programma C e Posix sotto Linux che riceve da riga di comando il nome di una directory e di
un file. Il programma crea un processo figlio che cerca il carattere “a” all’interno del file regolare il cui
nome corrisponde a quello passato come argomento e ad ogni occorrenza del carattere invia un segnale
SIGUSR1 al processo padre. Il processo padre conta il numero di occorrenze del segnale e dunque del
numero di occorrenze del carattere “a” nel file. Il processo padre, inoltre, crea nella directory corrente un
file conta.dat con diritti di lettura e scrittura per il proprietario, il gruppo e per gli altri e vi scrive il
numero di occorrenze del carattere “a”.
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>


static void handler(int);

int occ=0,n=0;

int main(int argc, char *argv[])
{
	char file[100], directory[100];
	sscanf(argv[1],"%s",directory);	//Leggo la directory e il file dove trovare le occorrenze
	sscanf(argv[2],"%s",file);
	printf("La directory è: %s, ed il file è: %s.\n",directory, file);
	DIR *dp;
	struct dirent *dirp;
	int pid;
	signal(SIGUSR1,handler);	
	if((pid = fork()) != 0)		//PADRE
	{
		wait(NULL);					//Il padre aspetta che il figlio termini
		printf("Il numero di occorrenze è:%d.\n",occ);
		int fd;
		umask(000);										//Imposto la maschera a zero
		fd=open("conta.dat",O_WRONLY|O_CREAT,0666);		//E posso mettere i permessi decisi
		write(fd,&occ,sizeof(int));						//Scrivo sul file il numero di occorrenze
		close(fd);
	}
	else		//FIGLIO
	{
		struct stat buf;
		if((dp=opendir(directory)) == NULL)				//Apro la directory
		{
			printf("Impossibile aprire la directory.\n");
			exit(0);
		}
		while((dirp=readdir(dp)) != NULL)				//Per ogni file contenuto nella directory
		{
			if( strcmp(dirp->d_name, file) == 0 )		//Vedo se è quello che cerco
			{
				printf("Il file %s è stato trovato.\n",file);
				chdir(directory);						//Se è così cambio la directory corrente
				if(stat(file,&buf) < 0)					//Prendo le info del file
				{
					printf("Stat ERROR.\n");
					perror("stat");
					closedir(dp);
					exit(0);
				}
				if(S_ISREG(buf.st_mode))				//Controllo che sia un file regolare
				{
					int fd,n;
					char car;
					fd=open(file, O_RDONLY);			//Lo apro in lettura
					while((n=read(fd,&car,1)) > 0)		//Per ogni carattere vedo se è uguale ad 'a'
						if(car == 'a')
						{
							kill(getppid(),SIGUSR1);	//Trovato il carattere invio il segnale al padre
							sleep(1);					//Do il tempo al padre di incrementare
						}
					close(fd);
				}
			}
		}
		closedir(dp);
	}
	exit(0);
}


static void handler(int signo)
{
	if(signo==SIGUSR1)				//Il padre riceve il segnale ed incrementa il numero di occorrenze
	{
		//printf("Padre: incremento.\n");
		occ++;
	}
}
