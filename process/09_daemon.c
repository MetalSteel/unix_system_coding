#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void setup_daemon() {
    pid_t pid = fork();

    if(pid > 0) {
        exit(EXIT_SUCCESS);
    }
    else if(pid == 0) {
        // create new session
        // setsid can't is the process group leader and this process is group leader
        pid_t sid = setsid();

        // change root dir
        chdir("/");

        // close stdin stdout stderr
        int fd = open("/dev/null", O_RDWR);
        dup2(fd, STDIN_FILENO);
        dup2(fd, STDOUT_FILENO);
        dup2(fd, STDERR_FILENO);
        close(fd);

        while(1)
            printf("hello, daemon\n");

    }
    else {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }
}


int main(int argc, char *argv[]) {
    
    // setup_daemon();
    // c stanrd library daemon function
    // first param: change to root dir
    // second param: close stdin/stdout/stderr
    daemon(0, 1);
    while(1) {
        sleep(1);
        printf("hello, daemon\n");
    }

    return EXIT_SUCCESS;
}
