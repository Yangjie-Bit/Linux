/*===============================================================
 * Copyright (C) . All rights reserved.")"
 * 文件名称：OperatorCharacterOverloaded
 * 创 建 者: yangjie
 * 创建日期: 2020.1.15
 * 描    述: 
 *
 * =============================================================*/

#include <iostream>
using namespace std;

#if 0
class Date()
{
  public:
    // 全缺省的构造函数
    Date(int year = 1900, int month = 1, int day = 1)
    {
      _year = year;
      _month = month;
      _day = day;
    }

    Date(const Date& d)
    {
      _year = d._year;
      _month = d._month;
      _day = d._day;
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

    bool IsSame(const Date& d)
    {
      return _year == d._year && 
           _month == d._month &&
           _day == d._day;
    }

    // d1 = d2 = d3;
    Date& operator = (const Date& d)
    {
      if(this != &d)
      {
        _year = d._year;
        _month = d._month;
        _day = d._day;
      }
      return *this;
    }

    bool operator(const Date& d)
    {
      return _year == d._year && 
           _month == d._month &&
           _day == d._day;
    }

    bool operator!=(const Date& d)
    {
      return !(*this == a);
    }

    Date operator+(int days)
    {
      Date temp(*this);
      temp._day -= days;
      return temp;
    }

  private:
    int _year;
    int _month;
    int _day;
}
#endif

/*
// 运算符重载-->函数
bool operatot == (const Date& left, const Date& right)
{
  return left._year == right._year &&
    left._month == right._month &&
    left._day == right._day;
}

void operator@(const Date& d)
{}

int operator+(const Date& d)
{
  return left + right;
}
*/

#if 0
int main()
{
  int a = 10;
  int b = 10;
  int c = 100;

  a = b = c;
  Date d1(2020, 1, 15);
  Date d2(2020, 1, 16);
  Date d3(2020, 1, 17);

  // d1 = d2;
  // d1.operator = (d2);                        // Date::operator = (&d1, d2);
  // d1 = d2 = d3;
  // d1 = (d2 = d3);
  d1.operator = (d2.operator = (d3));
  d1 = d1;
  Date& d4 = d1;
  d4 = d1;
  return 0;
}
#endif

#if 0
class Date
{
  public:
    // 全缺省的构造函数
    Date(int year = 1900, int month = 1, int day = 1)
    {
      _year = year;
      _month = year;
      _day = month;
    }

    void PrintDate()
    {
      cout << _year << "-" << month << "-" << _day << endl;
    }

    // 前置++
    Date& operator++()
    {
      _day += 1;
      return *this;
    }

    // 后置++
    Date operator++(int)
    {
      Date temp(*this);
      _day += 1;
      return temp;
    }

    // 前置--
    Date& operator--()
    {
      _day -= 1;
      return (*this);
    }

    // 后置--
    Date operator--(int)
    {
      Date temp(*this);
      _day -= 1;
      return temp;
    }
  private:
    int _year;
    int _month;
    int _day;
};

int main()
{
  int a = 10;
  a++;
  ++a;

  Date d1(2020,1,16);
  Date d2;

  d2 = ++d1;
  d2 = d1++;
  return 0;
}
#endif

#if 0
class Date
{
  public:
    Date(int year = 1900, int month = 1, int day = 1)
    {
      _year = year;
      _month = month;
      _day = day;
    }
  
    // const成员函数中不能修改成员变量
    // const修饰this指针, 表明当前对象中的内容不允许被修改
    // cosnt Date* const
    void PrintDate()const
    {
      // this->_day = 1;
      cout << _year << "-" << _month << "-" << _day << endl;
    }

    // Date* const
    void PrintDate()
    {
      _day = 1;
      cout << _year << "-" << _month << "-" << _day << endl;
    }

    bool operator == (const Date& d)const
    {
      // _day = 1;
      // d._day = 1;
      return _year == d._year &&
        _month == d._month &&
        _day == d._day;
    }

    Date* operator&()
    {
      return this;
    }

  private:
    int _year;
    int _month;
    int _day;
};

int main()
{
  Date d(2020, 1, 16);
  d.PrintDate();

  cout << &d << endl;
  const Date cd(2020, 1, 16);
  cout << &cd << endl;
  return 0;
}
#endif


