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
		wait(NULL);
		printf("child\n");
	} else {
		// parent
		//wait(NULL);
		printf("parent\n");
	}
}

// The program that has wait() will execute after the other process finishes.
