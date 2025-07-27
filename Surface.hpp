//
// Created by munip on 28/04/25.
//

#ifndef COMPUTER_GRAPHICS_STUDY_SURFACE_HPP
#define COMPUTER_GRAPHICS_STUDY_SURFACE_HPP

#include <iostream>
#include <fstream>
#include "Vec3.hpp"
#include "Renderer.hpp"
#include "Rgb.hpp"
#include "Ray.hpp"
#include <string>
#include <memory>
#include <vector>
#include "constants.hpp"
#include "Interval.hpp"

using std::make_shared;
using std::shared_ptr;

class Material
{
public:
  rgb color;
  Material(const rgb& col) : color{col} {}
};

class HitRecord
{
public:
  vec3 point; //point that was hit
  vec3 normal; //surface normal at the point
  double t; //coordinate of hit point along the ray
  bool front_face;
  shared_ptr<Material> material;

  void setFaceNormal(const Ray& r, const vec3& outward_normal)
  {
    front_face = dot(r.direction(), outward_normal) < 0;
    normal = front_face ? outward_normal : (-1)*outward_normal;
  }
};

class Surface
{
public:
  virtual ~Surface() = default;
  virtual bool hit(const Ray& r, Interval ray_t, HitRecord& rec) const = 0;
};


class SurfaceGroup : public Surface
{
public:
  std::vector<shared_ptr<Surface>> objects;

  SurfaceGroup() {}
  SurfaceGroup(shared_ptr<Surface> object) { add(object);}
  void clear() {objects.clear();}
  void add(shared_ptr<Surface> object)
  {
    objects.push_back(object);
  }

  bool hit(const Ray& r, Interval ray_t, HitRecord& rec) const override
  {
    HitRecord temp_rec;
    bool hit_anything = false;
    auto closest_so_far = ray_t.max;
    for(const auto& object : objects)
    {
      if(object->hit(r, Interval(ray_t.min, closest_so_far), temp_rec))
      {
        hit_anything = true;
        closest_so_far = temp_rec.t;
        rec = temp_rec;
      }
    }
    return hit_anything;
  }

};


class Sphere : public Surface
{
private:
  vec3 center;
  double radius;
  shared_ptr<Material> material;
public:
  Sphere(const vec3& center, double radius, shared_ptr<Material> mat)
    : center{center}, radius{std::fmax(0, radius)}, material{mat} {}
  bool hit(const Ray& r, Interval ray_t, HitRecord& rec) const override
  {
    vec3 oc = r.origin() - center;
    auto a = dot(r.direction(), r.direction());
    auto b = 2.0 * dot(r.direction(), oc);
    auto c = dot(oc, oc) - radius*radius;
    auto discriminant = b * b - 4 * a * c;
    if(discriminant < 0)
    {
      return false;
    }
    auto sqrt_d = std::sqrt(discriminant);

    auto root = (-b - sqrt_d) / (2.0 * a);
    if(!ray_t.surrounds(root))
    {
      root = (-b + sqrt_d) / (2.0 * a);
      if(!ray_t.surrounds(root))
      {
        return false;
      }
    }
    rec.t = root;
    rec.point = r.evaluate(rec.t);
    vec3 outward_normal = (rec.point - center) / radius;
    rec.setFaceNormal(r, unit_vector(outward_normal));
    rec.material = material;
    return true;
  }

};


#endif //COMPUTER_GRAPHICS_STUDY_SURFACE_HPP
