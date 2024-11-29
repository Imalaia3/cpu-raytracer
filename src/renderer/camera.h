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
    Camera(glm::vec3 position, float focalLength, float viewWidth, float viewHeight, uint32_t imgWidth, uint32_t imgHeight, uint32_t samplesPerPixel);
    std::vector<glm::vec3> render(World& world);
    void setCameraBounceLimit(uint32_t bounces) { m_maxBounces = bounces; }
private:
    std::optional<Object::CollisionData> getClosestObjectInWorld(Ray& ray, World& world);
    glm::vec3 getPixelValue(World& world, Ray initialRay, uint32_t bouncesLeft);
    glm::vec3 m_position; // camera center
    float m_focalLength;
    float m_width, m_height; // only correlates with the aspect ratio of the display
    float m_pixelDx, m_pixelDy; // how much of viewWidth & -viewHeight correspond to display
    glm::vec3 m_topLeft; // top left corner of the camera.
    uint32_t m_imageWidth, m_imageHeight;
    bool m_initialized = false; // False when default constructor used, must be true to render.
    uint32_t m_maxBounces = 1;
    uint32_t m_samplesPerPixel = 1;
};