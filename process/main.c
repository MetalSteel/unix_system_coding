#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char **environ;

int main(int argc, char *argv[]) {
    printf("hello, i am main app\n");
    printf("pid = %d\n", getpid());
    for(int i = 0; i < argc; ++i) {
        printf("%s\n", argv[i]);
    }
    printf("------------------------------\n");
    while(*environ != NULL) {
        printf("%s\n", *environ);
        ++environ;
    }

    return EXIT_SUCCESS;
}
