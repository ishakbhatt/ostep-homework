#include <time.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]){
	long long time;
	time = -clock();
	read(0, NULL, 0);
	time += clock();
	printf("Total time: %f\n", (double)time);
	return(0);
}
