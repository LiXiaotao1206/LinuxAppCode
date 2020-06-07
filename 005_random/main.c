#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void randTest();


int main(void){

    randTest();
}

/*********************************************
 * 伪随机数测试
 ********************************************/
void randTest(){
    
    srand(time(NULL));  //根据系统时间设置随机种子
    printf("rand:%d\n",rand()%10);
}