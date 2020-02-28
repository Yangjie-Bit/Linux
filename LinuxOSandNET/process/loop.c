/*===============================================================
 * Copyright (C) . All rights reserved.")"
 * 文件名称：loop
 * 创 建 者: yangjie
 * 创建日期: 2020年1月6日
 * 描    述: 死循环
 * =============================================================*/

#include <stdio.h>
#include <unistd.h>

int main()
{
  while(1)
  {
    sleep(0.5);
    printf("I will do better!\n");
  }
  return 0;
}
