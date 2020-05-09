#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void set_flag(int fd, int flag) {
    int flags = fcntl(fd, F_GETFL, 0);
    if(flags == -1) {
        perror("F_GETFL failed");
        exit(EXIT_FAILURE);
    }
    
    flags |= flag;

    fcntl(fd, F_SETFL, flags);
}

void clr_flag(int fd, int flag) {
    int flags = fcntl(fd, F_GETFL, 0);
    if(flags == -1) {
        perror("F_GETFL failed");
        exit(EXIT_FAILURE);
    }

    flags &= ~flag;
    fcntl(fd, F_SETFL, flags);
}

int main(int argc, char *argv[]) {
    // fcntl dup fd function
    // ===================================================
    int fd1 = open("test1.txt", O_WRONLY | O_CREAT, 0644);
    
    // from 10 to dup fd
    int new_fd = fcntl(fd1, F_DUPFD, 10);
    printf("fd1 dup is %d\n", new_fd);

    close(fd1);
    
    // ==================================================

    // fcntl set file status
    char buf[1024] = {0};
    printf("ready to read from stdin\n");
    //int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    //fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);
    set_flag(STDIN_FILENO, O_NONBLOCK);
    clr_flag(STDIN_FILENO, O_NONBLOCK);
    ssize_t sz = read(STDIN_FILENO, buf, sizeof(buf));
    if(sz == -1) {
        perror("read failed");
    }
    
    printf("read from stdin %ld byte\n", sz);
    printf("%s\n", buf);

    return EXIT_SUCCESS;
}
