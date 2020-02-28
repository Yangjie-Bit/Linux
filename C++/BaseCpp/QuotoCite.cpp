/*===============================================================
 * Copyright (C) . All rights reserved.")"
 * 文件名称：QuotoCite (引用)
 * 创 建 者: yangjie
 * 创建日期: 2020.1.15
 * 描    述: 通过这个demo介绍引用以及C++中函数通过传递引用,
 *           传指针, 传值的效率与区别;
 *           引用: 给已经存在的变量取了一个别名, 编译器不会为引用
 *           变量开辟内存空间, 它和它引用的变量共同使用同一块内存
 *           空间;引用类型必须和引用实体是同种类型的;
 * =============================================================*/

#include <iostream>
#include <time.h>
using namespace std;

/*
// 传值:
// 按照值的方式进行传递, 将来编译器会生成一份实参的拷贝
// 优点: 函数的副作用不会影响外部的实参;
// 缺点: 传参效率低, 不能通过形参改变实参;
void Swap(int left, int right)
{
  cout << &left << " " << &right << endl;
  int temp = left;
  left = right;
  right = temp;
}

void Swap(int* left, int* right)
{
  int temp = *left;
  *left = *right;
  *right = temp;
}

int main()
{
  int a = 10;
  int b = 20;
  cout << &a << " " << &b << endl;
  Swap(a, b);
  cout << "Swap(a, b)" << a << " " << b << endl;
  Swap(&a, &b);
  cout << "Swap(&a, &b)"<< a << " " << b << endl;
  return 0;
}
*/

/*
void Swap(int left, int right)
{
  int temp = left;
  left = right;
  right = temp;
}

int main()
{
  int a = 10;
  int b = 20;
  cout << "Swap(a, b)" << " " << Swap(a, b) << endl;
  return 0;
}
*/

/*
// 引用特性;
// 1. 引用在定义时必须初始化;
// 2. 一个变量可以有多个引用;
// 3. 引用一旦引用一个实体, 再不能引用其他实体;
//
int main()
{
  int a = 10;
  int& ra = a;
  ra = 100;

  int& rra = ra;
  cout << &a << " " << &ra << " " << &rra << endl;
  return 0;
}
*/

struct A
{
  int a[10000];
};

void TestFunc1(A* a){}

void TestFunc2(A& a){}

void TestRefAndValue()
{
  A a;                                 // 以值作为函数参数
  size_t begin1 = clock();
  for(size_t i = 0; i < 100000; ++i)
  {
    TestFunc1(&a);
  }
  size_t end1 = clock();

  // 以引用作为函数参数
  size_t begin2 = clock();
  for(size_t i = 0; i < 100000; ++i)
  {
    TestFunc2(a);
  }
  size_t end2 = clock();

  // 分别计算两个函数运行结束后的时间
  cout << "TestFunc1(int*)-time: " << end1 - begin1 << endl;
  cout << "TestFunc2(int&)-time: " << end2 - begin2 << endl;
}

int main()
{
  for(int i = 0; i < 10; i++)
  {
    TestRefAndValue();
  }
  return 0;
}
