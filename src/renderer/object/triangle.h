#pragma once

#pragma once
#include "object.h"

class Triangle : public Object {
public:
    Triangle(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, std::string objectName, std::shared_ptr<Material> material) : Object(glm::vec3(0.0f), objectName, material) {
        m_points.v1 = v1;
        m_points.v2 = v2;
        m_points.v3 = v3;
    }
    // https://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm
    std::optional<Object::CollisionData> collides(Ray& ray, float threshold = 0.0f) const override;
private:
    struct {
        glm::vec3 v1, v2, v3;
    } m_points;
};
