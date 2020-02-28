/*===============================================================
 * Copyright (C) . All rights reserved.")"
 * 文件名称：exit
 * 创 建 者: yangjie
 * 创建日期: 2020年1月7日
 * 描    述: 这是一个演示进程退出场景以及如何退出的demo
 * =============================================================*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int hot_beef_noodle = 0;
int main()
{
  printf("----------------------\n");
  sleep(2);
  // _exit(1);                             // 任意位置调用都是退出进程
  exit(1);
  // return 1;                               // 从main函数中的return退出也是退出进程
  printf("i want to eat hot_beef_noodle!!!\n");
  if(hot_beef_noodle)
  {
    printf("continue to eat hot_beef_noodle!!!\n");
  }
  else{
    printf("eat dumplings!!!\n");
  }
  printf("eat noodle!!!\n");
  return 0;
}

