/*===============================================================
 * Copyright (C) . All rights reserved.")"
 * 文件名称：this
 * 创 建 者: yangjie
 * 创建日期: 2020.1.15
 * 描    述: 通过这个demo简单了解this指针
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
      cout << this << endl;
      strcpy(this->_name, name);
      strcpy(this->_gender, gender);
      this->_age = age;
    }

    void PrintStudent()
    {
      cout << _name << ":" << _gender << ":" << _age << endl;
    }
  // provated:
    char _name[20];
    char _gender[3];
    int _age;
};

int main()
{
  Student p1, p2, p3;
  cout << &p1 << endl;
  p1.InitStudent("peter", "男", 26);
  p2.InitStudent("jingjing", "女", 26);
  p3.InitStudent("jim", "母", 2);

  p1.PrintStudent();
  p2.PrintStudent();
  p3.PrintStudent();
  return 0;
}
#endif
