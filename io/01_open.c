#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

// #define ERR_EXIT(m) (perror(m), exit(EXIT_FAILURE))

#define ERR_EXIT(m) \
    do \
    { \
        perror(m); \
        exit(EXIT_FAILURE); \
    } while(0)

int main(int argc, char *argv[]) {
    int fd;
    fd = open("test.txt", O_RDONLY);
    if(-1 == fd) {
        fprintf(stderr, "open error with error = %d %s\n", errno, strerror(errno));
        //return EXIT_FAILURE;
    }

    if(-1 == fd) {
        //perror("open error");
        //return EXIT_FAILURE;
        ERR_EXIT("open error");
    }

    printf("open success\n");
    
    return EXIT_SUCCESS;
}
