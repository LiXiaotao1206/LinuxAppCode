#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>           /* For O_* constants */
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>


#define SHM_NAME    "shm.dat"
#define SHM_ZISE    10

//Link with -lrt.


int  main(void){

    int fd = -1;
    char *mp = NULL;

    //创建共享内存
    fd = shm_open(SHM_NAME, O_RDWR|O_CREAT|O_TRUNC, S_IRUSR | S_IWUSR);
    if(fd<0){
        perror("shm_open:");
        return -1;
    }

    //设置共享内存大小
    ftruncate(fd, SHM_ZISE);

    //内存映射
    mp = mmap(NULL, SHM_ZISE, PROT_WRITE, MAP_SHARED, fd, 0);
    if(mp == MAP_FAILED){
        perror("mmap:");
        goto flg1;
    }

    //向内存写数据
    *mp = 'A';

    //需要在10秒内赶紧读，不然就取消内存映射了
    sleep(10);

    //取消内存映射
 flg1:   munmap(mp,SHM_ZISE);

    //关闭内存
    close(fd);
    //删除共享内存
    shm_unlink(SHM_NAME);

    return 0;
}