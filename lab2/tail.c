#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>


#define MAXLEN 1024

int nread;
char str2[MAXLEN];
char *stroki[MAXLEN];
char data[MAXLEN];
struct stat file_stat;
int fd1, fd2;
clock_t begin, end;


void close_all(){
	close(fd1);
	close(fd2);
}

int main(int argc, char ** argv){


	if(argc > 4 || argc < 4){
		perror("Illegal number of args");
		return 0;
	}

	char *argN = argv[1];
	int lines = atoi(argN);
	printf("%d\n", lines);
	char * arg1 = argv[2];
	char * arg2 = argv[3];

	if(strcmp(arg1, arg2) == 0){
		printf("%s\n", "Cannot copy file over itself");
		return 0;
	}

	fd1 = open(arg1, O_RDONLY);

	if(fd1 == -1){
		perror("Error in opening first file");
		close_all();
		return 0;
	}

	fd2 = open(arg2, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IWOTH | S_IXOTH);

	if(fd2 == -1){
		perror("Error in opening second file");
		close_all();
		return 0;
	}

	int res;
	begin = clock();
	if(lseek(fd1, -1 * lines, SEEK_END) < 0){
		perror("Error while moving the pointer");
		close_all();
		return 0;
	}

	while(res = read(fd1, &data, MAXLEN)){
		if(res == -1){
			perror("Error while reading from file");
			close_all();
			return 0;
		}
		// printf("%d\n", res);
		int resW = write(fd2, &data, res);
		if(resW == -1){
			perror("Error while writing to file");
			close_all();
			return 0;
		}
	}
	end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("%s %lf\n", "Copy finished", time_spent);
	close_all();

	return 0;
}