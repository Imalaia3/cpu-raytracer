#include "sphere.h"

std::optional<Sphere::CollisionData> Sphere::collides(Ray& ray, double threshold) const {
    glm::dvec3 oMinusC = ray.origin - m_position;
    double a = glm::dot(ray.direction, ray.direction);
    double b = 2.0*glm::dot(ray.direction, oMinusC);
    double c = glm::dot(oMinusC, oMinusC) - m_radius*m_radius;
    double discriminant = b*b - 4*a*c;
    if (discriminant < 0)
        return {};
    
    // if discriminant > 0 get closest result that is above the threshold
    double d = (-b - glm::sqrt(discriminant)) / 2*a;
    if (d < threshold) {
        d = (-b + glm::sqrt(discriminant)) / 2*a;
        if (d < threshold)
            return {};
    }

    CollisionData data =  CollisionData {
        .objectName = m_name,
        .t = d,
        .position = ray.point(d),
        .normal = glm::normalize(ray.point(d) - m_position), // Point - Center
        .material = m_material
    };
    setFaceType(data, ray.direction);

    return data;
}