#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){

	int rc = fork();
	if(rc < 0){
		fprintf(stderr, "could not execute fork()");
	} else if (rc == 0){
		// child
		printf("hello (pid: %d)\n", (int) getpid());
	} else{
		// parent
		//wait(NULL);
		printf("goodbye (parent of %d) (pid: %d)\n", rc, (int) getpid());
	}

}

/*
 * It is difficult to print hello before goodbye without calling wait()
 * in the parent process when this program is run on multiple cores.
 * The reason is that when the program gets run on multiple cores,
 * the order in which the processes finish is non-deterministic.
 *
 * We can ensure that hello prints before goodbye by either calling wait()
 * or by running this program on a single CPU core.
 * */
