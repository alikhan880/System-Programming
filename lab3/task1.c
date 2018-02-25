#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>



int main(){

	pid_t id = fork();


	if(id == 0){
		for(int i = 0; i < 100; i++) printf("Number: %d Parent pid: %d My pid: %d\n", i, getppid(), getpid());
	}
	else if(id != -1){
		for(int i = 0; i < 5; i++) printf("Number: %d Child pid: %d My pid: %d\n", i, id ,getpid());
	}



	return 0;
}