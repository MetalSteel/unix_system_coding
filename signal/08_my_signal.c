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
}

__sighandler_t my_signal(int sig, __sighandler_t handler) {
    struct sigaction act;
    struct sigaction old_act;

    act.sa_handler = handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;

    sigaction(sig, &act, &old_act);

    return old_act.sa_handler;
}

int main(int argc, char *argv[]) {
    __sighandler_t old_handler;
    old_handler = my_signal(SIGINT, handler);
    
    int n = 5;
    do {
        n = sleep(n);
        printf("remain %d s\n", n);
    } while(n > 0);

    my_signal(SIGINT, old_handler);
    
    return EXIT_SUCCESS;
}
