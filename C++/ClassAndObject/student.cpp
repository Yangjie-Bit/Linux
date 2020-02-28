/*===============================================================
 * Copyright (C) . All rights reserved.")"
 * 文件名称：student
 * 创 建 者: yangjie
 * 创建日期: 2020.1.15
 * 描    述: 这个demo通过创建student这个类, 然后再去进行访问
 * =============================================================*/

#include <iostream>
using namespace std;
#include <string.h>
#include <stddef.h>

#if 1
class Student
{
  public:
    void InitStudent(char* name, char* gender, int age)
    {
      strcpy(_name, name);
      strcpy(_gender, gender);
      _age = age;
    }

    void PrintStudent()
    {
      cout << _name << ":" << _gender << ":" << _age << endl;
    }
  // provate:
    char _name[20];
    char _gender[3];
    int _age;
};

class A
{
  public:
    void TestFunc()
    {}
;

// 空类---> 占1个字节, 区分该类创建的不同对象
class B
{};

struct C
{
  int a;
  char b;
  double c;
  char d;
};

int main()
{
  B b1, b2, b3;
  cout << offsetof(C, c) << endl;
  cout << sizeof(A) << " " << sizeof(B) << " " << sizeof(C) << endl;

  Student p1, p2, p3;
  p1.InitStudent("peter", "男", 26);
  p2.InitStudent("jingjing", "女", 26);
  p3.InitStudent("jim", "母", 2);

  p1.PrintStudent();
  p2.PrintStudent();
  p3.PrintStudent();
  cout << sizeof(Student) << endl;
  return 0;
}
#endif
