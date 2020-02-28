/*===============================================================
 * Copyright (C) . All rights reserved.")"
 * 文件名称：env
 * 创 建 者: yangjie
 * 创建日期: 2020年1月6日
 * 描    述: 这个demo体现环境变量的全局特性
 *           int main(int argc, char* argv[], char* env[])
 * =============================================================*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
  // char* getenv(const char* name);
  // 通过环境变量名获取内容
  // char* ptr = getenv("~");
  // printf("ptr: %s\n",ptr);
  int i;
  extern char** environ;
  for(i = 0; environ[i]!= NULL; i++)
  {
    printf("env[%d]=[%s]\n",i,environ[i]);
  }
  return 0;
}
