#pragma once
#include "object.h"

class Sphere : public Object {
public:
    Sphere(glm::dvec3 position, double radius, std::string objectName, std::shared_ptr<Material> material) : Object(position, objectName, material), m_radius(radius) {}
    double getRadius() const { return m_radius; }
    std::optional<Object::CollisionData> collides(Ray& ray, double threshold = 0.0) const override;
protected:
    double m_radius;
};