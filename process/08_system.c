#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

void my_system(const char *cmd) {
    pid_t pid = fork();

    if(pid > 0) {
        int status = 0;
        while(waitpid(pid, &status, 0) < 0) {
            if(errno == EINTR) {
                continue;
            }
            break;
        }
    }
    else if(pid == 0) {
        execl("/bin/sh", "sh", "-c", cmd, NULL);
    }
    else {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }

}

int main(int argc, char *argv[]) {
    // this function exec by fork -> execve -> waitpid
    // system("ls -l");
    my_system("ls -l");

    return EXIT_SUCCESS;
}
