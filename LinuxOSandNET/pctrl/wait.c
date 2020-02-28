/*===============================================================
 * Copyright (C) . All rights reserved.")"
 * 文件名称：wait
 * 创 建 者: yangjie
 * 创建日期: 2020年1月7日
 * 描    述: 这是一个实现进程等待的demo
 *           从这个demo中我们要体会, wait/waitpid两个接口的阻塞等待
 *           以及子进程的退出返回值的获取
 *           pid_t wait(int *status);
 *           pid_t waitpid(pid_t pid, int *status, int options);
 * =============================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>         

int main()
{
  int pid = fork();
  if(pid < 0)
  {
    // errno是一个全局变量, 存储每次系统调用接口出现错误原因编号
    // strerror 通过错误编号获取字符串错误原因
    printf("fork error :%s\n",strerror(errno));
    // perror 直接打印上一个系统调用错误原因
    perror("fork error");
  }
  else if(pid == 0){
   sleep(3);
   exit(1);
  }

  // pid_t wait(int *status);                            
  // 阻塞等待任意一个子进程退出, 获取返回值
  // wait(NULL);
  // pid_t waitpid(pid_t pid, int *status, int options); 
  // 阻塞等待任意一个子进程或者指定的子进程退出
  // pid: -1:等待任意一个子进程    pid > 0:等待指定子进程
  // option: WNOHANG: 将waitpid设置为非阻塞  0: 默认阻塞
  // 返回值: 若WNOHANG被指定, 没有子进程退出则立即报错返回0, 错误: 返回-1
  int statu;
  while(waitpid(-1,&statu,WNOHANG) == 0 )
  {
    // 非阻塞轮询操作
    printf("drink coffee!\n");
    sleep(1);
  }
  if((statu & 0x7f) == 0)
  {
    printf("exit code:%d\n",(statu>>8)&0xff);
  }
  if(WIFEXITED(statu))
  {
    printf("exit code:%d\n",WEXITSTATUS(statu));
  }
  while(1)
  {
    printf("i am parent!\n");
    sleep(1);
  }
  return 0;
}
