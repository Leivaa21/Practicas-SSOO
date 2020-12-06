#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>

int f(int n){
	alarm(n); 
	pause();
}

void sigalarm(int sign){
	printf(" RING");
	printf("[SIGNAL] Value: %d\n\n\n", sign);
}

void printandkill(int n){
	printf(" [ALARM] in %d secs\n", n);
	kill(getpid(), f(n));
}


int main( int argc, char **argv){
	int n=0;

	if(signal(SIGALRM, sigalarm) == SIG_ERR){
		perror("[ERROR] signal error");
		printf(" Errno value: %d\n", errno);
		exit(EXIT_FAILURE);
	}

	printandkill(5);

    printandkill(3);

	while(n >= 0){
		printandkill(1);
		n++;
		if(n == 4) kill(getpid(), SIGKILL);
	}

	exit(EXIT_SUCCESS);
}