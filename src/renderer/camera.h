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
    Camera(glm::dvec3 position, double fovDeg, uint32_t imgWidth, uint32_t imgHeight, uint32_t samplesPerPixel);
    std::vector<glm::dvec3> render(World& world);
    void setCameraBounceLimit(uint32_t bounces) { m_maxBounces = bounces; }
    void lookAt(glm::dvec3 v) {
        m_camLookAt = v;
        calculateVectors();
    }
    void setPosition(glm::dvec3 v) {
        m_position = v;
        calculateVectors();
    }
    void setWorldUpVector(glm::dvec3 up) {
        m_worldUp = up;
        calculateVectors();
    }
    void setFOV(double degrees) { m_fovDeg = degrees; }
private:
    std::optional<Object::CollisionData> getClosestObjectInWorld(Ray& ray, World& world);
    glm::dvec3 getPixelValue(World& world, Ray initialRay, uint32_t bouncesLeft);
    void calculateVectors();
    glm::dvec3 m_position; // camera center
    glm::dvec3 m_camRight, m_camForward, m_camUp;
    glm::dvec3 m_worldUp;
    glm::dvec3 m_camLookAt;
    double m_fovDeg;
    double m_exposure = 0.5; // todo: add to settings!
    glm::dvec3 m_topLeft; // top left corner of the camera.
    uint32_t m_imageWidth, m_imageHeight;
    bool m_initialized = false; // False when default constructor used, must be true to render.
    uint32_t m_maxBounces = 1;
    uint32_t m_samplesPerPixel = 1;
};