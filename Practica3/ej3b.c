#include <pthread.h> 
#include <semaphore.h>
#include <errno.h>
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAM_BUFFER 3
#define MAX_RAND 10

sem_t isempty, isfull, buffersize;

int buffer[TAM_BUFFER],buffin=0,buffout=0;

void *producer();
void *consumer();
int crearNumeroAleatorio(){
    return (rand()%MAX_RAND+1);
}

int main(){

    int i;
    for(i=0; i<3; i++)printf(" %d ", buffer[i]);
    printf("\n");

    srand(time(NULL));
    pthread_t ptid[3], ctid[3];
    sem_init(&isempty, 1, 1);
    sem_init(&isfull, 1, 0);
    sem_init(&buffersize, 1, TAM_BUFFER);
    int index[3] = {0, 1, 2};

    for(i=0; i<3; i++){
        if(pthread_create(&ptid[i], NULL, producer, &index[i])){
           printf("[Error] failed to create a thread. Errno value: %d\n",errno);
	        exit(EXIT_FAILURE); 
        }
        if(pthread_create(&ctid[i], NULL, consumer, &index[i])){
            printf("[Error] failed to create a thread. Errno value: %d\n",errno);
	        exit(EXIT_FAILURE);
        }
    }

    for(i=0; i<3; i++){
        if(pthread_join(ptid[i],NULL)){
            printf("[Error] failed to wait a thread. Errno value: %d\n", errno);
	  	    exit(EXIT_FAILURE); 
        }
        if(pthread_join(ctid[i],NULL)){
            printf("[Error] failed to wait a thread. Errno value: %d\n", errno);
	  	    exit(EXIT_FAILURE); 
        }
    }

    for(int i=0; i<3; i++)printf(" %d ", buffer[i]);
    printf("\n");

    exit(EXIT_SUCCESS);
}



void *producer(){
    int i; 
    printf("Producer is online with id = %ld \n", pthread_self());
    sem_wait(&isempty);
        sem_wait(&buffersize);

            buffer[buffin]=crearNumeroAleatorio();
            printf("[PRODUCE] a %d in slot %d\n",buffer[buffin],buffin);
            buffin=(buffin+1)%TAM_BUFFER;
        
        sem_post(&buffersize);
    sem_post(&isfull);
    
    pthread_exit(NULL);
}


void *consumer(){
    int i,datoLeido;
    printf("Consumer is online with id = %ld \n", pthread_self());
    
    sem_wait(&isfull);
        sem_wait(&buffersize);
            
            datoLeido=buffer[buffout];
            printf("[CONSUME] a %d from slot %d\n",datoLeido,buffout);
            buffout=(buffout+1)%TAM_BUFFER;
            
        sem_post(&buffersize);
    sem_post(&isempty);

    pthread_exit(NULL);
}
