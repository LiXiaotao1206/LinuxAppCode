#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void mySleep(unsigned int sec);

int main(void){

    printf("start\n");
    mySleep(3);
    printf("end\n");
    return 0;
}


/**********************************************
 * 使用alarm函数和pause函数模拟实现sleep
 * *******************************************/
void fun(int sig){};
void mySleep(unsigned int sec){
    struct sigaction sa;
    sa.sa_handler = fun;
    sigaction(SIGALRM,&sa,NULL);
    alarm(sec);
    pause();    //讲该进程挂起，交出CPU控制权给别的进程
                //等alarm到了，会打断pause
}