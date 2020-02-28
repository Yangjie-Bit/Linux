/*===============================================================
 * Copyright (C) . All rights reserved.")"
 * 文件名称：date
 * 创 建 者: yangjie
 * 创建日期: 2020.1.15 
 * 描    述: 
 * =============================================================*/

#include <iostream>
using namespace std;

#if 0
class Date
{
  public:
    Date()
    {
      _year = 1900;
      _month = 1;
      _day = 1;
    }

    Date(int year, int month, int day)
    {
      _year = year;
      _month = month;
      _day = day;
      cout << "Date::Date():" << this << endl;
    }

    void SetDate(int year, int month, int day)
    {
      _year = year;
      _month = month;
      _day = day;
    }

    void PrintDate()
    {
      cout << _year << "-" << _month << "-" << _day << endl;
    }

  private:
    int _year;
    int _month;
    int _day;
};

void TestDate()
{
  Date d1(2020, 1, 15);                 // 调用构造函数
  // d1.SetDate(2020, 1, 15);
  d1.PrintDate();
}

int main()
{
  int a;
  int b = 10;
  int c(20);
  Date d;                               // call Date::Date(int, int, int)
  TestDate();
  // Date d2(2020, 1, 15);
  return 0;
}
#endif

/*
class Date
{
  public:
    // 如果用户没有显示定义任何构造函数, 编译器将会生成一个默认的构造函数
    // 无参的构造函数和全缺省的构造函数不能同时存在
    
    // Date()
    // {}

    // 全缺省的构造函数
    Date(int year = 1900, int month = 1, int day = 1)
    {
      _year = year;
      _month = month;
      _day = day;
    }

    void SetDate(int year, int month, int day)
    {
      _year = year;
      _month = month;
      _day = day;
    }

    void PrintfDate()
    {
      cout << _year << "-" << _month << "-" << _day << endl;
    }

  private:
    int _year;
    int _month;
    int _day;
};

int main()
{
  Date d;
  return 0;
}
*/

class Time
{
  public:
    Time(int hour = 0, int minute = 0, int second = 0)
    {
      _hour = hour;
      _minute = minute;
      _second = second;
      cout << "Time::Time(int, int, int)" << endl;
    }
  private:
    int _hour;
    int _minute;
    int _second;
};

class Date
{
  public:
    Date()
    {
      cout << "Date()" << endl;
    }

    void SetDate(int year, int month, int day)
    {
      _year = year;
      _month = month;
      _day = day;
    }

    void PrintfDate()
    {
      cout << _year << "-" << _month << "-" << _day << endl;
    }

  private:
    int _year;
    int _month;
    int _day;
};

int main()
{
  Date d;                   // call Time(int, int, int)
  return 0;
}
