#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pthread.h>



int board[100][100];
int rows = 9;
int cols = 9;
FILE * fd;
char * line;
size_t len = 0;
ssize_t readNum;
int check_board[18];
pthread_t threadsArray[18];

void *check_function(void* idx){
	int x = *((int*)idx);

	if(x >= 0 && x <= 8){
		int check[10];
		for(int i = 0; i < 10; i++) check[i] = 0;
		for(int j = 0; j < 9; j++){
			int k = board[x][j];
			check[k]++;
			// printf("Checking row %d column %d and answer is %d\n", x, j, k);
		}
		int ans = 1;
		for(int i = 1; i < 10; i++){
			if(check[i] == 1) continue;
			ans = 0;
			break;
		}

		if(ans == 1) check_board[x] = 1;
		else check_board[x] = -1;
		// printf("Result of check of row %d is %d\n", x, check_board[x]);

	}
	else if(x >= 9 && x <= 17){
		int check[10];
		for(int i = 0; i < 10; i++) check[i] = 0;
		for(int j = 0; j < 9; j++){
			int k = board[j][x - 9];
			check[k]++;
			// printf("Checking row %d column %d and answer is %d\n", x, j, k);
		}
		int ans = 1;
		for(int i = 1; i < 10; i++){
			if(check[i] == 1) continue;
			ans = 0;
			break;
		}

		if(ans == 1) check_board[x] = 1;
		else check_board[x] = -1;
		// printf("Result of check of column %d is %d\n", x - 9, check_board[x]);
	}
}

int main(){


	for(int i = 0; i < 18; i++) check_board[i] = 0;

	fd = fopen("test.txt", "r");

	if(fd == NULL){
		exit(EXIT_FAILURE);
		return 0;
	}

	// printf("%d\n", fd);
	int curRow = 0;
	while((readNum = getline(&line, &len, fd)) != -1){
		for(int i = 0; i < strlen(line); i++){
			int num = line[i] - '0';
			board[curRow][i] = num;
		}
		curRow++;
	}


	for(int i = 0; i < rows; i++){
		for(int j = 0; j < cols; j++){
			printf("%d ", board[i][j]);
		}
		printf("\n");
	}

	fclose(fd);

	for(int i = 0; i < 18; i++){
		int *arg = malloc(sizeof(*arg));
		*arg = i;
		int check_bit = pthread_create(&threadsArray[i], NULL, check_function, arg);
		if(check_bit){
			exit(EXIT_FAILURE);
		}
	}

	for(int i = 0; i < 18; i++){
		pthread_join(threadsArray[i], NULL);
	}
	// for(int i = 0; i < 18; i++) printf("%d ", check_board[i]);
	for(int i = 0; i < 18; i++){
		if(check_board[i] == -1){
			printf("NO\n");
			return 0;
		}
		else if(check_board[i] == 0){
			printf("%s\n", "Some field not checked");
			return 0;
		}
	}

	printf("YES\n");

	exit(EXIT_SUCCESS);		

	return 0;
}