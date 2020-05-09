#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int fd1 = open("test1.txt", O_WRONLY | O_CREAT, 0644);

    //close(STDOUT_FILENO);
    //dup(fd1);
    
    dup2(fd1, STDOUT_FILENO);

    printf("hello, world!!!\n");

    close(fd1);
    
    return EXIT_SUCCESS;
}
