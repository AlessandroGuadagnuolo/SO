#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc,char *argv[]){
	char n[20];
	/*if(argc!=2){	
		printf("Num parametri errato\n");
		exit(1);
	}*/
	sscanf(argv[1],"%s",n);
	printf("Il nome e': %s\n",n);
	
}