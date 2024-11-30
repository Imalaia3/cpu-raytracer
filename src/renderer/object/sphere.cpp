#include "sphere.h"

std::optional<Sphere::CollisionData> Sphere::collides(Ray& ray, float threshold) const {
    glm::vec3 oMinusC = ray.origin - m_position;
    float a = glm::dot(ray.direction, ray.direction);
    float b = 2.0f*glm::dot(ray.direction, oMinusC);
    float c = glm::dot(oMinusC, oMinusC) - m_radius*m_radius;
    float discriminant = b*b - 4*a*c;
    if (discriminant < 0)
        return {};
    
    // if discriminant > 0 get closest result that is above the threshold
    float d = (-b - glm::sqrt(discriminant)) / 2*a;
    if (d < threshold) {
        d = (-b + glm::sqrt(discriminant)) / 2*a;
        if (d < threshold)
            return {};
    }
    return CollisionData {
        .objectName = m_name,
        .t = d,
        .position = ray.point(d),
        .normal = glm::normalize(ray.point(d) - m_position), // Point - Center
        .material = m_material
    };
}