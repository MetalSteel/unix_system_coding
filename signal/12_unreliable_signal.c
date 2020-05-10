#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Student {
    int no;
    char name[8];
    double weight;
    int height;
}Student;

void handler(int signum, siginfo_t *info, void *ctx);

int main(int argc, char *argv[]) {
    struct sigaction act;
    act.sa_sigaction = handler;
    sigemptyset(&act.sa_mask);
    sigaddset(&act.sa_mask, SIGUSR1);
    sigprocmask(SIG_BLOCK, &act.sa_mask, NULL);
    act.sa_flags = SA_SIGINFO;

    int ret = sigaction(SIGUSR1, &act, NULL);
    if(ret == -1) {
        perror("sigaction failed");
        exit(EXIT_FAILURE);
    }

    // circle send 5 un-reliable signal
    for(int i = 0; i < 5; ++i) {
        Student *student = (Student*)malloc(sizeof(Student));
        student->no = i + 1;
        strcpy(student->name, "metal");
        student->weight = 65.0;
        student->height = 180;

        printf("prepare send Student(%d, %s, %f, %d)\n", \
                student->no, student->name, student->weight, student->height);

        union sigval val;
        val.sival_ptr = student;
   
        ret = sigqueue(getpid(), SIGUSR1, val);
        if(ret == -1) {
            perror("sigqueue failed");
            exit(EXIT_FAILURE);
        }
    }

    sleep(3);
    
    // unblock
    sigset_t uset;
    sigemptyset(&uset);
    sigaddset(&uset, SIGUSR1);
    sigprocmask(SIG_UNBLOCK, &uset, NULL);

    printf("unblock SIGRTMIN\n");

    while(1);

    return EXIT_SUCCESS;
}

void handler(int signum, siginfo_t *info, void *ctx) {
    sleep(2);
    Student *student = (Student*)info->si_ptr;
    printf("recv signum = %d, data = (%d, %s, %f, %d)\n", signum, \
            student->no, student->name, student->weight, student->height);
    free(student);
}
