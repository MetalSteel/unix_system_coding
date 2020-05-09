#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int fd = open("test2.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
    if(fd == -1) {
        perror("open test2.txt failed");
        exit(EXIT_FAILURE);
    }

    struct flock file_lock;
    memset(&file_lock, 0, sizeof(file_lock));
    file_lock.l_type = F_WRLCK;
    file_lock.l_whence = SEEK_SET;
    file_lock.l_start = 0;
    file_lock.l_len = 0; // whole file lock
    
    // normal file lock
    //int ret = fcntl(fd, F_SETLK, &file_lock);
    // wait file lock will block until block release
    int ret = fcntl(fd, F_SETLKW, &file_lock);
    if(ret == 0) {
        printf("lock success\n");
        printf("press any key to unlock\n");
        // release file lock
        getchar();

        file_lock.l_type = F_UNLCK;
        ret = fcntl(fd, F_SETLK, &file_lock);
        if(ret == 0) {
            printf("unlock success\n");
        }
        else {
            perror("unlock failed");
            exit(EXIT_FAILURE);
        }
    }
    else {
        perror("lock failed");
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}
