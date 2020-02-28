/*===============================================================
 * Copyright (C) . All rights reserved.")"
 * 文件名称：fifo_read
 * 创 建 者: yangjie
 * 创建日期: 2020年1月7日
 * 描    述: 这个demo实现一个简单的命名管道通信, 通过这个demo
 *           体会管道的一些特性
 *           int mkfifo(const char *pathname, mode_t mode);
 * =============================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

int main()
{
  char* fifo = "./test.fifo";
  umask(0);
  // int mkfifo(const char *pathname, mode_t mode);
  int ret = mkfifo(fifo,0664);
  if(ret < 0)
  {
    if(errno != EEXIST)
    {
      perror("mkfifo error!\n");
      return -1;
    }
  }

  printf("start open ----------\n");
  int fd = open(fifo,O_RDONLY);
  printf("end open-------------\n");
  if(fd < 0)
  {
    perror("open error\n");
    return -1;
  }
  printf("fifo:%s open success!\n",fifo);

  while(1)
  {
    sleep(3);
    char buf[1024] = {0};
    read(fd,buf,1023);
    printf("peer say: %s\n",buf);
  }
  close(fd);
  return 0;
}

