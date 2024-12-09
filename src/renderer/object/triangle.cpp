#include "triangle.h"
#include <iostream>


std::optional<Object::CollisionData> Triangle::collides(Ray& ray, double threshold) const {
    const double epsilon = 0.0001; // fixme: implement a global epsilon value, must be positive

    glm::dvec3 normalDir = glm::normalize(ray.direction);

    glm::dvec3 e1 = m_points.v2 - m_points.v1;
    glm::dvec3 e2 = m_points.v3 - m_points.v1;
    glm::dvec3 DCrossE2 = glm::cross(normalDir, e2);
    double det = glm::dot(e1, DCrossE2);
    if (glm::abs(det) < epsilon)
        return {};
    
    double invDet = 1.0 / det;
    glm::dvec3 s = ray.origin - m_points.v1;
    double u = invDet * glm::dot(s, DCrossE2);
    //                                         FIXME: only int abs() on here
    if ((u < 0.0 && glm::abs(u) > epsilon) || (u > 1. && abs(u-1.0) > epsilon))
        return {};
    
    glm::dvec3 SCrossE1 = glm::cross(s, e1);
    double v = invDet * glm::dot(normalDir, SCrossE1);
    if ((v < 0.0 && glm::abs(v) > epsilon) || (u + v > 1 && abs(u + v - 1.0) > epsilon))
        return {};
    
    double t = invDet * glm::dot(e2, SCrossE1);
    if (t < threshold)
        return {};

    glm::dvec3 normal = glm::normalize(glm::cross(e1, e2));
    if (m_isBackFace)
        normal = -normal;
    auto data = CollisionData {
        .objectName = m_name ,
        .t = t,
        .position = ray.point(t),
        .normal = normal, // note: does this need to be normalized?
        .material = m_material, 
    };
    setFaceType(data, normalDir);
    return data;
}