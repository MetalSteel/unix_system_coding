#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define ERR_EXIT(m) \
    do \
    { \
        perror(m); \
        exit(EXIT_FAILURE); \
    } while(0)

int main(int argc, char *argv[]) {
    DIR *dir = opendir("./tmp");
    if(dir == NULL) {
        perror("open ./tmp failed");
    }
    closedir(dir);

    int ret = mkdir("./tmp", 0644);
    if(ret == -1) {
        ERR_EXIT("mkdir ./tmp failed");
    }
    
    return EXIT_SUCCESS;
}
