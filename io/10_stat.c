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

#define MAJOR(m) (int)((unsigned short)m >> 8)
#define MINOR(m) (int)((unsigned short)m & 0x00FF)

void file_type(struct stat *st_ptr);
void file_permission(struct stat *st_ptr);

int main(int argc, char *argv[]) {
    if(argc != 2) {
        fprintf(stderr, "Usage: %s filename\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    struct stat st;
    int ret = lstat(argv[1], &st);
    if(ret == -1) {
        ERR_EXIT("stat failed");
    }

    printf("file device marjor: %d minjor: %d\n", MAJOR(st.st_dev), MINOR(st.st_dev));
    
    printf("file inode number: %ld\n", st.st_ino);

    file_type(&st);
    file_permission(&st);
    
    return EXIT_SUCCESS;
}

void file_type(struct stat *st_ptr) {
    printf("file type: ");

    switch(st_ptr->st_mode & S_IFMT) {
    case S_IFBLK:  printf("block device\n");     break;
    case S_IFCHR:  printf("character device\n"); break;
    case S_IFDIR:  printf("directory\n");        break;
    case S_IFIFO:  printf("FIFO/pipe\n");        break;
    case S_IFLNK:  printf("symlink\n");          break;
    case S_IFREG:  printf("regular file\n");     break;
    case S_IFSOCK: printf("socket\n");           break;
    default: printf("unknown?\n");               break;
    }
}

void file_permission(struct stat *st_ptr) {
    char perm[] = "----------";

    switch(st_ptr->st_mode & S_IFMT) {
    case S_IFBLK:  perm[0] = 'b';     break;
    case S_IFCHR:  perm[0] = 'c';     break;
    case S_IFDIR:  perm[0] = 'd';     break;
    case S_IFIFO:  perm[0] = 'p';     break;
    case S_IFLNK:  perm[0] = 'l';     break;
    case S_IFREG:  perm[0] = '-';     break;
    case S_IFSOCK: perm[0] = 's';     break;
    }
    
    if(st_ptr->st_mode & S_IRUSR)
        perm[1] = 'r';
    if(st_ptr->st_mode & S_IWUSR)
        perm[2] = 'w';
    if(st_ptr->st_mode & S_IXUSR)
        perm[3] = 'x';
    if(st_ptr->st_mode & S_IRGRP)
        perm[4] = 'r';
    if(st_ptr->st_mode & S_IWGRP)
        perm[5] = 'w';
    if(st_ptr->st_mode & S_IXGRP)
        perm[6] = 'x';
    if(st_ptr->st_mode & S_IROTH)
        perm[7] = 'r';
    if(st_ptr->st_mode & S_IWOTH)
        perm[8] = 'w';
    if(st_ptr->st_mode & S_IXOTH)
        perm[9] = 'x';

    printf("%s\n", perm);
}
