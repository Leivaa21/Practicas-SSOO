#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <errno.h>

struct args{
    int suma,n,v[10],start;
}typedef args_t;

void *SumaVector(args_t *x);

int main(int argc, char **argv){

    // Comprobamos que el usuario introduce el parametro necesario
    if(argc!=2){
        printf("[ERROR] Invalid arguments. 1 Parameter needed.\n");
        exit(EXIT_FAILURE);
    }
    int n=atoi(argv[1]);
    if(n!=2&&n!=5){
        printf("[ERROR] Arg needs to be 2 or 5\n");
        exit(EXIT_FAILURE);
    }
    args_t arguments;
    arguments.n=10/n;
    arguments.suma=0;
    arguments.start=0;
    srand(time(NULL));

    for(int i=0; i<10 ;i++){
        arguments.v[i]=rand()%10;
        printf("v[%d] = %d\n", i, arguments.v[i]);
    }


    pthread_t x[n];
    int *res;
    int val[n];

    for(int i=0; i<n; i++){
        if(pthread_create(&x[i], NULL, (void*) SumaVector,&arguments)){
            printf("[Error] failed to create a thread. Errno value: %d\n",errno);
			exit(EXIT_FAILURE);
        }
    }
    
    for(int i=0; i<n; i++){
		if(pthread_join(x[i], (void**) &res)){
		  	printf("[Error] failed to wait a thread. Errno value: %d\n", errno);
		  	exit(EXIT_FAILURE);  
		}
        
        val[i]=*(int*)res;
        printf("\n Thread %d value: %d\n",i+1, val[i]);
    }
    int value=0;
    for(int i=0; i<n; i++) value+=val[i];
    printf("\n Final value: %d\n", value);
    exit(EXIT_SUCCESS); 
}

void *SumaVector(args_t *x){
    
    int *res=malloc(sizeof(int));

	if( res == NULL ){
		printf(" [Error] No memory left\n");
		exit(EXIT_FAILURE);
	}

    *res=0;

    for(int i=x->start; i<(x->n+x->start); i++){
        *res+=x->v[i];
    }
    x->start+=x->n;
    pthread_exit((void*) res);
}
