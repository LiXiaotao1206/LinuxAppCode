/*******************************************
 * 例程功能：
 * 在主线程捕获输入的字符，每3秒一次循环
 * 在子线程打印输入的结果，每1秒一次循环
 * 使用到了互斥锁,使用cleanup防死锁
 * 由于使用了多线程，编译时-lpthread
 * *****************************************/
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

char buf[256] = {0};
int stop = 0;
pthread_mutex_t mutex;

//防止子线程还没解锁就退出，避免造成死锁
void cleanMutex(void *res){
    printf("clean up\n");
    pthread_mutex_unlock(&mutex);   //开锁
}

void* threadGetInput(void *res){
    pthread_cleanup_push(cleanMutex,(void*)1);  //注意是（void*）1,否则编译失败
    while(!stop){
        pthread_mutex_lock(&mutex); //上锁
        printf("child thread: your input is %s\n",buf);
        pthread_mutex_unlock(&mutex);   //开锁
        sleep(1);
    }
    pthread_exit(NULL); //线程退出,后面记得cleanup_pop
    pthread_cleanup_pop(1); //这个1要与push对应
                            //若pop(0)也可以按出栈顺序pop掉最近的那个push，不过前提是必须得pthread_exit
                            //或者别的线程调用了pthread_cancel
}

int main(){
    pthread_t pth;

    pthread_mutex_init(&mutex,NULL);    //初始化互斥锁

    if(pthread_create(&pth,NULL,threadGetInput,NULL)!=0){
        perror("thread create:");
        return -1;
    }
    printf("创建线程OK\n");

    while(strcmp("over",buf)!=0){
        pthread_mutex_lock(&mutex); //上锁
        scanf("%s",buf);
        pthread_mutex_unlock(&mutex);   //开锁
        sleep(3);
    }
    stop = 1;   //终止子线程的循环
    //pthread_cancel(pth); //最好不要使用此函数


    pthread_join(pth,NULL); //等待线程退出

    printf("线程退出\n");

    pthread_mutex_destroy(&mutex);  //销毁互斥锁

    return 0;
}
