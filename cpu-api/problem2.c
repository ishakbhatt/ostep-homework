#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
	open("./p2.output", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
	int rc = fork();
	if(rc > 0) {
		printf("hello, I am parent of child %d (pid: %d)\n", rc, (int) getpid());
	} else if(rc == 0){
		printf("hello, I am child (pid: %d)\n", (int) getpid());
	} else {
		fprintf(stderr, "cannot exec fork()");
	}
}

/*
 * They can both access the file descriptor returned by open().
 * When they are both writing to the file concurrently,
 * it is indeterministic which process will overwrite the file at the end
 * unless we use wait().
 * */
