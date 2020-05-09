#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define ERR_EXIT(m) \
    do \
    { \
        perror(m); \
        exit(EXIT_FAILURE); \
    } while(0)

int main(int argc, char *argv[]) {
    int fd;
    fd = open("hole.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if(-1 == fd) {
        ERR_EXIT("open hole.txt error");
    }
    
    write(fd, "ABCDE", 5);

    ssize_t offset = lseek(fd, 0, SEEK_CUR);
    printf("%ld offset\n", offset);

    offset = lseek(fd, 1024*1024*10, SEEK_CUR);
    printf("%ld offset\n", offset);

    write(fd, "HELLO", 5);
    
    close(fd);
    
    return EXIT_SUCCESS;
}
