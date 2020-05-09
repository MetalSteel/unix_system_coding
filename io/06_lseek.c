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
    fd = open("test.txt", O_RDONLY);

    if(-1 == fd) {
        ERR_EXIT("open test.txt error");
    }
    
    char buf[1024] = {0};
    read(fd, buf, sizeof(buf));

    ssize_t sz = lseek(fd, 0, SEEK_CUR);
    printf("%ld offset\n", sz);

    close(fd);
    
    return EXIT_SUCCESS;
}
