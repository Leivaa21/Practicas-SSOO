#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

int main(int argc, char **argv){
    // Comprobamos que el usuario introduce el parametro necesario
    if(argc!=2){
        printf("[ERROR] Invalid arguments. 1 Parameter needed.\n");
        exit(EXIT_FAILURE);
    }
    int n, status;
    n=atoi(argv[1]);
    pid_t pid, pidd;
    for(int i= 1 ; i<n; i++){

		pid = fork();
		
        if(pid==-1){ //Error Case
            perror("fork error ");
			printf("errno value = %d\n", errno);
			exit(EXIT_FAILURE);
        }
        else if(pid==0) //SON case
            printf("[SON] PID %d, FROM [PARENT] PID %d\n",getpid() ,getppid());

        else {
            printf("[PARENT] with PID %d, from parent with PID %d [PPID]\n", getpid(), getppid());

            pidd=wait(&status);
            if(pidd > 0){
                
                if (WIFEXITED(status))printf("[SON] with PID %d exited, with status %d\n", pidd, WEXITSTATUS(status));
                else if(WIFSIGNALED(status))printf("[SON] with PID %d killed, with status %d\n", pidd, WTERMSIG(status));
                else if(WIFSTOPPED(status))printf("[SON] with PID %d stopped, with status %d\n", pidd, WSTOPSIG(status));
                else {
                    printf("[ERROR]\n");
                    exit(EXIT_FAILURE);
                } 	
            }
        }

    }

	exit(EXIT_SUCCESS);

}