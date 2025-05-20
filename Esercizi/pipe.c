#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 1024

int main(){
	int pipe_fd[2];
	int n;
	int pid;
	char buf[SIZE];
	if(pipe(pipe_fd)==-1){ //controllo se la pipe viene creata
		printf("Errore pipe() \n");
		exit(-1);
	}
	if((pid=fork())<0){ //controllo se il processo viene creato
		printf("Errore fork() \n");
		exit(-2);
	}
	if(pid==0){ //entra il figlio
		close(pipe_fd[1]); //chiudo in scrttura poichè in questo es. il figlio legge
		while((n=read(pipe_fd[0],buf,SIZE))!=0) //leggo dal buffer
			printf("Il figlio legge %s",buf);
		close(pipe_fd[0]); //chiudo il canale in lettura
	}
	else{ //entra il padre
		close(pipe_fd[0]); //al contrario chiudo in lettura poichè in questo es il padre scrive
		strcpy(buf,"\nSono tuo padre.\n"); //scrivo qualcosa nel buffer
		write(pipe_fd[1],buf,strlen(buf)+1); //scrivo nel buffer dal byte successivo
		close(pipe_fd[1]); //chiudo il canale in scrittura
	}
	exit(0);
}
