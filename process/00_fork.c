#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    pid_t pid = fork();

    if(pid > 0) {
        printf("this is parent process, pid = %d, child pid = %d\n", getpid(), pid);
    }
    else if(pid == 0) {
        printf("this is child process, pid = %d, parent pid = %d\n", getpid(), getppid());
    }
    else {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}
