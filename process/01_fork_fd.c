#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int fd = open("test.txt", O_RDWR);

    pid_t pid = fork();

    if(pid > 0) {
        printf("this is parent process, pid = %d, child pid = %d\n", getpid(), pid);
        write(fd, "world", 5);
        sleep(1);
    }
    else if(pid == 0) {
        printf("this is child process, pid = %d, parent pid = %d\n", getpid(), getppid());
        write(fd, "hello", 5);
    }
    else {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}
