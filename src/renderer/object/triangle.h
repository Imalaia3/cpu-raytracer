#pragma once

#pragma once
#include "object.h"

class Triangle : public Object {
public:
    Triangle(glm::dvec3 v1, glm::dvec3 v2, glm::dvec3 v3, std::string objectName, std::shared_ptr<Material> material, FaceType faceType = FaceType::FrontFace) : Object(glm::dvec3(0.0), objectName, material) {
        m_points.v1 = v1;
        m_points.v2 = v2;
        m_points.v3 = v3;
        setType(faceType);
    }
    void setType(FaceType t) { m_isBackFace = (t == FaceType::BackFace); }
    // https://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm
    std::optional<Object::CollisionData> collides(Ray& ray, double threshold = 0.0) const override;
private:
    bool m_isBackFace = false;
    struct {
        glm::dvec3 v1, v2, v3;
    } m_points;
};
