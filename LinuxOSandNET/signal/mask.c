/*===============================================================
 * Copyright (C) . All rights reserved.")"
 * 文件名称：mask
 * 创 建 者: yangjie
 * 创建日期: 2020年1月7日
 * 描    述: 这个demo实现信号的阻塞, 体会信号的可靠与不可靠
 *           先将所有信号全部阻塞
 *           getchar() 在用户按下回车之前, 这些信号一直被阻塞
 *           对所有信号解除阻塞, 这时信号解除阻塞, 将被处理
 * =============================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void sigcb(int signo)
{
  printf("recv signo:%d\n",signo);
}

int main(){
  signal(SIGINT,sigcb);
  signal(40,sigcb); 
  // int sigprocmask(int how,const sigset_t* set,sigset_t* oldset);
  sigset_t set,oldset;
  sigemptyset(&set);

  // int sigfillset(sigset_t* set);
  // 向set集合中添加所有信号
  // int sigaddset(sigset_t* set, int signum);
  // 向set集合中添加signum信号
  sigfillset(&set);
  sigprocmask(SIG_BLOCK,&set,&oldset);                 // 阻塞set中的信号
  getchar();
  sigprocmask(SIG_UNBLOCK,&set,NULL);
  // sigprocmask(SIG_SETMASK,&oldset,NULL);
  return 0;
}
