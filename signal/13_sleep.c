#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>

void handler(int signum) {
    printf("signum = %d\n", signum);
}

int main(int argc, char *argv[]) {
    
    signal(SIGINT, handler);

    // sleep will interrput by signal
    //int n = sleep(10);
    //printf("n remain %d s\n", n);

    // right method to sleep
    int n = 10;
    while(n = sleep(n));

    // usleep 1s = 1000ms = 1000000us

    return EXIT_SUCCESS;
}
