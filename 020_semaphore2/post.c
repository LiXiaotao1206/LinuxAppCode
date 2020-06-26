
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <semaphore.h>
#include <stdio.h>

#define SEM_NAME    "sem"


int main(void){

    //创建有名信号量
    sem_t *sem = NULL;
    sem = sem_open(SEM_NAME, O_CREAT|O_RDWR, 0777, 0);
    if(sem==SEM_FAILED){
        perror("sem_open:");
        return -1;
    }

    //post
    if(sem_post(sem)<0){
        perror("post:");
    }
    printf("post sem\n");

    //关闭并删除有名信号量
    sem_close(sem);
    sem_unlink(SEM_NAME);
    return 0;
}



