#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>

int val=0;
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
void *increment(){
	int loc,s;
    for(int i=0; i<10000; i++){
        s = pthread_mutex_lock(&mtx);
        
        if(s!=0){
            printf("Mutex lock error\n\n");
            pthread_exit(NULL);
        }

        loc=val;
    	loc++;
        val=loc;

        s = pthread_mutex_unlock(&mtx);
        
        if(s!=0){
            printf("Mutex unlock error\n\n");
            pthread_exit(NULL);
        }
	
    }
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