#include <iostream>
#include <pthread.h>
#include <stdlib.h>

class info
{
  public:
    static int* _data;
  public:
    int* getdata()
    {
      pthread_mutex_lock(&mutex);
      if(_data == NULL)
      {
        _data = new int;
        *_data = 10;
      }
      pthread_mutex_unlock(&mutex);
      return _data;
    }
};

int* info::_data = NULL;

int main()
{
  info a;
  info b;
  std::cout << "a.data:" << *a.getdata() <<std::endl;
  std::cout << "b.data:" << *b.getdata() <<std::endl;
  return 0;
}
