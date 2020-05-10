#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>

void handler(int signum) {
    printf("signum = %d\n", signum);
}

int main(int argc, char *argv[]) {
    signal(SIGALRM, handler);

    struct itimerval it;
    // 表示定时器的周期时间
    struct timeval tv_interval = {1, 0};
    // 表示定时器开始的时间
    struct timeval tv_value = {5, 0};
    it.it_interval = tv_interval;
    it.it_value = tv_value;
    setitimer(ITIMER_REAL, &it, NULL);

    while(1) {
        pause();
    }
    
    // 1. 重新设置setitimer的值都为0表示取消timer定时器
    // 2. 重新设置setitimer的时候, 第三个参数会返回剩余定时器的时间
    // 3. getitimer表示获取当前定时器还剩余多长时间

    return EXIT_SUCCESS;
}
