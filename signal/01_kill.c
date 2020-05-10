#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>

int count = 0;

void handler(int signum) {
    printf("recv %d signal\n", signum);
    if(count++ == 10) {
        exit(EXIT_SUCCESS);
    }
}

int main(int argc, char *argv[]) {

    signal(SIGUSR1, handler);

    while(1) {
        // pid > 0: send signal to specify pid
        // pid = 0: send this process group all process
        // pid = -1: send all process(has authority) except 0 and this
        // pid < -1: pid abs process group
        kill(getpid(), SIGUSR1);
        sleep(1);
    }

    return EXIT_SUCCESS;
}
