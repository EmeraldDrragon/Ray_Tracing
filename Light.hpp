//
// Created by munip on 29/04/25.
//

#ifndef COMPUTER_GRAPHICS_STUDY_LIGHT_HPP
#define COMPUTER_GRAPHICS_STUDY_LIGHT_HPP

#include "Vec3.hpp"
#include "Rgb.hpp"

class Light
{
public:
  rgb color;
  double intensity;
  Light(const rgb& col, double inten) : color{col}, intensity{inten} {}
  virtual ~Light() = default;
};

class PointLight : public Light
{
public:
  vec3 position;
  PointLight(const vec3& pos, const rgb& col, double inten) : Light(col, inten),  position{pos} {}
};

class AmbientLight : public Light
{
public:
  AmbientLight(const rgb& col, double inten) : Light(col, inten) {}
};


#endif //COMPUTER_GRAPHICS_STUDY_LIGHT_HPP
