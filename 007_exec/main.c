#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void execTest();
void systemTest();

int main(void){

    systemTest();
    execTest();
    return 0;
}

void execTest(){

    char* env[] = {"aaa","bbb","/usr/bin"};

    /* 在同一个进程，只能执行一个exec,因为会阻塞当前进程，若要连续操作多个，需要使用多进程 */

    //execl("/bin/ls","ls",NULL);           //execl 必须指定全路径，否则只在当前目录找，找不到就无法执行
    execlp("ls","ls",NULL);                 //execlp 现在PATH中找，找不到再从当前目录找
    //execle("/bin/ls","ls",NULL,env);      //elecle 把新的环境变量传递进去

    /* 不再测试 */
    //int execv(const char *path, char *const argv[]);
    //int execvp(const char *file, char *const argv[]);
    //int execvpe(const char *file, char *const argv[],char *const envp[]);


}

void systemTest(){

    // system = fork + exec
    system("ls -la");   //不阻塞当前进程
}