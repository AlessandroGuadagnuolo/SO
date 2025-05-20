#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

struct stampa{
	char carattere;
	int count;
};

void* stampacar(void* parametro)
{
	struct stampa* p= (struct stampa*) parametro;
	int i;
	for(i=0;i<p->count;++i)
		fputc(p->carattere,stderr);
	return NULL;
}

int main(){
	pthread_t tid1;
	pthread_t tid2;
	struct stampa tid1_args;
	struct stampa tid2_args;

	tid1_args.carattere='x';
	tid1_args.count=2;
	pthread_create(&tid1,NULL,stampacar,(void*)&tid1_args);

	tid2_args.carattere='A';
	tid2_args.count=3;
	pthread_create(&tid2,NULL,stampacar,(void*)&tid2_args);
	
	sleep(1);
	return 0;
}
