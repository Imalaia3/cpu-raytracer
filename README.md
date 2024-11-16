# CPU Raytracer
A simple CPU based raytracer (or a path tracer) that aims to be feature rich and relatively fast. The plan is to support multi-threading. It will almost always be slower than a GPU raytracer using compute shaders, but GPU programming is relatively hard to iterate over.

## Planned Features

Diffuse objects
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

## Acknowledgments
- Raytracing In A Weekend series: https://raytracing.github.io/ (Outlines what a proper raytracer outght to have)
- Blender Cycles Renderer Source Code: https://github.com/blender/cycles (Optimization techniques)
