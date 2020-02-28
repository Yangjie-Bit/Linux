/*===============================================================
 * Copyright (C) . All rights reserved.")"
 * 文件名称：sem
 * 创 建 者: yangjie
 * 创建日期: 2020年1月7日
 * 描    述: 这个demo体会posix标准信号量的基本操作
 * =============================================================*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>

int ticket = 100;
sem_t sem;

void* thr_start(void* arg)
{
  while(1)
  {
    // int sem_wait(sem_t* sem);
    // 若当前计数<=0, 则线程一直等待
    // int sem_trywait(sem_t* sem);
    // 若当前计数<=0, 则直接报错返回;
    // int sem_timewait(sem_t* sem,struct timespec* abs_timeout);
    // 若当前计数<=0, 等待超时后报错返回, errno == ETIMEOUT
    sem_wait(&sem);
    if(ticket > 0)
    {
      printf("get a ticket:%d\n",ticket);
      ticket--;
    }
    else{
      sem_post(&sem);
      pthread_exit(NULL);
    }
    // int sem_post(sem_t* sem);
    // 计数+1, 促使其他线程操作条件满足, 然后唤醒所有等待线程
    sem_post(&sem);
  }
  return NULL;
}

int main()
{
  int i, ret;
  pthread_t tid[4];
  // int sem_init(sem_t* sem, int pshared, unsigned int value);
  sem_init(&sem, 0, 1);
  for(i = 0; i < 4; i++)
  {
    ret = pthread_create(&tid[i],NULL,thr_start,NULL);
    if(ret != 0)
    {
      printf("pthread create error!\n");
      return -1;
    }
  }
  
  for(i = 0; i < 4; i++)
  {
    pthread_join(tid[i],NULL);
  }  
  
  // int sem_destroy(sem_t* sem);
  sem_destroy(&sem);
  return 0;
}
