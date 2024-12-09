#pragma once
#include <glm/glm.hpp>
#include <stdexcept>
#include <optional>
#include "ray.h"
#include "world.h"
#include "material/generic.h"

class Camera {
public:
    Camera() {}
    Camera(glm::dvec3 position, double focalLength, double viewWidth, double viewHeight, uint32_t imgWidth, uint32_t imgHeight, uint32_t samplesPerPixel);
    std::vector<glm::dvec3> render(World& world);
    void setCameraBounceLimit(uint32_t bounces) { m_maxBounces = bounces; }
private:
    std::optional<Object::CollisionData> getClosestObjectInWorld(Ray& ray, World& world);
    glm::dvec3 getPixelValue(World& world, Ray initialRay, uint32_t bouncesLeft);
    glm::dvec3 m_position; // camera center
    double m_focalLength;
    double m_width, m_height; // only correlates with the aspect ratio of the display
    double m_pixelDx, m_pixelDy; // how much of viewWidth & -viewHeight correspond to display
    glm::dvec3 m_topLeft; // top left corner of the camera.
    uint32_t m_imageWidth, m_imageHeight;
    bool m_initialized = false; // False when default constructor used, must be true to render.
    uint32_t m_maxBounces = 1;
    uint32_t m_samplesPerPixel = 1;
};