#include <iostream>
#include <queue>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>

#define THE_MAX 3

typedef void(*handler_t)(int data)
class Task
{
  public:
    void SetTask(int data, handler_t handler)
    {
      _data = data;
      _handler = handler;
    }

    void Run()
    {
      _handler(_data);
    }

  private:
    int _data;
    handler_t _handler;
}

class ThreadPool
{
  public:
    ThreadPool(int max = THR_MAX) : _thr_max(max),_cur_thr(max),_quit_flag(false)
    {
      pthread_mutex_init(&_mutex,NULL);
      pthread_cond_init(&_con_cond,NULL);
      pthread_cond_init(&_pro_cond,NULL);
    }

    ~ThreadPool()
    {
      pthread_mutex_destroy(&_mutex);  
      pthread_cond_destroy(&_con_cond);
      pthread_cond_destroy(&_pro_cond);
    }

    bool PoolInit()
    {
      int ret;
      for(int i = 0; i < _thr_max; i++)
      {
        ret = pthread_create(&tid, NULL, thr_start, (void*)this);
        if(ret != 0)
        {
          std::cerr << "thread create error\n"
          return false
        }
        pthread_detach(tid);
      }
      return true;
    }

    bool TaskPush(Task& t)
    {
      QueueBlock();
      _task_queue.push(t);
      ConsumerWakeUp();
      QueueUnBlock();
      return true;
    }

    bool TaskPop(Task& t)
    {
      t = _task_queue.front();
      _task_queue.pop();
      return true;
    }

    static void* thr_start(void* arg)
    {
      ThreadPool* pool = (ThreadPool*)arg;
      while(1)
      {
        pool->QueueBlock();
        while(pool->QueueIsEmpty())
        {
          pool->ConsumerWait();
        }
        Task t;
        pool->TaskPop(t);
        pool->QueueBlock();
        t.Run();
      }
      return NULL;
    }

    void PoolQuit()
    {
      QueueBlock();
      if(_quit_flag == false)
      {
        _quit_flag = true;
      }
      QueueUnBlocl();
      while(_cur_thr > 0)
      {
        ConsumerWakeUpAll();
        usleep(1000);
      }
    }

  public:
    void QueueBlock()
    {
      pthread_mutex_lock(&_mutex);
    }

    void QueueUnBlock()
    {
      pthread_mutex_unlock(&_mutex);
    }

    void ConsumerWait()
    {
      // 线程陷入等待之前先判断一下用户是否需要销毁线程池
      if(_quit_flag == true)
      {
        _cur_thr--;
        pthread_mutex_unlock(&mutex);
        printf("thread:%p exit\n",pthread_self());
        pthread_exit(NULL);
      }
      pthread_cond_wait(&_con_cond,&mutex);
    }

    void ConsumerWakeUp()
    {
      pthread_cond_broadcast(&_con_cond);
    }

    bool QueueIsEmpty()
    {
      return _task_queue.empty();
    }

  private:
    int _thr_max;
    int _cur_thr;
    bool _quit_flag;
    std::queue<Task> _task_queue;
    pthread_mutex_t _mutex;
    pthread_cond_t _pro_cond;
    pthread_cond_t _con_cond;
}

void thr_handle(int data)
{
  srand(time(NULL));
  int sec = rand()%5;
  printf("thr:%p--get data:%d--sleep:%d sec\n",pthread_self(), data, sec );
  sleep(sec);
}

int main()
{
  ThreadPool pool;
  pool.PoolInit();
  for(int i = 0; i < 10; i++)
  {
    Task task;
    task.SetTask(i, thr_handle);
    pool.TaskPush(task);
  }
  pool.PoolQuit();
  return 0;
}
