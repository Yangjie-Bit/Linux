/*===============================================================
 * Copyright (C) . All rights reserved.")"
 * 文件名称：complex
 * 创 建 者: yangjie
 * 创建日期: 2020.1.16
 * 描    述:
 *
 * =============================================================*/

#include <iostream>
using namespace std;

class Complex
{
  public:
    Complex(double real, double image)
      :_real(real)
      ,_image(image)
    {}

    Complex operator+(const Complex& c)const
    {
      // Complex temp(*this);
      // temp._real += c._real;
      // tmep._image += c._image;
      // return temp;
      return Complex(_real + c._real, _image + c._image);
    }

  private:
    double _real;
    double _image;
};

template<class T>
T Add(T left, T right)
{
  return left + right;
}

int main()
{
  Add(1, 2);
  Complex c1(1.0, 2.0);
  Complex c2(3.0, 4.0);
  Add(c1, c2);
  return 0;
}

