//
// Created by munip on 25/04/25.
//

#include "Renderer.hpp"
#include "Rgb.hpp"
#include "Ray.hpp"
#include "constants.hpp"
#include <cmath>


rgb Renderer::shade(const Ray& ray, const HitRecord& hit) const
{
  rgb color(0,0,0);
  const double kd = 0.8; // Diffuse coefficient
  const double ks = 0.2; // Specular coefficient
  const double shininess = 32.0; // Shininess exponent

  for(const auto& ambient : ambient_lights)
  {
    color += hit.material->color * ambient.color * ambient.intensity;
  }

  vec3 v = unit_vector((-1)*ray.direction());

  for(const auto& light : point_lights)
  {
    vec3 light_dir = unit_vector(light.position - hit.point);
    Ray shadow_ray(hit.point + hit.normal * 0.001, light_dir);
    HitRecord shadow_rec;
    if(!world.hit(shadow_ray, Interval(0.001, infinity), shadow_rec))
    {
      double diffuse = std::max(0.0, dot(hit.normal, light_dir));
      vec3 h = unit_vector(light_dir + v);
      double specular = std::pow(std::max(0.0, dot(hit.normal,h)),shininess);

      color += hit.material->color * light.color * light.intensity * (diffuse * kd + specular * ks);
    }
  }
  return color;
}



rgb Renderer::rayColor(const Ray& r)
{
  HitRecord rec;
  if(world.hit(r, Interval(0.001, infinity), rec))
  {
    return shade(r, rec); // <-- Just call shade()!
  }

  // Background gradient
  vec3 unit_direction = unit_vector(r.direction());
  auto a = 0.5 * (unit_direction.y() + 1.0);
  return (1.0 - a) * rgb(1.0, 1.0, 1.0) + a * rgb(0.5, 0.7, 1.0);
}

vec3 Renderer::sampleSquare() const
{
  return vec3(random_double() - 0.5, random_double() - 0.5, 0);
}

Ray Renderer::getRay(int i, int j) const
{
  auto offset = sampleSquare();
  auto pixel_sample = viewport_pixel_00_location + ((i+offset.x())*pixel_delta_u) + ((j+offset.y())*pixel_delta_v);
  auto ray_origin = camera_center;
  auto ray_direction = pixel_sample - ray_origin;
  return Ray(ray_origin, ray_direction);
}

void Renderer::pixelRay(int y, int x)
{
  auto viewport_pixel_center = viewport_pixel_00_location + (x * pixel_delta_u) + (y * pixel_delta_v);
  auto ray_direction = viewport_pixel_center - camera_center;
  Ray r(camera_center, unit_vector(ray_direction));

  rgb pixel_color = rayColor(r);
  image[y][x] = pixel_color;
}

void Renderer::render()
{
  for(int j = 0; j < image_height; j++)
  {
    for(int i = 0; i < image_width; i++)
    {
      rgb pixel_color(0,0,0);
      for(int sample = 0; sample < samples_per_pixel; sample++)
      {
        Ray r = getRay(i,j);
        pixel_color += rayColor(r);
      }
      image[j][i] = pixel_samples_scale * pixel_color;
    }
  }
}

void color(std::ostream& out, const rgb& pixel)
{
  auto r = pixel.r();
  auto g = pixel.g();
  auto b = pixel.b();

  static const Interval intensity(0.000,0.999);

  int ir = static_cast<int>(255.999 * intensity.clamp(r));
  int ig = static_cast<int>(255.999 * intensity.clamp(g));
  int ib = static_cast<int>(255.999 * intensity.clamp(b));
  out << ir << ' ' << ig << ' ' << ib << '\n';
}

void Renderer::imageToPpm()
{
  out_file << "P3\n" << image_width << ' ' << image_height << "\n255\n";
  for (int j = 0; j < image_height; j++)
  {
    for (int i = 0; i < image_width; i++)
    {
      color(out_file, image[j][i]);
    }
  }
}
