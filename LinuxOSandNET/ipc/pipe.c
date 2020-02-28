/*===============================================================
 * Copyright (C) . All rights reserved.")"
 * 文件名称：pipe
 * 创 建 者: yangjie
 * 创建日期: 2020年1月7日
 * 描    述: 这个demo实现最基本的一个管道通信
 *           通过这个例子体会管道的一些特性
 *           int pipe(int pipefd[2]);
 * =============================================================*/

#include <stdio.h>
#include <fcntl.h>  
#include <unistd.h>
#include <stdlib.h>

int main()
{
  // 管道必须创建于创建子进程之前(这样子进程才能复制到管道的操作句柄)
  // int pipe(int pipefd[2]);
  int pipefd[2];
  int ret = pipe(pipefd);
  if(ret < 0)
  {
    perror("pipe error!\n");
    return -1;
  }

  int pid = fork();
  if(pid == 0)
  {
    // child 
    // 关闭所有的写端, 不要忘了自己
    // close(pipefd[0]);
    char buf[1024] = {0};
    // 若所有写端被关闭, 则read不再阻塞, 读完数据后返回0
    int ret = read(pipefd[0],buf,1023);
    printf("child read buf:[%d-%s]\n",ret,buf);
    exit(0);
  }
  else if(pid > 0)
  {
    sleep(1);
    // close(pipefd[0]);
    // parent
    int total_len = 0;
    total_len += write(pipefd[1],"hello world",11);
    printf("-------line-------\n");
  }
  return 0;
}
