#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int fd = open("main_tmp.c", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    int fifo_fd = open("tp", O_RDONLY);
    char buf[64] = {0};
    ssize_t sz = 0;
    while((sz = read(fifo_fd, buf, sizeof(buf))) > 0) {
        write(fd, buf, sizeof(buf));
    }
    close(fd);
    close(fifo_fd);
    unlink("tp");

    return EXIT_SUCCESS;
}
