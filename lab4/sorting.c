#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pthread.h>

int a[500], b[500];
int n;
pthread_t threads[2];

void * sort(void * idx){
	int x = *((int *)idx);

	if(x == 0){
		for(int i = 0; i < n/2; i++){
			for(int j = i + 1; j < n/2; j++){
				if(a[i] > a[j]){
					int temp = a[i];
					a[i] = a[j];
					a[j] = temp;
				}
			}
		}
		// for(int i = 0; i < n; i++) printf("%d ", a[i]);
		// printf("\n");
	}
	else if(x == 1){
		for(int i = n/2 + 1; i < n; i++){
			for(int j = i + 1; j < n; j++){
				if(a[i] > a[j]){
					int temp = a[i];
					a[i] = a[j];
					a[j] = temp;
				}
			}
		}
		// for(int i = 0; i < n; i++) printf("%d ", a[i]);
		// printf("\n");
	}
}

void * merge(void * idx){
	for(int i = 0; i < n; i++){
		for(int j = i + 1; j < n; j++){
			if(a[i] > a[j]){
					int temp = a[i];
					a[i] = a[j];
					a[j] = temp;
			}
		}
	}
	for(int i = 0; i < n; i++) b[i] = a[i];
}

int main(){

	printf("Enter size of array\n");
	scanf("%d", &n);

	printf("Enter %d numbers\n", n);
	for(int i = 0; i < n; i++) scanf("%d", &a[i]);

	// for(int i = 0; i < n; i++) printf("%d ", a[i]);

	for(int i = 0; i < 2; i++){
		int *arg = malloc(sizeof(*arg));
		*arg = i;
		int check = pthread_create(&threads[i], NULL, sort, arg);
		if(check){
			perror("Error in creating threads");
			exit(EXIT_FAILURE);
		}
	}

	for(int i = 0; i < 2; i++) pthread_join(threads[i], NULL);

	pthread_t thread3;
	int check = pthread_create(&thread3, NULL, merge, NULL);
	if(check){
		perror("error");
		exit(EXIT_FAILURE);
	}
	pthread_join(thread3, NULL);

	for(int i = 0; i < n; i++) printf("%d ", b[i]);
	printf("\n");


	return 0;
}