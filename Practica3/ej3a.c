#include <pthread.h> 
#include <semaphore.h>
#include <errno.h>
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAM_BUFFER 5
sem_t isempty, isfull, buffersize;

int buffer[TAM_BUFFER];

void *producer();
void *consumer();
int crearNumeroAleatorio(){
    return (rand()%10+1);
}

int main(){
    for(int i=0; i<5; i++)printf(" %d ", buffer[i]);
    printf("\n");

    srand(time(NULL));
    pthread_t ptid, ctid;
    sem_init(&isempty, 1, 1);
    sem_init(&isfull, 1, 0);
    sem_init(&buffersize, 1, TAM_BUFFER);
    if(pthread_create(&ptid, NULL, producer, NULL)){
        printf("[Error] failed to create a thread. Errno value: %d\n",errno);
	    exit(EXIT_FAILURE);
    }
    if(pthread_create(&ctid, NULL, consumer, NULL)){
        printf("[Error] failed to create a thread. Errno value: %d\n",errno);
	    exit(EXIT_FAILURE);
    }
    if(pthread_join(ptid,NULL)){
        printf("[Error] failed to wait a thread. Errno value: %d\n", errno);
	  	exit(EXIT_FAILURE); 
    }
    if(pthread_join(ctid,NULL)){
        printf("[Error] failed to wait a thread. Errno value: %d\n", errno);
	  	exit(EXIT_FAILURE); 
    }

    for(int i=0; i<5; i++)printf(" %d ", buffer[i]);
    printf("\n");
    
    exit(EXIT_SUCCESS);

}



void *producer(){
    int i,buffin=0;; 
    printf("Producer is online with id = %ld \n", pthread_self());

    for(i=0; i<10; i++){
    sem_wait(&isempty);
        sem_wait(&buffersize);
            buffer[buffin]=crearNumeroAleatorio();
            printf("[PRODUCE] a %d in slot %d\n",buffer[buffin],buffin);
            buffin=(buffin+1)%TAM_BUFFER;

            
        sem_post(&buffersize);
    sem_post(&isfull);
    }
    pthread_exit(NULL);
}


void *consumer(){
    int i,buffout=0,datoLeido;
    printf("Consumer is online with id = %ld \n", pthread_self());

    for(i=0; i<10; i++){
        sem_wait(&isfull);
            sem_wait(&buffersize);
                
                datoLeido=buffer[buffout];
                printf("[CONSUME] a %d from slot %d\n",datoLeido,buffout);
                buffout=(buffout+1)%TAM_BUFFER;

                
            sem_post(&buffersize);
        sem_post(&isempty);
    }

    pthread_exit(NULL);
}
