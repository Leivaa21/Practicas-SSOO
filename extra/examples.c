#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
sem_t semaphore;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int queue[50];
int queueLength;
void *producer( void * param)
{
    for ( int i=0; i<50; i++ )
    {
        // Add item to queue
        pthread_mutex_lock( &mutex );
        queue[ queueLength++ ] = i;
        printf("Sent %d\n", i);
        pthread_mutex_unlock( &mutex );
        // Signal semaphore

        sem_post( &semaphore );
    }
}
void *consumer(void * param)
{
    for ( int i=0; i<50; i++ )
{
    int item;

    // wait for signal
    sem_wait(&semaphore);

    pthread_mutex_lock( &mutex );
    item = queue[--queueLength];
    pthread_mutex_unlock( &mutex );
    printf("Received %i\n", item);
}
}
int main()
{
    pthread_t threads[2];
    sem_init( &semaphore, 0, 1 );
    pthread_create( &threads[0], 0, producer, 0 );
    pthread_create( &threads[1], 0, consumer, 0 );
    pthread_join( threads[0], 0 );
    pthread_join( threads[1], 0 );
    sem_destroy( &semaphore );
}