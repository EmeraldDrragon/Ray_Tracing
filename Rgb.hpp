//
// Created by munip on 25/04/25.
//

#ifndef COMPUTER_GRAPHICS_STUDY_RGB_HPP
#define COMPUTER_GRAPHICS_STUDY_RGB_HPP

#include <iostream>

class rgb
{
private:
  double red;
  double green;
  double blue;
public:
  rgb() : red{0}, green{0}, blue{0} {}
  rgb(double r, double g, double b) : red{r}, green{g}, blue{b} {}
  double r() const {return red;}
  double g() const {return green;}
  double b() const {return blue;}

  void r(double value)
  {
    red = value;
  }
  void g(double value)
  {
    green = value;
  }
  void b(double value)
  {
    blue = value;
  }

  rgb& operator+=(const rgb& v)
  {
    red += v.red;
    green += v.green;
    blue += v.blue;
    return *this;
  }

  rgb& operator*=(double t)
  {
    red *= t;
    green *= t;
    blue *= t;
    return *this;
  }

  //vector scalar division
  rgb& operator/=(double t)
  {
    return *this *= 1/t;
  }
};

inline std::ostream& operator<<(std::ostream& out, const rgb& v)
{
  return out << v.r() << ' ' << v.g() << ' ' << v.b();
}

inline rgb operator+(const rgb& v, const rgb& w)
{
  return rgb(v.r() + w.r(), v.g() + w.g(), v.b() + w.b());
}

inline rgb operator-(const rgb& v, const rgb& w)
{
  return rgb(v.r()-w.r(), v.g()-w.g(), v.b()-w.b());
}

inline rgb operator*(double t, const rgb& v)
{
  return rgb(t * v.r(), t * v.g(), t * v.b());
}

inline rgb operator*(const rgb& v, double t)
{
  return t * v;
}

inline rgb operator/(const rgb& v, double t)
{
  return (1/t) * v;
}

inline double dot(const rgb& v, const rgb& w)
{
  return v.r() * w.r() + v.g() * w.g() + v.b() * w.b();
}

inline rgb cross(const rgb& v, const rgb& w)
{
  return rgb(v.g()*w.b() - v.b()*w.g(),
              v.b()*w.r() - v.r()*w.b(),
              v.r()*w.g() - v.g()*w.r());
}

inline rgb operator*(const rgb& v, const rgb& w)
{
  return rgb(v.r() * w.r(), v.g() * w.g(), v.b() * w.b());
}

#endif //COMPUTER_GRAPHICS_STUDY_RGB_HPP
