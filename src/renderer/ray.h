#pragma once
#include <glm/glm.hpp>

class Ray {
public:
    Ray() : origin(glm::dvec3(0.0)), direction(glm::dvec3(0.0, 0.0, 1.0)) {}
    Ray(glm::dvec3 initialOrigin, glm::dvec3 initialDirection) : origin(initialOrigin), direction(initialDirection) {}
    Ray(glm::dvec3 initialOrigin, glm::dvec3 initialDirection, uint8_t data) : origin(initialOrigin), direction(initialDirection), additionalData(data) {}
    glm::dvec3 point(double t) { return origin + direction*t; }
    glm::dvec3 origin, direction;
    uint8_t additionalData = 0; // Used for debugging
};