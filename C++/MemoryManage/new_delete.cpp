/*===============================================================
 * Copyright (C) . All rights reserved.")"
 * 文件名称：new_delete
 * 创 建 者: yangjie
 * 创建日期: 2020.1.16
 * 描    述:
 *
 * =============================================================*/

#include <iostream>
using namespace std;

class Date
{
  public: 
    // 全缺省的构造函数
    Date(int year = 1900, int month = 1, int day =1)
      :_year(year)
      ,_month(month)
      ,_day(day)
    {
      cout << "Date()" << endl;
    }

    Date(const Date& d)
      :_year(d._year)
      ,_month(d._month)
      ,_day(d._day)
    {}

    ~Date()
    {
      cout << "~Date()" << endl;
    }

  private:
    int _year;
    int _month;
    int _day;
};

int main()
{
  Date* pd1 = (Date*) malloc (sizeof(Date));
  free(pd1);

  Date* pd2 = new Date;
  delete pd2;

  int a[10];

  Date* pd3 = new Date[10];
  delete[] pd3;

  int* p1 = new int;
  int* p2 = new int(10);
  int* p3 = new int[10];
  int* p4 = new int[10]{0,1,2,3,4,5,6,7,8,9};

  delete p1;
  delete p2;
  delete[] p3;
  delete[] p4;
  return 0;
}
