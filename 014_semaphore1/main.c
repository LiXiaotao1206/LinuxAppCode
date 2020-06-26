/*******************************************
 * 例程功能：
 * 在主线程捕获输入的字符
 * 在子线程打印输入的结果
 * 使用到了信号量
 * 由于使用了多线程，编译时-lpthread
 * *****************************************/
#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <string.h>

char buf[256] = {0};
int stop = 0;
sem_t sem;

void* threadGetInput(void *res){
    while(!stop){
        sem_wait(&sem); //阻塞式等待信号
        printf("child thread: your input is %s\n",buf);
    }
    pthread_exit(NULL); //线程退出
}

int main(){
    pthread_t pth;
    if(pthread_create(&pth,NULL,threadGetInput,NULL)!=0){
        perror("thread create:");
        return -1;
    }
    printf("创建线程OK\n");

    sem_init(&sem,0,0); //初始化信号量

    while(strcmp("over",buf)!=0){
        scanf("%s",buf);
        sem_post(&sem);
    }
    stop = 1;   //终止子线程的循环
    //pthread_cancel(pth); //最好不要使用此函数
    sem_post(&sem); //发送信号量

    pthread_join(pth,NULL); //等待线程退出

    printf("线程退出\n");

    sem_destroy(&sem);  //销毁信号量

    return 0;
}