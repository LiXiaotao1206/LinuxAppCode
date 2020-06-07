#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#define SINGLE_PROCESS_FILE "singleprocessflgfile"

void delFile(void);

int main(void){

    int fd = open(SINGLE_PROCESS_FILE,O_CREAT|O_RDWR|O_TRUNC|O_EXCL,0664);
    if(fd<0){
        if (errno == EEXIST)
		{
			printf("该进程已经在运行，不可重复打开！\n");
			return -1;
		}
    }

    atexit(delFile);    //注册进程清理函数

    int i=10;
    for(;i>0;i--){
        printf("i=%d\n",i);
        sleep(1);
    }
    return 0;
}

void delFile(void){
    remove(SINGLE_PROCESS_FILE);    //删除文件
}