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
    alarm(2);
}

int main(int argc, char *argv[]) {
    signal(SIGALRM, handler);
    
    printf("ready exec alarm(2)\n");
    alarm(2);
    while(1);

    return EXIT_SUCCESS;
}
