#include "plane.h"

std::optional<Object::CollisionData> Plane::collides(Ray& ray, float threshold) const {
    const float epsilon = 0.0001f;
    // Ray-Plane intersection test:
    // Plane equation: dot(n, (p-p0)) = 0, where n is the normal, p is an arbitrary point and p0 is a point that will always be in the plane
    float denom = glm::dot(m_normal, ray.direction);
    if (glm::abs(denom) < epsilon)
        return {};
    
    float t = glm::dot(m_normal, (m_point - ray.origin)) / denom;
    if (t < threshold) 
        return {};

    return CollisionData {
        .objectName = m_name,
        .t = t,
        .position = ray.point(t),
        .normal = m_normal, // FIXME: plane normal may be bigger than a unit vector
        .material = m_material
    };
}