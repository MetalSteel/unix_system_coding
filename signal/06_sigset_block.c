#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>

void handler(int signum) {
    if(signum != SIGQUIT) {
        printf("recv %d signal\n", signum);
    }
    else {
        sigset_t uset;
        sigemptyset(&uset);
        sigaddset(&uset, SIGINT);
        sigprocmask(SIG_UNBLOCK, &uset, NULL);
    }
}

void print_pending_sigset(sigset_t *sigset) {
    for(int i = 1; i < NSIG; ++i) {
        if(sigismember(sigset, i)) {
            putchar('1');
        }
        else {
            putchar('0');
        }
    }
    printf("\n");
}

int main(int argc, char *argv[]) {

    // sigset block, block SIGINT signal
    sigset_t bset;
    sigemptyset(&bset);
    sigaddset(&bset, SIGINT);
    sigprocmask(SIG_BLOCK, &bset, NULL);
    
    // register signal
    signal(SIGINT, handler);
    // ctrl+\ unblock SIGINT signal
    signal(SIGQUIT, handler);

    // get pending sigset
    sigset_t pset;
    for(;;) {
        sigpending(&pset);
        print_pending_sigset(&pset);
        sleep(1);
    }

    return EXIT_SUCCESS;
}
