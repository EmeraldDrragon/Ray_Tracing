#include <iostream>
#include <fstream>
#include "Vec3.hpp"
#include "Renderer.hpp"
#include "Rgb.hpp"
#include "Ray.hpp"
#include <string>
#include "Surface.hpp"
#include "Interval.hpp"
#include "constants.hpp"


int main()
{
  //ppm file
  std::string ppm_file_path = "C:\\Users\\munip\\Desktop\\Salamat\\Programming\\JetBrains codes\\Clion\\C++\\Computer_Graphics_Study\\image.ppm";

  //image
  auto aspect_ratio = 16.0/9.0;
  int image_width = 400;
  int image_height = int(image_width / aspect_ratio);
  image_height = (image_height < 1) ? 1 : image_height;

  //camera
  auto focal_length = 1.0;
  auto camera_center = vec3(0,0,0);

  Material default_material(rgb(31.0/255.0,254.0/255.0,183.0/255.0));
  Material ground_material(rgb(0.5, 0.5, 0.5));

  //world
  SurfaceGroup world;
  world.add(make_shared<Sphere>(vec3(0,0,-1),0.5,make_shared<Material>(default_material)));
  world.add(make_shared<Sphere>(vec3(0,-100.5,-1),100,make_shared<Material>(ground_material)));

  //render
  Renderer render_inst(ppm_file_path, image_width, image_height, camera_center, focal_length, world);
  render_inst.addPointLight(PointLight(vec3(-1,1,1), rgb(1,1,1),1.0));
  render_inst.addAmbientLight(AmbientLight(rgb(1,1,1),0.1));

  render_inst.render();
  render_inst.imageToPpm();
}