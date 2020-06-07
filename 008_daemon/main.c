#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <syslog.h>

void createDaemon();

int main(void){

    createDaemon();
    //下面的程序，子进程会复制，因此会执行
    while(1){
        printf("hello\n");
        //附加：可以把一些信息输入到syslog
        openlog("8_daemon",LOG_PID,LOG_USER);
        syslog(LOG_INFO,"%s","daemon test\n");
        closelog();
        sleep(2);
    }
    return 0;
}


/*****************************************************************
 * 调用此函数，会让该进程变为一个守护进程
 * **************************************************************/
void createDaemon(){

    int id = fork();
    if(id<0){
        perror("fork:");
        return;
    }
    //第一步：关闭父进程
    if(id>0){
        printf("parent exit\n");
        exit(0);
    }
    /* 接下来的全是子进程，子进程会完整复制父进程*/
    //第二步：将当前进程设置为一个新的会话期session，目的就是让当前进程脱离控制台。
    id = setsid();
    if (id < 0)
	{
		perror("setsid");
		exit(-1);
	}
    //第三步： 将当前进程工作目录设置为根目录
	chdir("/");
    
    //第四步：设置为0确保将来进程有最大的文件操作权限
    umask(0);

    //第五步：关闭所有文件描述符 
	int cnt = sysconf(_SC_OPEN_MAX);    //先要获取当前系统中所允许打开的最大文件描述符数目
	int i = 0;
	for (; i<cnt; i++)
	{
		close(i);
	}
	//第六步：把标准输入输出错误定位到/dev/null
	open("/dev/null", O_RDWR);  //fd=0
	open("/dev/null", O_RDWR);  //fd=1
	open("/dev/null", O_RDWR);  //fd=2

}


