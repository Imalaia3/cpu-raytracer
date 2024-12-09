#pragma once
#include "../ray.h"
#include "../object/object.h"
#include <glm/glm.hpp>

class Material {
public:
    Material() {}
    // reflect / scatter
    virtual Ray reflect(Object::CollisionData& collision, Ray& incomingRay) = 0;
    // get pixel color. outgoingRay is the ray that is returned from reflect(), otherColor is the color that might have originated from a raytrace
    virtual glm::dvec3 color(Object::CollisionData& collision, Ray& outgoingRay, glm::dvec3 otherColor = glm::dvec3(1.0)) = 0;
};