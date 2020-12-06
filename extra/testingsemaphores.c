#include <pthread.h> 
#include <semaphore.h>
#include <errno.h>
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

int n, res=0;
sem_t mtx;

void * ThreadFunc(){
    int i, loc, sem;
    for(i=0; i<100;i++){
        sem = sem_wait(&mtx);
        if (sem != 0){
            printf("sem_wait error...\n");
            printf("errno value= %d definido como %s\n", errno, strerror(errno));
            pthread_exit(NULL);
        }
        res+=n;
        sem = sem_post(&mtx);
        if(sem != 0){
            printf("sem_post error...\n");
            printf("errno value= %d definido como %s\n", errno, strerror(errno));
            pthread_exit(NULL);
        }
    }
    pthread_exit(NULL);
}

int main(int argc, char **argv){
    pthread_t thread[10];
    n=atoi(argv[1]);
    printf("El numero introducido es %d\n", n);
    int sem = sem_init(&mtx, 0, 1);
    if(sem != 0){
        printf("sem_post error...\n");
        printf("errno value= %d definido como %s\n", errno, strerror(errno));
        pthread_exit(NULL);
    }
    for(int i=0; i<10; i++){
        if(pthread_create(&thread[i], NULL, ThreadFunc, NULL)){
            printf("\n ERROR creating thread\n");
            exit(EXIT_FAILURE); 
        }
    }
    for(int i=0; i<10; i++){
        if(pthread_join(thread[i], NULL)){
            printf("\n ERROR joining thread\n");
            exit(EXIT_FAILURE); 
        }
    }
    printf("Final value is %d, should be %d", res , n*1000);
    return 0;
}