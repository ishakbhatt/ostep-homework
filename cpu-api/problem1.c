#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//#include <sys/wait.h>

int main(int argc, char *argv[]){
	printf("hello world (pid: %d)\n", (int) getpid());
	int x;
	x = 100;
	int rc = fork();
	printf("val of x: %d\n", x);
	if (rc < 0) {
		// fork failed
		fprintf(stderr, "fork failed\n");
		exit(1);
	} else if (rc == 0){
		// child
		printf("hello, I am child (pid: %d)\n", (int) getpid());
	} else {
//		wait(NULL);
		// parent
		printf("hello, I am parent of %d (pid: %d)\n", rc, (int) getpid());
	}
}

/*
 * The program starts as one process at main. The hello world statement is first printed.
 * fork() is called and a copy of this program is created (a separate process) with its own
 * address space. The copy of the parent process is the child process that starts right after fork().
 * So, hello world is only printed once. The parent process finishes, then the child process finishes.
 * Because the processes do not share the same address space, they do not share the same variable x.
 * Therefore, modifications to x from one program does not affect x in the other process.
 *
 * When we use wait() in the parent process, the parent process waits for the child process to finish
 * before continuing through the program.
 * */
