#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>

int main(){
    pid_t pid, pidd;
    int status;
    pid=fork();
    switch(pid){
        case 0:
            printf("[SON] PID %d, FROM [PARENT] PID %d\n", getpid(), getppid());
            exit(EXIT_SUCCESS);
        case -1: 
            printf("ERRNO = %d", errno);
            exit(EXIT_FAILURE);
        default:
            sleep(4);
            printf("[PARENT] with PID %d, from parent with PID %d [PPID]\n", getpid(), getppid());
            exit(EXIT_SUCCESS);
    }
    return 0;
}