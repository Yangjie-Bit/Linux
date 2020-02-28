/*===============================================================
 * Copyright (C) . All rights reserved.")"
 * 文件名称：exit
 * 创 建 者: yangjie
 * 创建日期: 2020年1月13日
 * 描    述: 通过这个demo体会线程退出的几种方式
 * =============================================================*/

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>

void* thr_entry(void* arg)
{
  pthread_detach(pthread_self());
  char* ptr = "nihao~~";
  sleep(3);
  pthread_exit(ptr);
  while(1)
  {
    printf("i am common thread---%s\n", (char*)arg);
    sleep(1);
  }
  return NULL;
}

int main()
{
  pthread_t mtid;
  // pthread_t pthread_self(void);
  // 获取调用线程的线程ID
  // int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
  //     void *(*start_routine) (void *), void *arg);
  pthread_t tid;
  char* param = "this is input param";
  int ret = pthread_create(&tid, NULL, thr_entry, (void*)mtid);
  if(ret != 0)
  {
    printf("pthread create error!\n");
    return -1;
  }
  void* retval;
  ret = pthread_join(tid, &retval);
  if(ret == EINVAL)
  {
    printf("thread is not joinable!\n");
  }
  printf("ret:%d tid:%p---retval:%s\n",ret, tid, retval);
  // pthread_cancel(tid);
  while(1)
  {
    printf("i am main thread---\n");
    sleep(1);
  }
  return 0;
}
