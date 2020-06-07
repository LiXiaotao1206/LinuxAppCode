#include <stdio.h>
#include <sys/types.h>          
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#define IP_ADDR "192.168.31.184"
int main(){
    //建立socket
    int socketFd = socket(AF_INET, SOCK_STREAM, 0);
    if(socketFd<0){
        perror("socket:");
        return -1;
    }
    printf("socket fd = %d\n",socketFd);

    //connect
    struct sockaddr_in sockAddr;
    sockAddr.sin_family = AF_INET;
    sockAddr.sin_addr.s_addr = inet_addr(IP_ADDR);
    sockAddr.sin_port = ntohs(5000);
    if(connect(socketFd, (const struct sockaddr *)&sockAddr, sizeof(sockAddr))!=0){
        perror("connect:");
        close(socketFd);
        return -1;
    }
    printf("connect ok\n");

    //收发数据
    char buf[128] = {0};
    while(buf[0]!='0'){
        memset(buf,0,sizeof(buf));
        scanf("%s",buf);
        send(socketFd,buf,sizeof(buf),0);
        if(recv(socketFd,buf,sizeof(buf),0)>0){
            printf("recv:%s\n",buf);
        }
    }
    //关闭连接
    close(socketFd);

    return 0;
}