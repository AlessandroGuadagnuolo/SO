/* Esempio di creazione pipe per lanciare ls | sort */ 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
	int pfd[2],pid;
	pipe(pfd);
	pid=fork();
	if(pid==0){
		close(pfd[0]);
		dup2(pfd[1],1);
		execlp("ls","ls",NULL);
	}
	else if(pid>0){
		close(pfd[1]);
		dup2(pfd[0],0);
		execlp("sort","sort",NULL);
	}
}
