#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>


//Funcion ejemplo que escribe un aviso de llegada de la señal.
void tratarSennal(int n){
	printf("[SIGNAL] RECIVED FROM [PARENT] %d \n", n);
}

int main( int argc, char **argv){
	pid_t pid, pidd;
	int status;
	int m = 0;
	pid = fork();
    if(pid==-1){ //Error Case
        perror("fork error");
		printf("errno value = %d\n", errno);
		exit(EXIT_FAILURE);
    }	
	else if(pid == 0){

		printf("[SON] PID %d, FROM [PARENT] PID %d\n", getpid(), getppid());
		signal(SIGUSR1, tratarSennal);
		while(1);
		pause();
	}

	if(pid > 0){
		while(1){
			sleep(1);
			if(m==5){
				kill(pid, SIGKILL);
				printf("[SIGNAL] REMOVED\n");
                pidd=wait(&status);
                if(pidd > 0){
                    if (WIFEXITED(status))printf("[SON] with PID %d exited, with status %d\n", pidd, WEXITSTATUS(status));
                    else if(WIFSIGNALED(status))printf("[SON] with PID %d killed, with status %d\n", pidd, WTERMSIG(status));
                    else if(WIFSTOPPED(status))printf("[SON] with PID %d stopped, with status %d\n", pidd, WSTOPSIG(status));
                }
				exit(EXIT_SUCCESS);
			}
			kill(pid, SIGUSR1);

			m++;
		}

	}

}

