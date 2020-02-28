/*===============================================================
 * Copyright (C) . All rights reserved.")"
 * 文件名称：signal
 * 创 建 者: yangjie
 * 创建日期: 2020年1月7日
 * 描    述: 这个demo体会信号替换动作的修改
 *           sighandler_t signal(int signum, sighandler_t handler);
 *           int sigaction(int signum, const struct sigaction *act,
 *                        struct sigaction *oldact);
 * =============================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <signal.h>
#include <unistd.h>

void sigcb(int signo)
{
  printf("recv a signo:%d\n", signo);
  signal(signo,SIG_DFL);
}

int main()
{
  // signal(SIGINT,SIG_IGN);
  struct sigaction new_act, old_act;
  new_act.sa_flags = 0;
  new_act.sa_handler = sigcb;
  // int sigemptset(sigset_t *set);
  // 清空set信号集合
  sigemptyset(&new_act.sa_mask);

  // sigaction使用new_act替换2号信号的处理动作, 将原有动作保存到old_act中
  sigaction(2,&new_act,&old_act);

  while(1)
  {
    printf("everything would be better!\n");
    sleep(3);
  }
}
