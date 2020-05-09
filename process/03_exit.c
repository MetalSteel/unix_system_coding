#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void func1() {
    printf("func1...");
}

void func2() {
    printf("func2...");
}

int main(int argc, char *argv[]) {
    printf("hello,world");
    // _exit is system call, it can't flush io buffer and hook function
    //_exit(0);

    // exit is c library, it can flush io buffer
    // exit also can register hook function by atexit, exec reverse sequence
    // first exec func2 then exec func1
    atexit(func1);
    atexit(func2);
    
    exit(0);
}
