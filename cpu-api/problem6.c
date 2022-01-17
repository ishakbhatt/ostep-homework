#define _POSIX_SOURCE
#include <sys/types.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
	int rc = fork();

	
	if (rc < 0) {
		// fork failed
		fprintf(stderr, "fork failed\n");
		exit(1);
	} else if (rc == 0){
		// child
		printf("child\n");
		exit(0);
	} else {
		// parent
		int status;
		waitpid(rc, &status, 0);
		printf("parent\n");
	}
}

/*
 * waitpid() suspends calling process until system gets status info 
 * on child (pid passed in) or signal to execute signal handler/exit.
 * This is different from wait() because if there are multiple
 * child processes, waitpid() allows waiting for a specific child to finish
 * and the progress on that child process can be tracked through the end of
 * its execution.
 * */
