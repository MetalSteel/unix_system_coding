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
    // exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[]) {
    __sighandler_t old_handler;

    old_handler = signal(SIGINT, handler);

    while(getchar() != '\n');
    
    // re-register old_handler(default is term)
    signal(SIGINT, old_handler);

    while(1);

    printf("app exit...\n");

    return EXIT_SUCCESS;
}
