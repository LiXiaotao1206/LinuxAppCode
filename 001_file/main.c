#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


#define FILENAME "test.txt"

int dupTest(void);
void fcntlTest(void);

int main(void){

    //dupTest();
    fcntlTest();

    return 0;
}

/**********************************
 * 学习dup() 及 dup2() 函数,
 * 用于复制一个文件描述符
 * ********************************/
int dupTest(void){
    int fd = open(FILENAME,O_CREAT|O_APPEND|O_RDWR,0666);
    if(fd<0){
        perror("dupTest open:");
        return -1;
    }
    printf("open ok, fd = %d\n",fd);
    //测试dup
    int fd2 = dup(fd);
    printf("dup fd2 = %d\n",fd2);
    //测试dup2，新的fd设为5，看dup2后fd3是不是5
    int fd3 = dup2(fd,10); 
    printf("dup fd3 = %d\n",fd3);
    //fd重定位到标准输出,标准输出fd为1,
    //关闭了1，此时fd4会分配为1，
    //这样标准输出的东西会写入到FILENAME文件
    close(1);
    int fd4 = dup(fd);
    printf("dup fd4 = %d\n",fd4);
    write(fd,"hello",6);

    close(fd);
    close(fd2);
    close(fd3);
    close(fd4);
    return 0;
}

/********************************************
 * fcntl()函数学习
 * 用于执行一条命令
 * 例如F_DUPFD就是一条命令，用于复制一个fd
 *******************************************/
void fcntlTest(void){
    int fd = open(FILENAME,O_CREAT|O_APPEND|O_RDWR,0666);
    printf("fd = %d\n",fd);
    int fd2 = fcntl(fd,F_DUPFD,10);
    printf("fd2 = %d\n",fd2);
    close(fd);
    close(fd2);
}
