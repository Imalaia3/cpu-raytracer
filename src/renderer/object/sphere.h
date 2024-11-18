#pragma once
#include "object.h"


class Sphere : public Object {
public:
    Sphere(glm::vec3 position, float radius, std::string objectName, glm::vec3 color) : Object(position, objectName, color), m_radius(radius) {}
    float getRadius() const { return m_radius; }
    std::optional<Object::CollisionData> collides(Ray& ray) const override;

protected:
    float m_radius;
};