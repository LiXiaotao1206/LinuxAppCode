#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>


#define DIRNAME "/home/lixiaotao/linuxApp/3_opendir"

void opendirTest(void);

int main(void){

    opendirTest();
}

/********************************************
 * 使用opendir()函数浏览目录
 * ******************************************/
void opendirTest(void){
    DIR* dir = opendir(DIRNAME);
    struct dirent *fp = readdir(dir);
    //读文件目录内容需要多次读，每读一次系统会返回一个内容
    while(fp!=NULL){
        printf("%s\n",fp->d_name);
        fp = readdir(dir);
    }
}