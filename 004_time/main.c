#include <time.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>

void timeTest();


int main(void){

    timeTest();
    return 0;
}

void timeTest(){

    char *tc;
    struct tm *tmc;
    //获取系统时间
    time_t timer = time(NULL);  //或者可以time(t);
    printf("t=%ld\n",timer);    //t=1590896689

    //测试 ctime函数
    tc = ctime(&timer);
    printf("ctime:%s",tc);    //ctime:Sun May 31 11:59:45 2020

    //测试 gmtime函数  或者gmtime_r函数
    tmc = gmtime(&timer);   //gmtime: 120-5-31  3:53:25
    printf("gmtime: %d-%d-%d  %d:%d:%d\n",
        tmc->tm_year+1900,tmc->tm_mon+1,tmc->tm_mday,tmc->tm_hour,tmc->tm_min,tmc->tm_sec);

    //测试 localtime函数  或者localtime_r函数
    tmc = localtime(&timer);   //localtime: 120-5-31  3:53:25
    printf("localtime: %d-%d-%d  %d:%d:%d\n",
        tmc->tm_year+1900,tmc->tm_mon+1,tmc->tm_mday,tmc->tm_hour,tmc->tm_min,tmc->tm_sec);

    //测试 asctimetime函数  其实和ctime一样，只是函数参数不同
    tc = asctime(tmc);  
    printf("asctime:%s",tc);   //asctime:Sun May 31 11:59:45 2020 

    //测试gettimeofday 实际是1970-1-1零点到现在的时间
    struct timeval tv;
    if(gettimeofday(&tv,NULL)!=0){
        perror("gettimeofday:");
    }
    else{
        printf("gettimeofday:%ld\n",tv.tv_sec); //gettimeofday:1590898092
    }
}


