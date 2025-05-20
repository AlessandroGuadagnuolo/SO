#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(){
	int pfd[2],n;
	char *stringa="Messaggio di prova . . .";
	char buf[100];
	pipe(pfd);
	if(fork()==0){
		close(pfd[0]);
		write(pfd[1],stringa,strlen(stringa)+1);
		close(pfd[1]);
	}
	else{
		close(pfd[1]);
		n=read(pfd[0],buf,100);
		printf("Letti %d bytes: %s\n",n,buf);
		close(pfd[0]);
	}
}
