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
    umask(0);
    fd = open("test.txt", O_RDONLY | O_CREAT, 0666);

    if(-1 == fd) {
        ERR_EXIT("open error");
    }

    printf("open success\n");
    close(fd);
    
    return EXIT_SUCCESS;
}
