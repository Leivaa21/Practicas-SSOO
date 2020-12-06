#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#include <time.h>

#define MAX 10

void* Suma(float *res);

int main(int argc, char **argv){
    
    // Comprobamos que el usuario introduce el parametro necesario
    if(argc!=2){
        printf("[ERROR] Invalid arguments. 1 Parameter needed.\n");
        exit(EXIT_FAILURE);
    }
    
    srand(time(NULL));

    pthread_t x;

    int n;
    n=atoi(argv[1]);
    float suma;

    for(int i=0; i<n; i++){
    
        if(pthread_create(&x,NULL,(void*) Suma, (float*) &suma)){
			printf("[Error] failed to create a thread. Errno value: %d\n",errno);
			exit(EXIT_FAILURE);
		} 

		printf("Thread created %d\n", i+1);

		if( pthread_join(x, NULL) ){
		  	printf("[Error] failed to wait a thread. Errno value: %d\n", errno);
		  	exit(EXIT_FAILURE);  
		} 
		
        printf(" Thread %d ended\n\n", i+1);
	}

	printf("Final value: %f\n",suma);
	exit(EXIT_SUCCESS);

}

void* Suma(float *res){

    float n1= (float)rand()/RAND_MAX * MAX,
        n2=  (float)rand()/RAND_MAX * MAX;

    *res+= n1+n2;

    printf(" This thread got: %f\n", n1+n2);

    pthread_exit(NULL);
}