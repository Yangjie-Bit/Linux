/*===============================================================
 * Copyright (C) . All rights reserved.")"
 * 文件名称：seqlist
 * 创 建 者: yangjie
 * 创建日期: 2020.1.15
 * 描    述: 
 * =============================================================*/

#include <iostream>
#include <malloc.h>
#include <assert.h>
using namespace std;
typedef int DataType;

class SeqList
{
  public:
    SeqList(size_t capacity = 3)
    {
      cout << "SeqList(int):" << this << endl;
      _array = (DataType*) malloc (sizeof (Datatype) * capacity);
      if(nullptr == _array)
      {
        assert(0);
        return;
      }

      _capacity = capacity;
      _size = 0;
    }

    ~SeqList()
    {
      cout << "~SeqList():" << this << endl;
      if(_array)
      {
        free(_array);
        _array = nullptr;
      }
    }

  private:
    Datatype* _array;
    size_t _size;
    size_t _capacity;
};

void TestSeqList()
{
  SeqList s;
}

int main()
{
  TestSeqList();
  return 0;
}
