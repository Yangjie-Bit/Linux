/*===============================================================
 * Copyright (C) . All rights reserved.")"
 * 文件名称：systemio
 * 创 建 者: yangjie
 * 创建日期: 2020年1月6日
 * 描    述: 这个demo用于演示系统调用io接口的基本使用
 *           int open(const char *pathname, int flags, mode_t mode);
 *           ssize_t read(int fd, void *buf, size_t count);
 *           ssize_t write(int fd, const void *buf, size_t count);
 *           off_t lseek(int fd, off_t offset, int whence);
 *           int close(int fd);
 *           mode_t umask(mode_t mask);
 * =============================================================*/

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
int main()
{
    // mode_t umask(mode_t mask);
    // 将当前进程的文件创建权限掩码修改为mask
    umask(0);
    // int open(const char *pathname, int flags, mode_t mode);
    int fd  = open("test.txt",O_RDWR|O_CREAT|O_APPEND,0664);
    if(fd < 0 )
    {
      perror("open error!");
      return -1;
    }
    // ssize_t read(int fd, void *buf, size_t count);
    // fd: open打开文件所返回的文件描述符
    // buf: 要写入的数据
    // count: 要写入的字节数
    // 返回值: 实际写入的字节数
    char* data = "life is the sun!!!\n";
    ssize_t ret = write(fd, data, strlen(data));
    if(ret < 0)
    {
      perror("write error!");
      return -1;
    }
    // off_t lseek(int fd, off_t offset, int whence);
    // 跳转fd文件的读写位置到指定处
    // whence: SEEK_SET  SEEL_CUR  SEELK_END
    // offset: 偏移量
    lseek(fd,2,SEEK_SET);

    // ssize_t read(int fd, void *buf, size_t count);
    // 从fd文件中读取count长度的数据, 放到buf中
    // 返回值: 返回实际读取到的字节数    失败: 返回-1
    char buf[1024] = {0};
    ret = read(fd, buf, 1023);
    if(ret < 0)
    {
      perror("read error!");
      return -1;
    }
    printf("ret: %d-[%s]\n",ret,&buf);

    // int close(int fd);
    close(fd);
}
