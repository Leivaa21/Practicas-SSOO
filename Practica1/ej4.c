#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

long factorial(int n){
    if(n==0)return 1;
    return (n*factorial(n-1));
}

int main(int argc, char** argv){
        // Comprobamos que el usuario introduce el parametro necesario
    if(argc!=3){
        printf("[ERROR] Invalid arguments. 2 Parameter needed.\n");
        exit(EXIT_FAILURE);
    }
	pid_t pid, pidd;
	int n1=atoi(argv[1]), n2=atoi(argv[2]), status;


	for(int i=0; i<2; i++){

		pid = fork();
        if(pid==-1){ //ERROR case
        
            printf("fork error");
            printf(" Errno value: %d\n",errno);
            exit(EXIT_FAILURE);
        }
			
        else if(pid==0){ //SON case

            printf("[SON #%d] PID %d, FROM [PARENT] PID %d\n", i+1, getpid(), getppid());
            if(i==0){
                printf("%d! is equal to %ld\n",n1,factorial(n1));
                exit(EXIT_SUCCESS);
            }
            else{
                printf("%d! is equal to %ld\n", n2, factorial(n2));
                exit(EXIT_SUCCESS);
            }
            sleep(1);
            exit(EXIT_SUCCESS);
        }
	}

	printf(" Proceso padre: %d\n", getpid() );

	for(int i=0 ; i<2; i++){

        if(pidd > 0){
            pidd=wait(&status);
            if (WIFEXITED(status))printf("[SON #%d] with PID %d exited, with status %d\n", i+1, pidd, WEXITSTATUS(status));
            else if(WIFSIGNALED(status))printf("[SON #%d] with PID %d killed, with status %d\n", i+1, pidd, WTERMSIG(status));
            else if(WIFSTOPPED(status))printf("[SON #%d] with PID %d stopped, with status %d\n", i+1, pidd, WSTOPSIG(status));
        }

        else {
            printf("[ERROR]");
            exit(EXIT_FAILURE);
        } 	

   	}
	exit(EXIT_SUCCESS);
}

