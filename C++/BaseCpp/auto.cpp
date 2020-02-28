/*===============================================================
 * Copyright (C) . All rights reserved.")"
 * 文件名称：auto (auto关键字的使用)
 * 创 建 者: yangjie
 * 创建日期: 2020.1.15
 * 描    述:
 * =============================================================*/
#include <iostream>
#include <map>
#include <string>
using namespace std;

#if 0
int TestAuto()
{
  return 10;
}

int main()
{  
  int a = 10;
  auto b = 12.34;
  auto c = TestAuto();
  // auto e; auto在定义变量时, 必须要进行初始化
  cout << typeid(a).name() << endl;
  cout << typeid(b).name() << endl;
  cout << typeid(c).name() << endl;
  return 0;
}
#endif

#if 0
int main()
{
  std::map<std::string, int> m 
  {
    {"apple", 3},
    {"banana", 2},
    {"peach", 2}
  };
  // c++98
  // std::map<std::string, int> :: iterator it = m. begin();
  auto it = m.begin();
  while(it !=m.end())
  {
    cout << it->first << "-->" << it->second << endl;
    ++it;
  }
  cout << endl;
  return 0;
}
#endif

int main()
{
  int array[10] = {0, 1, 2, 3, 4 ,5 , 6 , 7, 8 ,9 };
  for(auto& e : array)
  {
    e *= 2;
  }
  for(auto& e : array)
  {
    cout << e << " ";
  }
  cout << endl;
  return 0;
}
