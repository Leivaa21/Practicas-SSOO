#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>

int val=0;

void *increment(void* argc){
	for(int i=0; i<10000; i++)	val++;
	pthread_exit(NULL);
}


int main(){

    pthread_t x[2];
    
    printf( " Global variable value : %d\n", val );

    for(int i=0; i<2; i++){
		if( pthread_create(&x[i],NULL, (void*)increment, (void*) NULL) ){
			printf("[Error] failed to create a thread. Errno value: %d\n",errno);
			exit(EXIT_FAILURE);
		}
    }

    for(int i=0; i<2; i++){
        if( pthread_join(x[i],NULL) ){
		  	printf("[Error] failed to wait a thread. Errno value: %d\n", errno);
		  	exit(EXIT_FAILURE); 
        }
    }
    printf( " Global variable value : %d\n", val );
    exit(EXIT_SUCCESS);
}