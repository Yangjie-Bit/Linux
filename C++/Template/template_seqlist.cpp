/*===============================================================
 * Copyright (C) . All rights reserved.")"
 * 文件名称：template_seqlist
 * 创 建 者: yangjie
 * 创建日期: 2020.1.16
 * 描    述: 这个demo描述了一个通用的顺序表
 * =============================================================*/

#include <iostream>
using namespace std;

template<class T>
class SeqList
{
  public:
    SeqList(size_t capacity = 3)
      :_array(new T[capacity])
      ,_size(0)
      ,_capacity(capacity)
    {}
  
    // 拷贝构造 & 赋值运算符重载
    ~SeqList()
    {
      if(_array)
      {
        delete[] _array;
        _array = nullptr;
        _size = 0;
        _capacity = 0;
      }
    }

    void PushBack(const T& data);

    void PopBack()
    {
      if(!Empty())
      {
        return;
      }
      --size;
    }

    // 随机访问
    T& operator[](size_t index)
    {
      return _array[index];
    }

    T& Front()
    {
      return _array[0];
    }

    size_t Size()const
    {
      return _size;
    }

    size_t Capacity()const
    {
      return _capacity;
    }

    bool Empty()const
    {
      return 0 == _size;
    }

  private:
    T* _array;
    size_t _size;
    size_t _capacity;
};

void SeqList<T>::PushBack(const T& data)
{
  // CheckCapacity();
  _array[_size++] = data;
}

int main()
{
  int array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
  cout << array[5] << endl;

  SeqList<int> s1;
  s1.PushBack(1);
  s1.PushBack(2);
  s1.PushBack(3);
  cout << s1.Size() << endl;
  cout << s1.Capacity() << endl;
  cout << s1.Front() << endl;
  s1[1] = 10;

  SeqList<double> s2;
  s2.PushBack(1.0);
  s2.PushBack(2.0);
  s2.PushBack(3.0);
  return 0;
}
