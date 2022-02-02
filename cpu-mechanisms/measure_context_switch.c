#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char * argv[]){
	// create pipes: two file descriptors for read/write
	int pipe1[2];
	int pipe2[2];
	
	// info for pipe and track child proc
	pid_t child_pid;
	char input[10] = "info";

	// create & error check pipes
	if(pipe(pipe1) == -1){
		fprintf(stderr, "Pipe 1 failed");
	}

	if(pipe(pipe2) == -1){
		fprintf(stderr, "Pipe 2 failed");
	}
	
	// create a child proc
	child_pid = fork();

	// handle three fork cases: error, parent, child
	if(child_pid < 0){ // error
		fprintf(stderr, "fork() failed");
	} else if(child_pid > 0){ // parent
		long long time;
		time = -clock();

		// close read end
		close(pipe1[0]);

		// send string to proc 2
		write(pipe1[1], input, strlen(input) + 1);
		
		// close write from proc 1
		close(pipe1[1]);

		// wait for child to finish
		wait(NULL);

		// close write from proc 2
		close(pipe2[1]);

		// read from child
		char output[10];
		read(pipe2[0], output, 10);
		
		// close read from child
		close(pipe2[0]);
		time += clock();
		printf("time elapsed: %f\n", (double)time);
		printf("Output string: %s\n", output);
	} else { // child
		// close write from first pipe
		close(pipe1[1]);

		// read from proc 1
		char output[10];
		read(pipe1[0], output, 10);
		printf("Read from parent: %s\n", output);

		// close both reading ends
		close(pipe1[0]);
		close(pipe2[0]);
		// write to pipe 2
		write(pipe2[1], output, 10);
		// close write from pipe 2
		close(pipe2[1]);

		exit(0);
	}
}

// For this task, I use LMbench: a suite of portable benchmarks
// it compares different unix systems performance
// open source
//
//
// pipe() is unidirectional so use two pipes for bidirectional
// fork() returns one of three: 0, <0, or >0
