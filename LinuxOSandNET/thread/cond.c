/*===============================================================
 * Copyright (C) . All rights reserved.")"
 * 文件名称：cond
 * 创 建 者: yangjie
 * 创建日期: 2020年1月13日
 * 描    述: 这个demo实现条件变量的基本使用
 *           以自己吃面和厨师做面为例子;
 *           自己要想吃面, 前提得有面, 没有则等待;
 *           厨师做面, 做好面后, 唤醒吃面的人.
 * =============================================================*/

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int _have_noodle = 0;
pthread_mutex_t mutex;
pthread_cond_t cond_eat;
pthread_cont_t cont_cook;
void* eat_noodle(void* arg)
{
  while(1)
  {
    pthread_mutex_lock(&mutex);
    while(_have_noodle == 0)
    {
      // 没有面就不能吃面
      // int pthread_cond_wait(pthread_cond_t* restrict cond, pthread_mutex_t* restrict mutex);
      // 一直阻塞等待
      // int pthread_cond_timedwait(pthread_cond_t* restrict cond, pthread_mutex_t* restrict mutex,
      //     const struct timespec* restrict abstime);
      // 限时等待, 等待超时后报错返回;
      // 休眠之前应该先解锁
      // pthread_cond_wait 实现了三步操作;
      // 1. 解锁;
      // 2. 休眠;
      // 3. 被唤醒后加锁;
      // 其中解锁和休眠必须是原子操作;
      pthread_cond_wait(&cond_eat, &mutex);
    }

    // 能执行下来说明have_noodle == 1, 表示有面
    printf("eat noodle, delicious!\n");
    _have_noodle = 0;
    pthread_cond_signal(&cond_cook);
    pthread_mutex_unlock(&mutext);
  }
  return NULL;
}

void* cook_noodle(void* arg)
{
  while(1)
  {
    pthread_mutex_lock(&mutex);
    // 现在有面, 但是没人吃, 不能继续做了
    pthread_cond_wait(&cond_cook, &mutex);
  }
  printf("cook noodle~~~ come on~~\n");
  _have_noodle = 1;
  pthread_cond_signal(&cond_wait);
  pthread_mutex_unlock(&mutex);
}

int main()
{
  pthread_t tid1, tid2;
  pthread_mutex_init(&mutex, NULL);
  // int pthread_cond_init(pthread_cond_t* cond, const pthrad_condattr_t* attr);
  pthread_cond_init(&cond_eat, NULL);
  pthread_cond_init(&cond_cook, NULL);
  for(int i = 0; i < 4; i++)
  {
    int ret = pthread_create(&tid1, NULL, eat_noodle, NULL);
    if(ret != 0)
    {
      prinf("pthrad create error!\n");
      return -1;
    }
  }

  for(int i = 0; i < 4; i++)
  {
    int ret = pthread_create(&tid2, NULL, eat_noodle, NULL);
    if(ret != 0)
    {
      prinf("pthrad create error!\n");
      return -1;
    }
  }

  pthread_join(tid1, NULL);
  pthread_join(tid2, NULL);
  pthread_mutex_destroy(&mutex);
  // int pthread_cond_destroy(pthread_cond_t* cond);
  pthread_cond_destroy(&cond_eat);
  pthread_cond_destroy(&cond_cook);
  return 0;
}
