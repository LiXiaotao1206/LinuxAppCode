#include <stdio.h>
#include <sys/types.h>          
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#define IP_ADDR "192.168.31.184"


int main(){
    //创建socket
    int fd = socket(AF_INET,SOCK_DGRAM,0);
    if(fd<0){
        perror("socket:");
        return -1;
    }
    printf("server fd = %d\n",fd);
    //收发数据
    struct sockaddr_in socketAddr;
    socketAddr.sin_family = AF_INET;
    socketAddr.sin_addr.s_addr = inet_addr(IP_ADDR);
    socketAddr.sin_port = htons(5000);
    socklen_t socketAddrLen = sizeof(socketAddr);
    char buf[128] = {0};
    while(buf[0]!='0'){
        memset(buf,0,sizeof(buf));
        scanf("%s",buf);
        sendto(fd,buf,sizeof(buf),0,(struct sockaddr *)&socketAddr,socketAddrLen);
        if(recvfrom(fd,buf,sizeof(buf),0,(struct sockaddr *)&socketAddr,&socketAddrLen)>0){
            printf("recv ip=%s, buf=%s\n",inet_ntoa(socketAddr.sin_addr),buf);
        }
    }
    close(fd);
    return 0;
}