/*******************************************
 * 例程功能：
 * 在主线程捕获输入的字符
 * 在子线程打印输入的结果
 * 使用到了条件变量
 * 由于使用了多线程，编译时-lpthread
 * *****************************************/
#include <stdio.h>
#include <pthread.h>
#include <string.h>

char buf[256] = {0};
int stop = 0;
pthread_cond_t cond;
pthread_mutex_t mutex;


void cleanup(void *res){
    printf("clean up\n");
    pthread_mutex_unlock(&mutex);
}

void* threadGetInput(void *res){
    pthread_cleanup_push(cleanup,(void*)1);
    while(!stop){
        //先上锁，再等待条件变量，最后解锁
        pthread_mutex_lock(&mutex);
        pthread_cond_wait(&cond,&mutex);
        printf("child thread: your input is %s\n",buf);
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL); //线程退出
    pthread_cleanup_pop(1);
}

int main(){
    pthread_t pth;

    pthread_cond_init(&cond,NULL);  //初始化条件变量
    pthread_mutex_init(&mutex,NULL); //初始化互斥量,两者是配合使用的，类似于QT中的condition

    //一定要先初始化好互斥量和条件变量后再创建新线程，否则在子线程的cond和mutex没有被初始化
    if(pthread_create(&pth,NULL,threadGetInput,NULL)!=0){
        perror("thread create:");
        return -1;
    }
    printf("创建线程OK\n");

    while(strcmp("over",buf)!=0){
        scanf("%s",buf);
        pthread_cond_signal(&cond); //激发其中一个线程
        //pthread_cond_broadcast(&cond);  //激发所有线程
    }
    stop = 1;   //终止子线程的循环
    //pthread_cancel(pth); //最好不要使用此函数

    pthread_join(pth,NULL); //等待线程退出

    printf("线程退出\n");

    //销毁条件变量和互斥量
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);

    return 0;
}