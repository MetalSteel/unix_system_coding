#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <time.h>

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
        if((strcmp(dir_item->d_name, ".") == 0) || (strcmp(dir_item->d_name, "..") == 0)) {
            continue;
        }

        struct stat st;
        int ret = lstat(dir_item->d_name, &st);
        if(ret == -1) {
            ERR_EXIT("stat failed");
        }
        
        char perm[11] = "----------";
        
        // file type
        switch(st.st_mode & S_IFMT) {
        case S_IFBLK:  perm[0] = 'b';     break;
        case S_IFCHR:  perm[0] = 'c';     break;
        case S_IFDIR:  perm[0] = 'd';     break;
        case S_IFIFO:  perm[0] = 'p';     break;
        case S_IFLNK:  perm[0] = 'l';     break;
        case S_IFREG:  perm[0] = '-';     break;
        case S_IFSOCK: perm[0] = 's';     break;
        }
        
        // file permission
        if(st.st_mode & S_IRUSR)
            perm[1] = 'r';
        if(st.st_mode & S_IWUSR)
            perm[2] = 'w';
        if(st.st_mode & S_IXUSR)
            perm[3] = 'x';
        if(st.st_mode & S_IRGRP)
            perm[4] = 'r';
        if(st.st_mode & S_IWGRP)
            perm[5] = 'w';
        if(st.st_mode & S_IXGRP)
            perm[6] = 'x';
        if(st.st_mode & S_IROTH)
            perm[7] = 'r';
        if(st.st_mode & S_IWOTH)
            perm[8] = 'w';
        if(st.st_mode & S_IXOTH)
            perm[9] = 'x';

        // hard link number
        int hard_link_num = st.st_nlink;
        
        // user name
        struct passwd *pw = getpwuid(getuid());
        
        // group name
        struct group *gr = getgrgid(getgid());

        // file size
        long file_sz = st.st_size;
        
        // file modify time
        struct tm *loc_tm = localtime(&st.st_mtime);
        char time_buf[32] = {0};
        strftime(time_buf, sizeof(time_buf), "%Y-%m-%d %H:%M:%S", loc_tm);
        
        // file name
        char file_name[64] = {0};
        strcpy(file_name, dir_item->d_name);
        if(perm[0] == 'l') {
            char link_file_name[64] = {0};
            readlink(file_name, link_file_name, sizeof(link_file_name));
            strcat(file_name, " -> ");
            strcat(file_name, link_file_name);
        }

        printf("%s %d %s %s %10ld %s %s\n", perm, hard_link_num, pw->pw_name, gr->gr_name, file_sz, time_buf, file_name);
    }
    
    closedir(dir);

    return EXIT_SUCCESS;
}
