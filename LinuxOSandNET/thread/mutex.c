/*===============================================================
 * Copyright (C) . All rights reserved.")"
 * 文件名称：mutex
 * 创 建 者: yangjie
 * 创建日期: 2020.1.13
 * 描    述: 
 *      1. 这个demo体会没有互斥的情况线程间资源抢占数据二义性问题
 *      2. 体会互斥锁实现互斥带来的效果
 *      3. 互斥锁实现流程
 * =============================================================*/

#include <stdio.h>
#include <pthread.h>
#include <pthread.h>

// pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex;
int ticket = 100;
void* yellow_bull (void* arg)
{
  while(1)
  {
    // pthread_mutex_lock (pthread_mutex_t* _mutex);
    // _mutex: 互斥锁变量
    // int pthread_mutex_trylock (pthread_mutex_t* mutex);
    // 非阻塞加锁: 若现在不能加锁, 则立即报错返回;
    pthread_mutex_lock(&mutex);
    if (ticket > 0)
    {
      usleep(1000);
      printf("bull %d get a ticket:%d\n", (int)arg, ticket);
      ticket--;
    }
    else{
      printf("have no tickets, bull %d exit\n", (int)arg);
      // 用户在加锁之后, 需要在任意有可能退出线程的地方进行解锁
      pthread_mutex_unlock(&mutex);
      pthread_exit(NULL);
    }
    // int pthread_mutex_unlock(pthread_mutex_t* mutex);
    pthread_mutex_unlock(&mutex);
  }
}

int main()
{
  pthread_t tid[4];
  // int pthread_mutex_init(pthread_mutex_t *restrict mutex, const pthread_mutexattr_t *restrict attr);
  // mutex: 互斥锁变量   attr: 初始化互斥锁属性--通常置为NULL
  pthread_mutex_init(&mutex, NULL);
  int i;
  for(i = 0; i < 4; i++)
  {
    int ret = pthread_create(%tid[i], NULL, yellow_bull, (void*)i);
    if(ret != 0)
    {
      printf("thread create error!\n");
      return -1;
    }
  }

  for(i = 0; i < 4; i++)
  {
    pthread_join(tid[i], NULL);
  }
  // int pthread_mutex_destroy(pthread_mutex_t* mutex);
  // mutex: 互斥锁变量
  pthread_mutex_destroy(&mutex);
  return 0;
}
