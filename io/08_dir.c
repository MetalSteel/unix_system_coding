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
    DIR *dir = opendir(".");
    struct dirent *dir_item = NULL;
    while((dir_item = readdir(dir)) != NULL) {
        printf("%s\n", dir_item->d_name);
    }

    closedir(dir);
    
    return EXIT_SUCCESS;
}
