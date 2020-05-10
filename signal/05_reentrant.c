#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>

typedef struct TEST {
    int a;
    int b;
}test;

test g_val;

void handler(int signum) {
    // it's not safe because is static variable
    printf("a = %d, b = %d\n", g_val.a, g_val.b);
    alarm(1);
}

int main(int argc, char *argv[]) {
    test zero = {0, 0};
    test one = {1, 1};

    signal(SIGALRM, handler);
    
    printf("ready exec alarm(2)\n");
    
    g_val = zero;
    alarm(1);

    while(1) {
        g_val = zero;
        g_val = one;
    }

    return EXIT_SUCCESS;
}
