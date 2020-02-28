/*===============================================================
 * Copyright (C) . All rights reserved.")"
 * 文件名称：create
 * 创 建 者: yangjie
 * 创建日期: 2020年1月6日
 * 描    述: 进程创建
 *           pid_t fork(void);
 *           pid_t vfork(void);
 *           通过复制调用进程, 创建一个新的子进程         
 * =============================================================*/

#include <stdio.h>
#include <unistd.h>

int main()
{
  printf("hello world-----pid:%d\n",getpid());
  // pid_t fork(void);
  // 创建一个子进程, 父进程返回子进程的pid, 子进程返回0
  pid_t pid = fork();
  if(pid < 0 )
  {
    printf("fork error!\n");
    return -1;
  }
  else if(pid == 0)
  {
    printf("-----i am child-----:%d\n",getpid());
  }
  else
  {
    printf("-----i am parent----:%d\n",getpid());
  }
  printf("everything would be better!!!\n");
  while(1)
  {
    printf("Believe yourself!\n");
    sleep(1);
  }
}

