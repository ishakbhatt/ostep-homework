#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
	int rc = fork();
	
	if(rc == 0){ // child
		printf("CHILD\n");
		//char * const args[] = {"ls", NULL};
		char * const envp[] = {NULL}; // environment var
		execle("/bin/ls", "ls", NULL, envp);
	} else if(rc > 0){ // parent
		printf("PARENT\n");
		wait(NULL);
	} else { // fork error
		fprintf(stderr, "fork() error");
	}
}

/*
 *exec function family replaces current running process with new process.
 run a C program by using another C program. allows process to run any program files including binary or shell.
 under header file unistd.h
execvp: child proc doesn't have to run the same program as parent process. takes file name and null terminated array of char ptrs
execv: takes path to file name and args
execlp: file name and list of args
execvpe: file name, args, environment
 *
 * */
