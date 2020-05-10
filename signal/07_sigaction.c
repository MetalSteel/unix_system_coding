#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>

void handler(int signum) {
    printf("recv %d signal\n", signum);
    sleep(10);
    printf("exec complete\n");
}

int main(int argc, char *argv[]) {
    struct sigaction act;

    act.sa_handler = handler;

    sigemptyset(&act.sa_mask);
    // while handler exec, SIGQUIT can't interrupt handler exec
    sigaddset(&act.sa_mask, SIGQUIT);

    act.sa_flags = 0;

    sigaction(SIGINT, &act, NULL);

    while(1);

    
    return EXIT_SUCCESS;
}
