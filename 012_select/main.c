#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

int mouseInit();
int readMouse(const int mouseFd, char* buf, const unsigned int len);
int readKey(char* buf,const unsigned int len);


int main(void){

    char buf[256];
    fd_set readFds;
    struct timeval tv;

    int mouseFd = mouseInit();
    if(mouseFd<0){
        perror("mouseInit:");
        return -1;
    }

    tv.tv_sec = 10;
    tv.tv_usec = 0;

    while(1){

        FD_ZERO(&readFds);
        FD_SET(mouseFd,&readFds);
        FD_SET(0,&readFds);

        int selRet = select(mouseFd+1,&readFds,NULL,NULL,&tv);
        
        if(selRet<0){
            perror("select:");
            return -1;
        }
        else if(selRet==0){
            //printf("select ret=0,no data readed\n");
            continue;
        }
        else{
            if(FD_ISSET(0,&readFds)){
                readKey(buf,256);
                printf("read key:[%s]\n",buf);
            }
            if(FD_ISSET(mouseFd,&readFds)){
                readMouse(mouseFd,buf,256);
                printf("read mouse:[%s]\n",buf);
            }
        }
    }
    
}

/***********************************************
 * 读鼠标初始化
 * ********************************************/
int mouseInit(){
    return open("/dev/input/mouse0",O_RDONLY);
}

/***********************************************
 * 读鼠标数据
 * ********************************************/
int readMouse(const int mouseFd, char* buf, const unsigned int len){
    memset(buf,0,len);
    return read(mouseFd,buf,len);
}


/***********************************************
 * 读键盘数据
 * ********************************************/
int readKey(char* buf,const unsigned int len){
    memset(buf,0,len);
    return read(0,buf,len); //键盘是标准输入，文件描述符为0
}