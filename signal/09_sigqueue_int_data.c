#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>

void handler(int signum, siginfo_t *info, void *ctx);

int main(int argc, char *argv[]) {
    pid_t pid = fork();
    signal(SIGCHLD, SIG_IGN);

    if(pid > 0) {
        printf("parent process ready SIGUSR1 and data is 986\n");
        sleep(2);

        union sigval val;
        val.sival_int = 986;
        int ret = sigqueue(pid, SIGUSR1, val);
        if(ret == -1) {
            perror("sigqueue failed");
            exit(EXIT_FAILURE);
        }

        while(1);
    } 
    else if(pid == 0) {
        printf("child process ready read data from parent process\n");

        struct sigaction act;
        act.sa_sigaction = handler;
        sigemptyset(&act.sa_mask);
        act.sa_flags = SA_SIGINFO;

        int ret = sigaction(SIGUSR1, &act, NULL);
        if(ret == -1) {
            perror("sigaction failed");
            exit(EXIT_FAILURE);
        }

        while(1);
    }
    else {
        printf("fork failed\n");
    }

    return EXIT_SUCCESS;
}

void handler(int signum, siginfo_t *info, void *ctx) {
    printf("recv signum = %d, data = %d\n", signum, info->si_int);
}
