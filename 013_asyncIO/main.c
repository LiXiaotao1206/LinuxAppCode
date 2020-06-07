#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>




/***********************************************
 * 本例程用于演示异步IO
 * 程序主任务一直循环读键盘
 * 把读鼠标设为一个异步事件，类似于中断
 * 当鼠标有数据，就会触发
 * ********************************************/

int mouseFd = -1;

//异步IO事件的处理函数，读鼠标
void getMouseData(int sig){
    if(sig!=SIGIO){
        return;
    }
    char buf[128] = {0};
    if(read(mouseFd,buf,128)>0){
        printf("read mouse data:[%s]\n",buf);
    }
}

int main(){

    mouseFd = open("/dev/input/mouse0",O_RDONLY);
    if(mouseFd<0){
        perror("open mouse:");
        return -1;
    }

    //把鼠标文件描述符设置为可接收异步IO
    int mouseFl = fcntl(mouseFd,F_GETFL);
    mouseFl |= O_ASYNC;
    fcntl(mouseFd,F_SETFL,mouseFl);
    //设置接收异步IO事件的进程为当前进程（当然也可以在其他进程处理）
    fcntl(mouseFd,F_SETOWN,getpid());
    //注册异步IO信号捕获函数
    signal(SIGIO,getMouseData);


    while(1){
        //读键盘
        char buf[128] = {0};
        if(read(0,buf,128)>0){
            printf("read key data:[%s]\n",buf);
        }
    }

    return 0;
}


