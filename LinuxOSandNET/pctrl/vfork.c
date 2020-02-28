/*===============================================================
 * Copyright (C) . All rights reserved.")"
 * 文件名称: vfork
 * 创 建 者: yangjie
 * 创建日期: 2020年1月7日
 * 描    述: 这是一个体会vfork的demo, 父进程调用vfork会阻塞
 * =============================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
  // pid_t vfork(void);
  int pid = vfork();
  if(pid == 0 )
  {
    // return -1;
    printf("-------i am child!-------\n");
    sleep(3);
    // return -1;
    // exit(0);
    printf("-----i am child two!-----\n");
  }
  printf("-------i am parent!--------\n");
  return 0;
}

