#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
int valor = 0;

int main( int argc, char **argv){
    // Comprobamos que el usuario introduce el parametro necesario
    if(argc!=2){
        printf("[ERROR] Invalid arguments. 1 Parameter needed.\n");
        exit(EXIT_FAILURE);
    }
	pid_t pid, pidd;
	int status ,n;
    n=atoi(argv[1]);

	for(int i=0 ; i<n; i++){
		pid = fork();
		if(pid==-1){ //caso error
			perror("fork error");
			printf(" Errno value = %d\n", errno);
			exit(EXIT_FAILURE);
        }
		if(pid==0){ //hijo
            printf("[SON #%d] PID %d, FROM [PARENT] PID %d\n", i+1, getpid(), getppid());
			valor++;
            printf("I have modified the valor! %d\n", valor);
			exit(EXIT_SUCCESS);
        }
	}

	

	printf("[PARENT] with PID %d, from parent with PID %d [PPID]\n", getpid(), getppid());

	for(int i=0 ; i<n; i++){
		if(pidd > 0){
            pidd=wait(&status);
            if (WIFEXITED(status))printf("[SON #%d] with PID %d exited, with status %d\n", i+1, pidd, WEXITSTATUS(status));
            else if(WIFSIGNALED(status))printf("[SON #%d] with PID %d killed, with status %d\n", i+1, pidd, WTERMSIG(status));
            else if(WIFSTOPPED(status))printf("[SON #%d] with PID %d stopped, with status %d\n", i+1, pidd, WSTOPSIG(status));
		}
		else {
		    printf("[ERROR]\n");
		 	exit(EXIT_FAILURE);
        } 

	    printf(" [SON] %d. Valor: %d\n", i+1, valor);	

	    }

	exit(EXIT_SUCCESS);

}