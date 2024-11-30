#pragma once
#include "object.h"

class Sphere : public Object {
public:
    Sphere(glm::vec3 position, float radius, std::string objectName, std::shared_ptr<Material> material) : Object(position, objectName, material), m_radius(radius) {}
    float getRadius() const { return m_radius; }
    std::optional<Object::CollisionData> collides(Ray& ray, float threshold = 0.0f) const override;
protected:
    float m_radius;
};