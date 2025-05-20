#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

void *funzione1(void *arg){
	printf("Thread 1 returning \n");
	return((void *)1);
}

void *funzione2(void *arg){
	printf("Thread 2 exiting \n");
	pthread_exit((void *)2);
}


int main(){
	int err;
	pthread_t tid1,tid2;
	void *ptr;
	err=pthread_create(&tid1,NULL,funzione1,NULL);
	if(err!=0)
	{
		printf("Thread 1 non creato. ");
		exit(1);
	}
	err=pthread_create(&tid2,NULL,funzione2,NULL);
	if(err!=0)
	{
		printf("Thread 2 non creato. ");
		exit(1);
	}
	err=pthread_join(tid1,&ptr);
	if(err!=0)
		printf("Pthread join error. %s ",strerror(err));
	printf("Thread 1 exit code %ls\n ",(int *)ptr);
	err=pthread_join(tid2,&ptr);
	if(err!=0)
		printf("Pthread join error. %s ",strerror(err));
	printf("Thread 2 exit code %ls\n ",(int *)ptr);
	exit(0);
}
