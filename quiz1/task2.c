#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>


#define MAXLEN 1024

int nread;
char str2[MAXLEN];
char *stroki[MAXLEN];
char data[MAXLEN];
int fd1, fd2;

void close_all(){
	if(close(fd1) == -1){
		if(errno == EINTR){
			perror("System call was interrupted");	

		}
		else{
			perror("Error in closing file");
		}
	}
	if(close(fd2)){
		if(errno == EINTR){
			perror("System call was interrupted");	
		}		
		else{
			perror("Error in closing file");
		}
	}

}


int main(int argc, char ** argv){


	if(argc > 3 || argc < 3){
		perror("Illegal number of args");
		return 0;
	}

	char * arg1 = argv[1];
	char * arg2 = argv[2];

	if(strcmp(arg1, arg2) == 0){
		perror("Cannot copy file over itself");
		return 0;
	}

	fd1 = open(arg1, O_RDONLY);
	
	if(fd1 == -1){
		if(errno == EINTR){
			perror("System call was interrupted");
		}
		else{
			perror("Error in opening first file");
		}
		close_all();
		return 0;
	}


	fd2 = open(arg2, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IWOTH | S_IXOTH);

	if(fd2 == -1){
		if(errno == EINTR){
			perror("System call was interrupted");	
		}
		else{
			perror("Error in opening second file");

		}
		close_all();
		return 0;
	}

	int res;
	while(res = read(fd1, &data, MAXLEN)){
		if(res == -1){
			if(errno == EINTR){
				perror("System call was interrupted");

			}
			else
				perror("Error while reading from file");
			close_all();
			return 0;
		}
		int resW = write(fd2, &data, res);
		if(resW == -1){
			if(errno == EINTR)
				perror("System call was interrupted");
			else
				perror("Error while writing to file");
			close_all();
			return 0;
		}
	}
	printf("%s\n", "Copy finished");
	close_all();

	return 0;
}