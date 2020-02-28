/*===============================================================
 * Copyright (C) . All rights reserved.")"
 * 文件名称：class
 * 创 建 者: yangjie
 * 创建日期: 2020.1.15
 * 描    述: 通过这个demo识别类名, 类中的成员变量, 类中的成员
             函数以及对成员函数的改写;
 * =============================================================*/

#include <iostream>
using namespace std;

class Student
{
  public:
    void InitStudent(Student* const this, char* name, char* gender, int age)
    {
      strcpy(this->_name, name);
      strcpy(this->_gender, gender);
      this->_age = age;
    }

    void InitStudent(char* name, char* gender, int age)
    {
      // this = nullptr;
      strcpy(_name, name);
      strcpy(_gender, gender);
      _age = age;
    }

    void PrintStudent(Student* const this)
    {
      cout << this->_name << ":" << this->_gender << ":" << this->_age << endl;
    }

    void PrintfStudent()
    {
      cout << _name << ":" << _gender << ":" << _age << endl;
    }

    // this是通过参数压栈
    void TestFunc()
    {
      cout << this << endl;
    }

    // protected:
    char _name[20];
    char _gender[3];
    int _age;
}

int main()
{
  Student p1, p2, p3;
  cout << &p1 << endl;
  cout << this << endl;
  // this是通过ecx寄存器
  Student::InitStudent(&p1, "peter", "男", 26);
  p1.PrintfStudent("peter", "男", 26);

  Student::InitStudent(&p2, "jingjing", "女", 26); 
  p2.PrintStudent("jingjing", "女", 26);
  p3.PrintStudent("jim", "母", 2);

  p1.PrintfStudent();
  p2.PrintfStudent();
  p3.PrintStudent();

  p1.TestFunc(10);
  p2.TestFunc(10, 20);

  Student* p = &p1;
  p->PrintStudent();

  p = nullptr;
  p->TestFunc();
  p->PrintStudent();
  return 0;
}
