#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int fd1 = open("test.txt", O_RDONLY);

    int fd2 = open("test.txt", O_RDWR);

    char buf1[1024] = {0};
    char buf2[1024] = {0};

    read(fd1, buf1, 5);
    printf("%s\n", buf1);

    read(fd2, buf2, 5);
    printf("%s\n", buf2);

    write(fd2, "hello", 5);

    memset(buf1, 0, sizeof(buf1));
    read(fd1, buf1, 5);
    printf("%s\n", buf1);

    close(fd1);
    close(fd2);
    
    return EXIT_SUCCESS;
}
