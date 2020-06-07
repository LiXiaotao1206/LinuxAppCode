#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>


#define FILENAME "test.txt"

int statTest(void);
void accessTest(void);

int main(void){


    statTest();
    accessTest();
}

/*******************************************
 * 使用stat()检查文件属性
 * *****************************************/
int statTest(void){

    struct stat s;
    int ret = stat(FILENAME,&s);
    if(ret!=0){
        perror("stat:");
        return ret;
    }
    //打印文件大小
    printf("size=%ld\n",s.st_size);
    //打印文件的是不是文件夹
    if ((s.st_mode & S_IFMT) == S_IFDIR) {
        printf("this is a dir\n");
    }
    else{
        printf("not dir\n");
    }
    //或者可以这样
    int m = S_ISDIR(s.st_mode);
    if(m){
        printf("this is a dir\n");
    }
    else{
        printf("not dir\n");
    }
    //文件权限
    if ((s.st_mode & S_IRUSR) == 0) {
        printf("owner has no read permission\n");
    }
    else{
        printf("owner has read permission\n");
    }
    return ret;
}

/****************************************************
 * 使用access()检查文件
 * 存在？可读？
 * *************************************************/
void accessTest(void){

    if(access(FILENAME,F_OK)!=0){
        printf("no exist\n");
        return;
    }
    if(access(FILENAME,R_OK)==0){
        printf("can read ok\n");
    }
}

