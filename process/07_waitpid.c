#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    pid_t pid = fork();

    if(pid > 0) {
        printf("this is parent process, pid = %d, child pid = %d\n", getpid(), pid);
        int child_status = 0;
        // wait for parent group any child process
        // pid_t pid = waitpid(0, &child_status, 0);
        
        // wait for any child process
        // pid_t pid = waitpid(-1, &child_status, 0);

        // wait for specify pid child process
        // options can be set 0 or WNOHANG, WNOHANG means is will not block and return is -1
        pid_t pid = waitpid(pid, &child_status, 0);
        
        // wait for -100 abs group any child process
        // pid_t pid = waitpid(-100, &child_status, 0);


        // normal exit
        if(WIFEXITED(child_status)) {
            printf("child process pid = %d, normal return status = %d\n", pid, WEXITSTATUS(child_status));
        }
        // signal exit
        else if(WIFSIGNALED(child_status)) {
            printf("child process pid = %d, signal exit status = %d\n", pid, WTERMSIG(child_status));
        }
        // stop exit
        else if(WIFSTOPPED(child_status)) {
            printf("child process pid = %d, stop status = %d\n", pid, WSTOPSIG(child_status));
        }
    }
    else if(pid == 0) {
        printf("this is child process, pid = %d, parent pid = %d\n", getpid(), getppid());
        // normal exit
        // exit(100);
        
        // signal exit
        abort();
    }
    else {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}
