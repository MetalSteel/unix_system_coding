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
    sleep(2);
}

int main(int argc, char *argv[]) {

    signal(SIGINT, handler);
    signal(SIGQUIT, handler);

    while(1) {
        // pause while return until signal handler exec complete
        pause();
        printf("pause return\n");
    }

    return EXIT_SUCCESS;
}
