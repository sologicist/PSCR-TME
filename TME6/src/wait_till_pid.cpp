#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

pid_t wait_till_pid(pid_t pid) {
    while (1) {
        pid_t p = wait(nullptr);
        if ( p == pid ) {
            return p;
        }
    }
}


int wait_till_pid_sec (pid_t pid, int sec){
    bool finito;
    signal(SIGALRM,[](){ finito = true;})
    alarm(sec);

    sigset_t set;
    sigfillset(&set);
    sigdelset(&set,SIGALRM);
    sigdelset(&set,SIGCHLD);

    while(1){
        sigsuspend(&set);

        if(finito){
           return 0; 
        }
        else{
           return wait_till_pid(pid);
        }
    }
}