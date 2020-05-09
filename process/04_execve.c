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
        sleep(1);
    }
    else if(pid == 0) {
        // application argv 
        char *child_argv[] = {"./main", "wang", "gang", NULL};
        // application environ
        char *child_env[] = {"key = val", "key1 = val1", NULL};
        // exec application
        execve("./main", child_argv, child_env);
        // will not exec, becase it's replace
        printf("this is child process, pid = %d, parent pid = %d\n", getpid(), getppid());
    }
    else {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}
