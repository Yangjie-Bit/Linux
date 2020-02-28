/*===============================================================
 * Copyright (C) . All rights reserved.")"
 * 文件名称：template (函数模板)
 * 创 建 者: yangjie
 * 创建日期: 2020.1.16
 * 描    述:
 *
 * =============================================================*/

#include <iostream>
using namespace std;

template<typename T>
T Add(T left, T right)
{
  cout << typeid.name() << endl;
  return left +right;
}

int main()
{
  // 隐式实例化
  // 对Add函数模板进行实例化
  cout << Add(1, 2) << endl;           // int,int-->T-->int-->专门处理int的Add函数

  // 在编译阶段, 编译器需要对实参的类型进行推演, 来确认模板参数
  // 类表中T的实际类型, 最后生成处理具体类型的有效代码
  cout << Add(1.0, 2.0) << endl;

  // Add(1, (int)2.0);                 // int, double--->int
  // 显示实例化---> 直接将T的类型实例化为参数类型, 不需要对实参的类型进行推演
  // 在代码执行时, 可能会对实参作隐式的类型转化
  Add<double>(1, 2.0);
  return 0;
}
