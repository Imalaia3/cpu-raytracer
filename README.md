# CPU Raytracer
A simple CPU based raytracer (or a path tracer) that aims to be feature rich and relatively fast. The plan is to support multi-threading. It will almost always be slower than a GPU raytracer using compute shaders, but GPU programming is relatively hard to iterate over.

## Planned Features

- [ ] Diffuse objects
- [ ] Reflective/Metallic objects
- [ ] Emissive objects
- [ ] Normal maps / Roughness maps / Color (albedo) maps
- [ ] Refraction
- [ ] Bounding Volume Hierarchies
- [ ] Multiple object types ( Spheres, Quads, Planes, etc )
- [ ] Volumetric objects ( Smoke, Fog, etc )
- [ ] HDRIs
- [ ] Bloom
- [ ] Multithreaded rendering
- [ ] Keyframing / Animations (?)
- [ ] Use double precision instead of single precision floats

## Compilation
To compile this project CMake, SDL2 and GLM must be installed. It is assumed that a Linux environment is being used. Support for Windows may be implemented in the future
- [Install CMake](https://cmake.org/download/)
- [Install SDL2](https://wiki.libsdl.org/SDL2/Installation)
- [Build & Install GLM](https://github.com/g-truc/glm/tree/master?tab=readme-ov-file#build-and-install)

To compile the project the following commands should be executed:
```bash
mkdir build
cd build
cmake ..
make
```
After compiling an executable named `Raytracer` should have been generated in the `build/` directory.

## Acknowledgments
- Raytracing In A Weekend series: https://raytracing.github.io/ (Outlines what a proper raytracer outght to have)
- Blender Cycles Renderer Source Code: https://github.com/blender/cycles (Optimization techniques)
- Computer Graphics From Scratch: https://gabrielgambetta.com/computer-graphics-from-scratch/
- Physically Based Rendering: From Theory To Implementation: https://pbr-book.org/4ed/contents
