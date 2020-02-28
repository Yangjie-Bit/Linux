/*===============================================================
 * Copyright (C) . All rights reserved.")"
 * 文件名称：string
 * 创 建 者: yangjie
 * 创建日期: 2020.1.15
 * 描    述:
 *
 * =============================================================*/

#include <iostream>
#include <malloc.h>
#include <assert.h>

class String
{
  public:
    String(const char* pstr = "")
    {
      _str = (char*) malloc (strlen(pstr) +1);
      if(nullptr == _str)
      {
        assert(0);
        return;
      }
      strcpy(_str, pstr);
      cout << "String()" << endl;
    }

    ~String()
    {
      if(_str)
      {
        free(_str);
      }
      cout << "~String()" << endl;
    }

  private:
    char* _str;
};

void TestString()
{
  String s1("hello");
  String s2(s1);
  String s3("world");
  // 默认的赋值: 浅拷贝 + 内存泄漏
  s3 = s1;
}

int main()
{
  TestString();
  return 0;
}
