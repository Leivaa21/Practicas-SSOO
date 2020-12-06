#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>
#include <time.h>

int par=0,impar=0;
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;


void *func (int *x);


int main(int argc, char **argv){
    if(argc!=2){
        printf("[ERROR] Invalid arguments. 1 Parameter needed.\n");
        exit(EXIT_FAILURE);
    }
    int i,n=atoi(argv[1]);
    int ressuma[n];
    pthread_t threads[n];
    srand(time(NULL));

    int index[n];
    for(i=0; i<n; i++) index[i]=i+1;


    for(i=0; i<n; i++)
        if(pthread_create(&threads[i], NULL, (void*)func, (int*)&index[i])){
            printf("[Error] failed to create a thread. Errno value: %d\n",errno);
	        exit(EXIT_FAILURE);
        }


    for(i=0; i<n; i++){
        int *result;
        if(pthread_join(threads[i], (void**) &result)){
            printf("[Error] failed to wait a thread. Errno value: %d\n", errno);
	  	    exit(EXIT_FAILURE); 
        }
        ressuma[i]=*(int*)result;
        free(result);
        printf("La hebra nº %d devolvio el valor de suma total: %d\n", i+1, ressuma[i]);
    }
    printf("\n Valor de la variable compartida impar: %d\n", impar);
    printf("\n Valor de la variable compartida par: %d\n\n", par);
}

void *func (int *x){

    int *res = malloc(sizeof(int));
    if ( res == NULL ){
        printf("[ERROR] Memory isnt avalible. Failed to make the calloc\n");
        exit(EXIT_FAILURE);
    }
    *res=0;
    int loc, s;

    for(int i=0; i<5; i++) *res+=rand()%10+1;
    
    s = pthread_mutex_lock(&mtx);

    if(s!=0){
        printf("Mutex lock error\n\n");
        pthread_exit(NULL);
    }

    if(*x%2==0){
        loc=par;
        loc += *res;
        par=loc;
    }
    else {
        loc=impar;
        loc += *res;
        impar=loc;
    }

    s = pthread_mutex_unlock(&mtx);
    
    if(s!=0){
        printf("Mutex unlock error\n\n");
        pthread_exit(NULL);
    }

    pthread_exit(res);
}