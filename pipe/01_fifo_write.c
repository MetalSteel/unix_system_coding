#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    mkfifo("tp", 0644);
    int fd = open("main.c", O_RDONLY);
    int fifo_fd = open("tp", O_WRONLY);
    char buf[64] = {0};
    ssize_t sz = 0;
    while((sz = read(fd, buf, sizeof(buf))) > 0) {
        write(fifo_fd, buf, sizeof(buf));
    }
    close(fifo_fd);
    close(fd);

    return EXIT_SUCCESS;
}
