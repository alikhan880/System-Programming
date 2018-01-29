#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>
int main()
{
    pid_t id;
    int sz;
    char * stroki[1000];
    char *buffer;
    size_t bufsize = 32;
    while (1) {
        sz = 0;

        buffer = (char *)malloc(bufsize * sizeof(char));
        getline(&buffer, &bufsize, stdin);

        // printf("%s\n", "1");
        char * token = strtok(buffer, " ");
        // printf("%s\n", token);
        while(token != NULL){
            if(strcmp(token, " ") != 0) stroki[sz++] = token;
            token = strtok(NULL, " ");
        }
        // printf("%s\n", "2");

        for(int i = 0; i < sz; i++) printf("%s\n", stroki[i]);
        id = fork();
        int status;
        if (id == 0){
            if(execvp(*stroki, stroki) < 0){
                perror("Failed");
            }
        }
        if(id < 0){
            perror("Error");
        }
        else{
            while(wait(&status) != id){}
        }
    }
    return 0;
}