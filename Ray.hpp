//
// Created by munip on 26/04/25.
//

#ifndef COMPUTER_GRAPHICS_STUDY_RAY_HPP
#define COMPUTER_GRAPHICS_STUDY_RAY_HPP

#include "Vec3.hpp"
class Ray
{
private:
  vec3 o;
  vec3 d;
public:
  Ray() {}
  Ray(const vec3& origin, const vec3& direction) : o{origin},d{direction} {}
  const vec3& origin() const {return o;}
  const vec3& direction() const {return d;}

  vec3 evaluate(double t) const
  {
    return o + t * d;
  }
};

#endif //COMPUTER_GRAPHICS_STUDY_RAY_HPP
