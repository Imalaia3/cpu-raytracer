#include "triangle.h"
#include <iostream>


std::optional<Object::CollisionData> Triangle::collides(Ray& ray, float threshold) const {
    const float epsilon = 0.0001f; // fixme: implement a global epsilon value, must be positive

    glm::vec3 normalDir = glm::normalize(ray.direction);

    glm::vec3 e1 = m_points.v2 - m_points.v1;
    glm::vec3 e2 = m_points.v3 - m_points.v1;
    glm::vec3 DCrossE2 = glm::cross(normalDir, e2);
    float det = glm::dot(e1, DCrossE2);
    if (glm::abs(det) < epsilon)
        return {};
    
    float invDet = 1.0f / det;
    glm::vec3 s = ray.origin - m_points.v1;
    float u = invDet * glm::dot(s, DCrossE2);
    //                                         FIXME: only int abs() on here
    if ((u < 0.0f && glm::abs(u) > epsilon) || (u > 1.f && abs(u-1.0f) > epsilon))
        return {};
    
    glm::vec3 SCrossE1 = glm::cross(s, e1);
    float v = invDet * glm::dot(normalDir, SCrossE1);
    if ((v < 0.0f && glm::abs(v) > epsilon) || (u + v > 1 && abs(u + v - 1.0f) > epsilon))
        return {};
    
    float t = invDet * glm::dot(e2, SCrossE1);
    if (t < threshold)
        return {};

    auto data = CollisionData {
        .objectName = m_name ,
        .t = t,
        .position = ray.point(t),
        .normal = glm::normalize(glm::cross(e1, e2)), // note: does this need to be normalized?
        .material = m_material, 
    };
    setFaceType(data, normalDir);
    return data;
}