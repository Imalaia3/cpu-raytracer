#include "plane.h"

std::optional<Object::CollisionData> Plane::collides(Ray& ray, double threshold) const {
    const double epsilon = 0.0001;
    // Ray-Plane intersection test:
    // Plane equation: dot(n, (p-p0)) = 0, where n is the normal, p is an arbitrary point and p0 is a point that will always be in the plane
    double denom = glm::dot(m_normal, ray.direction);
    if (glm::abs(denom) < epsilon)
        return {};
    
    double t = glm::dot(m_normal, (m_point - ray.origin)) / denom;
    if (t < threshold) 
        return {};

    CollisionData data = CollisionData {
        .objectName = m_name,
        .t = t,
        .position = ray.point(t),
        .normal = m_normal, // FIXME: plane normal may be bigger than a unit vector
        .material = m_material
    };
    setFaceType(data, ray.direction);
    return data;
}