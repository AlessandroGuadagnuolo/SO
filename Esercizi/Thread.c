#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

pthread_t ntid;
void stampatid(const char *s){
	pid_t pid;
	pthread_t tid;
	pid=getpid();
	tid=pthread_self();
	printf("%s pid %lu tid %lu (0x%lx)\n",s,(unsigned long) pid, (unsigned long) tid, (unsigned long) tid);
}

void * funzione(void *arg){
	stampatid("nuovo thread ");
	return((void *)0);
}

int main(){
	int err;
	err=pthread_create(&ntid, NULL, funzione, NULL);
	if(err!=0){
		printf("Thread non creato");
		exit(1);
	}
	stampatid("Thread principale");
	sleep(1);
	exit(0);
}
