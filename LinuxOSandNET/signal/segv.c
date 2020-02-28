/*===============================================================
 * Copyright (C) . All rights reserved.")"
 * 文件名称：segv
 * 创 建 者: yangjie
 * 创建日期: 2020年1月7日
 * 描    述:
 *
 * =============================================================*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int main()
{
  // int kill(pid_t pid, int sig);
  // 向pid进程发送sig信号
  kill(getpid(),SIGHUP);

  // int raise(int sig);                  向自己发送sig信号
  raise(SIGTERM);

  // void abort(void);                    给自己发送SIGABRT信号
  abort();

  // unsigned alarm(unsigned seconds);
  // 经过seconds秒之后, 给自己发送一个SIGALARM信号--定时器
  // seconds==0时, 表示取消上一个时间未到的定时器
  alarm(3);
  // alarm(0);
  
  while(1)
  {
    printf("hello world!\n");
    sleep(1);
  }

  char* ptr = NULL;
  memcpy(ptr,"hello",5);
  return 0;
}
