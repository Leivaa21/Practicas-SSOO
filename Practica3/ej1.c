#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>
#include <time.h>

int *stock,m,n;

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

void *rellenar();
void *purcharse(void *arg);
void *suplies(void *arg);

int main(int argc, char **argv){

    if(argc!=3){
        printf("[ERROR] Invalid arguments. 2 Parameters needed.\n");
        exit(EXIT_FAILURE);
    }

    n = atoi(argv[1]), m = atoi(argv[2]);
    int i;
    srand(time(NULL));
    pthread_t prov[m],clients[n];


    stock = (int*) malloc(m*sizeof(int));
    if ( stock == NULL ){
        printf("[ERROR] Memory isnt avalible. Failed to make the calloc\n");
        exit(EXIT_FAILURE);
    }
    for(i=0; i<m; i++)stock[i]=0;    


	if( pthread_create(&prov[i],NULL, (void*)rellenar, (int*) &m) ){
		printf("[Error] failed to create a thread. Errno value: %d\n",errno);
		exit(EXIT_FAILURE);
	}

    if( pthread_join(prov[i],NULL) ){
	  	printf("[Error] failed to wait a thread. Errno value: %d\n", errno);
	  	exit(EXIT_FAILURE); 
    }
    


    printf("\nStock de %d tipos de camisetas antes de abrir la tienda:\n |", m);
    for(i=0; i<m; i++)printf("  %d  |",stock[i]);    
    printf("\n\n");

    if(m>n){
        for(i=0; i<m; i++){
            if( pthread_create(&prov[i],NULL, (void*)suplies, (void*) NULL) ){
			    printf("[Error] failed to create a thread. Errno value: %d\n",errno);
			    exit(EXIT_FAILURE);
		    }
            if(i<n){
                if( pthread_create(&clients[i],NULL, (void*)purcharse, (void*) NULL) ){
                    printf("[Error] failed to create a thread. Errno value: %d\n",errno);
                    exit(EXIT_FAILURE);
                }
            }
        }
        for(i=0; i<m; i++){
            if( pthread_join(prov[i],NULL) ){
                printf("[Error] failed to wait a thread. Errno value: %d\n", errno);
                exit(EXIT_FAILURE); 
            }
            if(i<n){
                if( pthread_join(clients[i],NULL) ){
		  	        printf("[Error] failed to wait a thread. Errno value: %d\n", errno);
		  	        exit(EXIT_FAILURE);
                }
            }
        }
    }
        

    else{
        for(i=0; i<n; i++){
            if( pthread_create(&clients[i],NULL, (void*)purcharse, (void*) NULL) ){
                    printf("[Error] failed to create a thread. Errno value: %d\n",errno);
                    exit(EXIT_FAILURE);
		    }
            if(i<m){
                if( pthread_create(&prov[i],NULL, (void*)suplies, (void*) NULL) ){
			    printf("[Error] failed to create a thread. Errno value: %d\n",errno);
			    exit(EXIT_FAILURE);
                }
            }
        }
        for(i=0; i<n; i++){
            if( pthread_join(clients[i],NULL) ){
		  	    printf("[Error] failed to wait a thread. Errno value: %d\n", errno);
		  	    exit(EXIT_FAILURE);
            }
            if(i<m){
                if( pthread_join(prov[i],NULL) ){
                    printf("[Error] failed to wait a thread. Errno value: %d\n", errno);
                    exit(EXIT_FAILURE); 
                }
            }
        }
    }
    printf("\nStock de %d tipos de camisetas despues de cerrar la tienda:\n |", m);
    for(i=0; i<m; i++)printf(" %d |",stock[i]);    
    printf("\n");

    free(stock);
    exit(EXIT_SUCCESS);
}


void *rellenar(){
    int loc,s;
    for(int i=0; i<m; i++){
        
        s = pthread_mutex_lock(&mtx);
        if(s!=0){
            printf("[ERROR] Mutex lock failed\n\n");
            pthread_exit(NULL);
        }

        loc = stock[ i ];
        loc = (rand()%100+1);
        stock[ i ] = loc;
        s = pthread_mutex_unlock(&mtx);
        
        if(s!=0){
            printf("[ERROR] Mutex unlock failed\n\n");
            pthread_exit(NULL);
        }
    }

    pthread_exit(NULL);
}


void *purcharse(void *arg){

    int buy=rand()%10+1,
    type=rand()%m;

    int loc,s,bool=0;

    s = pthread_mutex_lock(&mtx);
    
    if(s!=0){
        printf("Mutex lock error\n\n");
        pthread_exit(NULL);
    }

    if(stock[type]<buy){
        printf("<-- Cliente %ld, quiso comprar %d unidades de la camiseta %d\n",pthread_self(), buy, type+1);
        printf(" STOCK INSUFICIENTE, solo pudo comprar %d\n",stock[type]);
        loc=stock[type];
        loc = 0;
        stock[type]=loc;
    }
    
    else{
        printf("<-- Cliente %ld, compro %d unidades de la camiseta %d\n",pthread_self(), buy, type+1);
        loc=stock[type];
        loc -= buy;
        stock[type]=loc;
    }
    s = pthread_mutex_unlock(&mtx);
    if(s!=0){
        printf("Mutex unlock error\n\n");
        pthread_exit(NULL);
    }
    pthread_exit(NULL);
}

void *suplies(void *arg){

    int sup=rand()%10+1,
    type=rand()%m;

    int loc,s;

    s = pthread_mutex_lock(&mtx);
    
    if(s!=0){
        printf("Mutex lock error\n\n");
        pthread_exit(NULL);
    }
    loc=stock[type];
    loc += sup;
    stock[type]=loc;
    s = pthread_mutex_unlock(&mtx);
    
    if(s!=0){
        printf("Mutex unlock error\n\n");
        pthread_exit(NULL);
    }
    printf("--> Proveedor %ld, suministro %d unidades de la camiseta %d\n",  pthread_self(), sup, type+1);
    pthread_exit(NULL);
}