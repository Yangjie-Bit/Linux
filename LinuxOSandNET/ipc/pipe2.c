/*===============================================================
 * Copyright (C) . All rights reserved.")"
 * 文件名称: pipe2
 * 创 建 者: yangjie
 * 创建日期: 2020年1月7日
 * 描    述: 
 * =============================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>         
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
  // ls | grep make
  int pipefd[2];
  int ret = pipe(pipefd);
  if(ret < 0)
  {
    perror("pipe error!\n");
    return -1;
  }

  int pid1 = fork();
  if(pid1 == 0)
  {
    // ls
    close(pipefd[0]);
    dup2(pipefd[1],1);
    // int dup2(int oldfd, int newfd);
    // int execlp( const char *file, const char *arg, ... );
    execlp("ls","ls",NULL);
    exit(0);
  }

  int pid2 = fork();
  if(pid2 == 0)
  {
    // grep make
    close(pipefd[1]);
    dup2(pipefd[0],0);
    execlp("grep","grep","make",NULL);
    exit(0);
  }
  close(pipefd[1]);
  close(pipefd[0]);
  // pid_t waitpid(pid_t pid, int *status, int options);
  waitpid(pid1,NULL,0);
  waitpid(pid2,NULL,0);
  return 0;
}
