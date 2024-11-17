#pragma once
#include <glm/glm.hpp>

class Ray {
public:
    Ray() : origin(glm::vec3(0.0f)), direction(glm::vec3(0.0f, 0.0f, 1.0f)) {}
    Ray(glm::vec3 initialOrigin, glm::vec3 initialDirection) : origin(initialOrigin), direction(initialDirection) {}
    glm::vec3 point(float t) { return origin + direction*t; }
    glm::vec3 origin, direction;
};