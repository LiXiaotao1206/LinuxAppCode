
#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>           /* For O_* constants */
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>


#define SHM_NAME    "shm.dat"
#define SHM_ZISE    10

int  main(void){

    int fd = -1;
    char *mp = NULL;

    //打开共享内存
    fd = shm_open(SHM_NAME, O_RDWR, S_IRUSR | S_IWUSR);
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
    //读内存数据
    printf("shm data = %c\n",*mp);

    //取消内存映射
flg1:    munmap(mp,SHM_ZISE);

    //删除共享内存
    shm_unlink(SHM_NAME);

    return 0;
}