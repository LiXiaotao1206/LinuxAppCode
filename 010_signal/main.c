
#include <stdio.h>
#include <signal.h>
#include <unistd.h>


/* 3种信号捕获的情况 */
//#define SIGNAL_TEST
//#define SIGACTION_TEST_1
#define SIGACTION_TEST_2

void sighandlerCallback(int sig){
    printf("sighandlerCallback,sig=%d\n",sig);
}

void sigactionCallback(int sig,siginfo_t *si,void *res){
    printf("sigactionCallback,sig=%d,signo=%d,sender_pid=%d,res=%d\n",
        sig,
        si->si_signo,
        si->si_pid,
        *((int*)res));

}

int main(void){

#if defined SIGNAL_TEST //第一种
    // signal(SIGINT,SIG_IGN); //对中断信号屏蔽，按下ctrl+C没反应
    signal(SIGINT,sighandlerCallback);
#elif defined SIGACTION_TEST_1  //第二种
    struct sigaction sa;
    sa.sa_handler = sighandlerCallback;
    sigaction(SIGINT,&sa,NULL);
#elif defined SIGACTION_TEST_2  //第三种
    struct sigaction sa;
    sa.sa_flags |= SA_SIGINFO;
    sa.sa_sigaction = sigactionCallback;
    sigaction(SIGINT,&sa,NULL);
#endif


    while(1){
        printf("I am running...\n");
        sleep(1);
    }
}