#pragma once
#include "../object/object.h"
#include "../ray.h"
#include <glm/glm.hpp>

class Material {
public:
    Material() {}
    // reflect / scatter
    virtual Ray reflect(Object::CollisionData& collision, Ray& incomingRay) = 0;
    // get pixel color. outgoingRay is the ray that is returned from reflect(), otherColor is the color that might have originated from a raytrace
    virtual glm::vec3 color(Object::CollisionData& collision, Ray& outgoingRay, glm::vec3 otherColor = glm::vec3(1.0f)) = 0;
};