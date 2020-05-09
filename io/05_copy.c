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
    if(argc != 3) {
        fprintf(stderr, "Usage %s src dest\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int src_fd;
    src_fd = open(argv[1], O_RDONLY);

    if(-1 == src_fd) {
        ERR_EXIT("open src error");
    }
    
    int dst_fd;
    dst_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if(-1 == dst_fd) {
        close(src_fd);
        ERR_EXIT("open dst error");
    }

    char buf[1024] = {0};
    ssize_t read_sz = 0;
    while((read_sz = read(src_fd, buf, sizeof(buf))) > 0) {
        fprintf(stdout, "read %ld byte\n", read_sz);
        ssize_t write_sz = write(dst_fd, buf, read_sz);     
        fprintf(stdout, "write %ld byte\n", write_sz);
    }

    close(src_fd);
    close(dst_fd);
    
    return EXIT_SUCCESS;
}
