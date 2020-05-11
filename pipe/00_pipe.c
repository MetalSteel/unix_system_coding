#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int pipe_fd[2];
    // pipe fd[0] read / fd[1] write
    if(pipe(pipe_fd) == -1) {
        perror("pipe failed");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();

    if(pid == 0) {
        close(pipe_fd[0]);
        write(pipe_fd[1], "hello", 5);
        close(pipe_fd[1]);
        exit(EXIT_SUCCESS);
    }

    close(pipe_fd[1]);
    char buf[5] = {0};
    read(pipe_fd[0], buf, sizeof(buf));
    close(pipe_fd[0]);

    printf("%s\n", buf);

    return EXIT_SUCCESS;
}
