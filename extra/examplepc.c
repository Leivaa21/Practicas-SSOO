//BUFFER SIZE = 1

#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#define SHARED 1
void *Producer(); // Make Declaration of Producer
void *Consumer(); // Make Declaration of Consumer
sem_t empty, full,sm; //Declare semaphores to be used
int data; // data variable


int main()
{
    pthread_t ptid, ctid; // Line 1
    printf("\nMain Started");
    sem_init(&empty, SHARED, 1); // Line 2
    sem_init(&full, SHARED, 0); // Line 3
    sem_init(&sm, SHARED, 1);// Line 4
    pthread_create(&ptid,NULL,Producer,NULL); // Line 5
    pthread_create(&ctid,NULL,Consumer,NULL); // Line 6
    pthread_join(ptid,NULL); // Line 7
    pthread_join(ctid,NULL); // Line 8
    printf("\nMain done\n");
}

void *Producer()
{
    //ITEM PRODUCED...
    int produced;
    printf("\nProducer created");
    printf("\nProducer id is %ld\n",pthread_self()); //print thread id
    for(produced=0;produced<100;produced++)
    {
    sem_wait(&empty);
    // LOCK-starts
        sem_wait(&sm);
            //CRITICAL SECTION STARTS
                    data++;
            //CRITICAL SECTION ENDS
        sem_post(&sm);
    //LOCK-ends
    sem_post(&full);
    printf("\nProducer makes data : %d",data);
    }
}

void *Consumer()
{
    int consumed, total=0;
    printf("\nConsumer created\n");
    printf("\nConsumer id is %ld\n",pthread_self());
    for(consumed=0;consumed<100;consumed++)
    {
    sem_wait(&full);
    //LOCK-starts
        sem_wait(&sm);
                //CRITICAL SECTION STARTS
                        data--;
                //CRITICAL SECTION ENDS
        sem_post(&sm);
    //LOCK-ends
    sem_post(&empty);
    printf("\nConsumed makes data: %d",data);
    }
    printf("\nThe total of 100 iterations is %d\n",data);
}