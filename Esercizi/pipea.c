#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(){
	int pfd[2];
	pid_t pid;
	if(pipe(pfd)==-1){
		perror("Pipe() fallita");
		exit(-1);
	}
	if(pid=fork()<0){
		printf("Fork() fallita");
		exit(-2);
	}
	
	if(pid==0){
		close(pfd[1]);
		dup2(pfd[0],STDIN_FILENO);
		execlp("sort","sort",NULL);
		perror("Il figlio non ha eseguito i comandi\n");
		exit(-3);
	}

	else{
		close(pfd[0]);
		write(pfd[1],"Test 1.\n",9);
		write(pfd[1],"Test 2..\n",10);
		write(pfd[1],"Test 3...\n",11);
		close(pfd[1]);
		waitpid(pid,NULL,0);
	}
	return 0;
}
