#pragma once
#include "object.h"

// https://graphics.cs.kuleuven.be/publications/LD05ERQIT/LD05ERQIT_paper.pdf
// TODO: Make edges relative and add a world position
class Plane : public Object {
public:
    // normal: normal vector of the plane, point: a point that falls within the plane
    Plane(glm::dvec3 normal, glm::dvec3 point, std::string objectName, std::shared_ptr<Material> material) :
        Object(m_point, objectName, material), m_point(point), m_normal(normal) { /* Note: m_point = m_position*/ }
    std::optional<Object::CollisionData> collides(Ray& ray, double threshold = 0.0) const override;
private:
    glm::dvec3 m_normal, m_point;
};