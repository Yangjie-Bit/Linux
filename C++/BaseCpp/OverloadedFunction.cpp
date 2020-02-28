/*===============================================================
 * Copyright (C) . All rights reserved.")"
 * 文件名称：OverLoadedFunction (函数重载)
 * 创 建 者: yangjie
 * 创建日期: 2020.1.14
 * 描    述: 这个demo描述函数重载
 *           函数重载: 是函数的一种特殊情况, C++允许在同一作用域中
 *           声明几个功能类似的同名函数, 这些同名函数的形参列表
 *           (参数个数或类型或顺序)必须不同;
 * =============================================================*/

#include <iostream>
using namespace std;

/*
int Add(int left, int right)
{
  return (left + right);
}

double Add(double left, double right)
{
  return (left + right); 
}

long Add(long left, long right)
{
  return (left + right);
}

int main()
{
  // 编译器在编译期间, 必须对实参的类型进行推演
  // 根据推演的结果进行
  Add(1, 2);                        // call Add(int, int);
  Add(1.5, 2.5);                    // call Add(double, double);
  Add('1', '2');                    // char--->int Add(int, int);
  Add(1, (int)2.9);                 // int double;
  return 0;
}
*/

/*
void TestFunc(){}

void TestFunc(int a){}

// int TestFunc(int a){}

void TestFunc(int a, char b){}

void TestFunc(char a, int b){}

int main()
{
  TestFunc(10);
  return 0;
}
*/

int Add(int left, int right)
{
  return (left + right);
}

double Add(double left, double right)
{
  return (left + right); 
}

int Add(int left, double right)
{
  return (left + right); 
}

int main()
{
  cout << "Add(1.0, 2.0)" << "=" << Add(1.0, 2.0) << endl;
  cout << "Add(1, 2)" << "=" << Add(1, 2) << endl;
  cout << "Add(1, 2.0)" << "=" << Add(1, 2.0) << endl;
  return 0;
}
