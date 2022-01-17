#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#define BUFSIZE 32

int main(int argc, char *argv[]){
	int num_children = 2;
	int pid;

	// set up pipe
	char buff[BUFSIZE];
	int p[2];
	
	if(pipe(p) < 0){
		exit(1);
	}

	for(int i = 0; i < num_children; ++i){
		pid = fork();
		if(pid > 0){
			printf("parent (pid: %d)\n", (int) getpid());
		} else if(pid == 0){
			if(i == 0){
				printf("child 1\n");
				close(p[0]);
				dup2(p[1], 1);
				printf("goes to the pipe\n");
			} else {
				printf("child 2\n");
				close(p[1]);
				dup2(p[0], 0);
				char buff[512];
				read(STDIN_FILENO, buff, 512);
				printf("buffer: %s", buff);
			}
			printf("child (pid: %d)\n", (int) getpid());
		} else{
			fprintf(stderr, "fork() #%d error", i+1);
			exit(1);
		}
	}
}

