#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>

void calculadora(char *f){
    if(execlp(f,f,(char*)NULL)<0){
        perror("exec");
        printf("ERRNO = %d\n", errno);
        exit(EXIT_FAILURE);
    }
}
void ficheros(char *f, char **ff){
    if(execvp(f,ff)<0){
        perror("exec");
        printf("ERRNO = %d\n", errno);
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char **argv){
    int status, n;
    pid_t pid, pidd;
    printf("Introduce el numero del fichero: ");
    scanf("%d", &n);
        // Comprobamos que el usuario introduce el parametro necesario
    if(argc!=3+n){
        printf("[ERROR] Invalid arguments. %d Parameters needed.\n", 2+n);
        exit(EXIT_FAILURE);
    }
    for(int i=0; i<2; i++){
        pid=fork();
        if(pid==-1){
            printf("ERRNO: %d\n", errno);
            exit(EXIT_FAILURE);
        }
        else if(pid==0){
            if(i==0){
                printf("[SON #%d] PID %d\n", i+1, getpid());
                calculadora(argv[1]);
            }
            else{
                printf("[SON #%d] PID %d\n", i+1, getpid());
                ficheros(argv[2], &argv[2]);
            }
        }
        else if(pid>0){
            printf("[PARENT] PID %d\n", getpid());
            pidd=wait(&status);
            if (WIFEXITED(status))printf("[PARENT] is waiting [SON #%d] with status %d\n", pidd, WEXITSTATUS(status));
            else if(WIFSIGNALED(status))printf("[SON #%d] dead, his status is %d\n", pidd, WTERMSIG(status));
            else if(WIFSTOPPED(status))printf("[SON #%d] has stopped, his status is %d\n", pidd, WSTOPSIG(status));
            else{
                printf("[ERROR] on wait %d", errno);
                exit(EXIT_SUCCESS);
            }
        }
    }
    exit(EXIT_SUCCESS);
}