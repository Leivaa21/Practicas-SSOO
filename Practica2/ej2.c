#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>

void *linecount(char *filename);

int main(int argc, char **argv){

	pthread_t x[argc-1];

	if(argc < 2){
		printf("Missing args \n Please do ./a.out file1 file2 etc..\n");
		exit(EXIT_FAILURE);
	}

	for ( int i=0; i<argc-1; i++){
		if( pthread_create(&x[i],NULL, (void*) linecount, argv[i+1]) ){
			printf("[Error] failed to create a thread. Errno value: %d\n",errno);
			exit(EXIT_FAILURE);
		}
    }
    int val[argc-1];
    int *res;
	for ( int i=0; i<argc-1; i++){
        if( pthread_join(x[i],(void**) &res) ){
		  	printf("[Error] failed to wait a thread. Errno value: %d\n", errno);
		  	exit(EXIT_FAILURE); 
        }
        val[i]=*(int*)res;
        printf("\n Thread %d value: %d\n",i+1, val[i]);
    }
    int value=0;
    for(int i=0; i<argc-1; i++) value+=val[i];
    printf("\n Final value: %d\n", value);

	exit(EXIT_SUCCESS);	

}

void *linecount(char *filename){
    int *suma=malloc(sizeof(int));
	char buffer[100];
	FILE* f=fopen(filename, "r");
    if(f==NULL){
        printf("[ERROR] %s CANT BE OPENED, Errno value: %d \n",filename, errno);
        exit(EXIT_FAILURE);
    }

	while( fgets(buffer,100,f) != NULL) (*suma)++;

	fclose(f);
	pthread_exit((void*) suma);
}
