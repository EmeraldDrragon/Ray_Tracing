//
// Created by munip on 25/04/25.
//

#ifndef COMPUTER_GRAPHICS_STUDY_VEC3_HPP
#define COMPUTER_GRAPHICS_STUDY_VEC3_HPP

#include <iostream>
#include <cmath>

class vec3
{
private:
  double x_c;
  double y_c;
  double z_c;
public:
  vec3() : x_c{0}, y_c{0}, z_c{0} {}
  vec3(double x, double y, double z) : x_c{x}, y_c{y}, z_c{z} {}
  double x() const {return x_c;}
  double y() const {return y_c;}
  double z() const {return z_c;}

  vec3& operator+=(const vec3& v)
  {
    x_c += v.x_c;
    y_c += v.y_c;
    z_c += v.z_c;
    return *this;
  }

  vec3& operator*=(double t)
  {
    x_c *= t;
    y_c *= t;
    z_c *= t;
    return *this;
  }

  //vector scalar division
  vec3& operator/=(double t)
  {
    return *this *= 1/t;
  }

  double length() const
  {
    return std::sqrt(x_c*x_c + y_c*y_c + z_c*z_c);
  }
};

inline std::ostream& operator<<(std::ostream& out, const vec3& v)
{
  return out << v.x() << ' ' << v.y() << ' ' << v.z();
}

inline vec3 operator+(const vec3& v, const vec3& w)
{
  return vec3(v.x() + w.x(), v.y() + w.y(), v.z() + w.z());
}

inline vec3 operator-(const vec3& v, const vec3& w)
{
  return vec3(v.x()-w.x(), v.y()-w.y(), v.z()-w.z());
}

inline vec3 operator*(double t, const vec3& v)
{
  return vec3(t * v.x(), t * v.y(), t * v.z());
}

inline vec3 operator*(const vec3& v, double t)
{
  return t * v;
}

inline vec3 operator/(const vec3& v, double t)
{
  return (1/t) * v;
}

inline double dot(const vec3& v, const vec3& w)
{
  return v.x() * w.x() + v.y() * w.y() + v.z() * w.z();
}

inline vec3 cross(const vec3& v, const vec3& w)
{
  return vec3(v.y()*w.z() - v.z()*w.y(),
              v.z()*w.x() - v.x()*w.z(),
              v.x()*w.y() - v.y()*w.x());
}

inline vec3 unit_vector(const vec3& v)
{
  return v / v.length();
}

#endif //COMPUTER_GRAPHICS_STUDY_VEC3_HPP
