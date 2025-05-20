/*
    Si realizzi un programma in C e Posix sotto Linux che, con l’ausilio della libreria Pthread, lancia n thread
    per cercare il valore minimo ed il valore massimo in una matrice nxn di interi. La ricerca del minimo e del
    massimo deve essere effettuata simultaneamente su tutte le righe. Individuati i valori cercati, si
    provvederà a stamparli a video. La dimensione della matrice può essere fornita in input al programma in
    fase di esecuzione o da riga di comando.
*/

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
int n;
int Mat[32][32];
pthread_t tid[32];
pthread_mutex_t mymutex=PTHREAD_MUTEX_INITIALIZER;
int max=0,min=9999;
int indice;

void * Funzione ()
{
    int j;
    pthread_mutex_lock(&mymutex);
    for(j=0;j<n;j++)
    {
        if(Mat[indice][j]>max)
        {
            max=Mat[indice][j];

        }
        else if (Mat[indice][j]<min)
        {
            min=Mat[indice][j];
        }
    }
    pthread_mutex_unlock(&mymutex);
    pthread_exit(NULL);
}

int main (int argc , char **argv)
{
    int i,j;
    if(argc!=2){
	printf("Numero di parametri errato!\n");
	return 1;
    }
    n=atoi(argv[1]);
    for(i=0;i<n;i++)
    {
        printf("\n");
        for(j=0;j<n;j++)
        {
            Mat[i][j]=1+rand()%70;
            printf("%d ",Mat[i][j]);
        }
    }
        for(i=0;i<n;i++)
        {

            indice=i;
            pthread_create(&tid[i],NULL,Funzione,NULL);
            pthread_join(tid[i],NULL);

        }
    printf("\n\nIl max : %d\n",max);
    printf("\n\nIl min : %d\n",min);

}

