/*===============================================================
 * Copyright (C) . All rights reserved.")"
 * 文件名称：namespace
 * 创 建 者: yangjie
 * 创建日期: 2020.1.14
 * 描    述: 这个demo简单进行命名空间的运用
 * =============================================================*/

#include <iostream>
#include <stdio.h>
using namespace std;

/*
namespace N1
{
  int a = 10;
  int Add(int left, int right)
  {
    return left + right;
  }
}

int a = 20;

int main()
{
  int a = 30;
  printf("%d\n", a);               // 局部变量a
  printf("%d\n", ::a);             // 全局变量a
  printf("%d\n",N1::a);            // N1::a
  return 0;
}
*/

/*
namespace N1
{
  int a = 10;
  int Add(int left, int right)
  {
    return (left + right);
  }
}

namespace N2
{
  int a = 10;
  int Sub(int left, int right)
  {
    return (left - right);
  }

  namespace N3
  {
    int a = 20;
    int Mul(int left, int right)
    {
      return (left * right);
    }
  }
}

namespace N4
{
  int a = 30;
  int Dev(int left, int right)
  {
    return (left/right);
  }
}

int main()
{
  cout <<"N2::a"<<N2::a<<" "<<"N2::N3::a"<<N2::N3::a<<" "<<N4::Dev(6,2)<< endl;
  return 0;
}
*/

int main()
{
  int a;
  double d;
  cin >> a >> d;
  cout << "change world!" << endl;
  cout << 100 << " " << d << " " << a << endl; 
  return 0;
}
