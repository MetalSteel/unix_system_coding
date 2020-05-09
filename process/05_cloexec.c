#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    // set fd FD_CLOEXEC, while execve exec, the STDOUT_FILENO will be close, so
    // main application not printf
    fcntl(STDOUT_FILENO, F_SETFD, FD_CLOEXEC);
    
    // application argv 
    char *child_argv[] = {"./main", "wang", "gang", NULL};
    // application environ
    char *child_env[] = {"key = val", "key1 = val1", NULL};
    // exec application
    execve("./main", child_argv, child_env);

    return EXIT_SUCCESS;
}
