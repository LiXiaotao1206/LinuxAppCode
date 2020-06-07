#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

#define FILENAME "test.txt"

void processShareFileTest();
void processNoShareFileTest();


int main(void){

    processShareFileTest();
    //processNoShareFileTest();
}

/**************************************************
 * 新建进程，两个进程共享文件指针
 * 
 * 把test.txt清空，执行后，文件里有hello 也有 world
 * ************************************************/
void processShareFileTest(){

    int status;
    int fd = open(FILENAME,O_RDWR,0666);
    if(fd<0){
        perror("open:");
        return;
    }
    printf("open fd = %d\n",fd);
    pid_t id = fork();
    if(id>0){   //父进程处理

        write(fd,"hello",5);
        //等待子进程退出，回收子进程
        wait(&status);
        //waitpid(id,&status,0);        //阻塞
        //waitpid(id,&status,WNOHANG);  //非阻塞
        close(fd);
        //判断是否是正常退出 （子进程exit()  _exit()  return)
        if(WIFEXITED(status)!=0){
            printf("子进程正常退出\n");
        }
        //判断是否是非正常退出
        if(WIFSIGNALED(status)!=0){
            printf("子进程退出异常\n");
        }
        //打印退出的子进程的id
        printf("退出的子进程id=%d\n",WEXITSTATUS(status));
    }
    else if(id==0){ //子进程处理
        sleep(1);
        write(fd,"world",5);
        //return 123;
        //_exit(123);
        exit(123);
    }
    else{   //新建进程错误
        perror("fork:");
    }
}


/****************************************************************
 * 父进程和子进程分别打开同一文件
 * 发现两个进程的文件指针是独立的
 * 不是共享的
 * 
 * 把test.txt清空，执行后，文件里只有一个world
 * ***************************************************************/
void processNoShareFileTest(){
    int id = fork();
    if(id>0){
        int status;
        int fd = open(FILENAME,O_RDWR,0666);
        write(fd,"hello",5);
        wait(&status);
        close(fd);
        printf("exit\n");
    }
    else if(id==0){
        sleep(1);
        int fd = open(FILENAME,O_RDWR,0666);
        write(fd,"world",5);
        close(fd);
        exit(123);
    }
    else{   //新建进程错误
        perror("fork:");
    }
}