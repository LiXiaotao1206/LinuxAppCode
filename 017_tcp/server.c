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
    //bind
    struct sockaddr_in sockAddr;
    sockAddr.sin_family = AF_INET;
    sockAddr.sin_addr.s_addr = inet_addr(IP_ADDR);
    sockAddr.sin_port = ntohs(5000);
    bind(socketFd, (const struct sockaddr *)&sockAddr, sizeof(sockAddr));
    printf("bind ok\n");
    //listen
    if(0!=listen(socketFd,5)){
        perror("listen:\n");
        close(socketFd);
        return -1;
    }
    printf("listen ok\n");
    //accept
    struct sockaddr_in clientAddr;
    socklen_t acceptLen = sizeof(clientAddr);
    int clientFd = accept(socketFd, (struct sockaddr *)&clientAddr, &acceptLen);
    printf("accept client, fd=%d,ip=%s\n",clientFd,inet_ntoa(clientAddr.sin_addr));
    //收发数据
    char buf[128] = {0};
    while(buf[0]!='0'){
        memset(buf,0,sizeof(buf));
        int len = recv(clientFd,buf,sizeof(buf),0);
        printf("recv:%s\n",buf);
        send(clientFd,buf,len,0);
    }
    //关闭连接
    close(clientFd);
    close(socketFd);

    return 0;
}