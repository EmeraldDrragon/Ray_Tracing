//
// Created by munip on 25/04/25.
//

#ifndef COMPUTER_GRAPHICS_STUDY_RENDERER_HPP
#define COMPUTER_GRAPHICS_STUDY_RENDERER_HPP

#include <iostream>
#include <fstream>
#include "Vec3.hpp"
#include "Rgb.hpp"
#include <vector>
#include "Ray.hpp"
#include "Surface.hpp"
#include "Interval.hpp"
#include "constants.hpp"
#include "Light.hpp"

class Renderer
{
private:
  //output file
  std::ofstream out_file;

  //image
  int image_width;
  int image_height;
  std::vector<std::vector<rgb>> image;

  //camera
  vec3 camera_center;
  double focal_length;

  //ssaa
  double pixel_samples_scale;

  //viewport
  double viewport_height;
  double viewport_width;
  vec3 pixel_delta_u;
  vec3 pixel_delta_v;
  vec3 viewport_pixel_00_location;

  //world
  SurfaceGroup world;

  //lights
  std::vector<PointLight> point_lights;
  std::vector<AmbientLight> ambient_lights;

public:
  //ssaa
  int samples_per_pixel = 100;

  //constructor
  Renderer(std::string file_path, int width, int height, vec3 camera, double focal_length, SurfaceGroup& world) :
    image_width{width}, image_height{height}, focal_length{focal_length}, world{world}
  {
    pixel_samples_scale = 1.0 / samples_per_pixel;
    out_file.open(file_path);
    image.resize(image_height, std::vector<rgb>(image_width));
    camera_center = camera;

    viewport_height = 2.0;
    viewport_width = viewport_height * (double(image_width)/image_height);
    auto viewport_u = vec3(viewport_width, 0, 0);
    auto viewport_v = vec3(0,-viewport_height, 0);
    pixel_delta_u = viewport_u / image_width;
    pixel_delta_v = viewport_v / image_height;
    auto viewport_upper_left = camera_center - vec3(0,0,focal_length)-viewport_u/2-viewport_v/2;
    viewport_pixel_00_location = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
  }

  vec3 sampleSquare() const;

  Ray getRay(int i, int j) const;

  void pixelRay(int y, int x);

  void render();

  void imageToPpm();

  rgb rayColor(const Ray& r);

  void addPointLight(const PointLight& light)
  {
    point_lights.push_back(light);
  }
  void addAmbientLight(const AmbientLight& light)
  {
    ambient_lights.push_back(light);
  }
  rgb shade(const Ray& ray, const HitRecord& hit) const;
};




#endif //COMPUTER_GRAPHICS_STUDY_RENDERER_HPP
