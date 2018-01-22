#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <fcntl.h>

int main(int argc, const char *argv[])
{
    char random_garbage[8192];
    int fd = -1;
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 0;
    }
    fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (fd < 0) {
        perror("Can't open file: ");
        return 0;
    }
    write(fd, random_garbage, 8192);
    lseek(fd, 5 * 4096, SEEK_CUR);
    write(fd, random_garbage, 8192);
    close(fd);
    return 0;
}