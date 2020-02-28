/*===============================================================
 * Copyright (C) . All rights reserved.")"
 * 文件名称：create
 * 创 建 者: yangjie
 * 创建日期: 2020年1月13日
 * 描    述: 通过线程创建的demo体会每一个线程都是一个执行流,
 *           让每一个线程都运行一个死循环, 查看是否都可以打印数据
 * =============================================================*/

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void* thr_entry(void* arg)
{
  while(1)
  {
    printf("i am common thread---%s\n", (char*)arg);
    sleep(1);
  }
  return NULL;
}

int main()
{
  // int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
  //     void *(*start_routine) (void *), void *arg);
  pthread_t tid;
  char* param = "this is input param!";
  int ret = pthread_create(&tid, NULL, thr_entry, (void*)param);
  if(ret != 0)
  {
    printf("pthread create error!\n");
    return -1;
  }

  printf("tid:%p\n",tid);
  while(1)
  {
    printf("i am main thread---\n");
    sleep(1);
  }
  return 0;
}
