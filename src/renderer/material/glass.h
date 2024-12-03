#pragma once
#include "material.h"
#include <iostream>

// Reflective + Glass-Like material
class Glass : public Material {
public:
    Glass() : Material() {};

    glm::vec3 color(Object::CollisionData& collision, Ray& outgoingRay, glm::vec3 otherColor = glm::vec3(1.0f)) override {
        return glm::vec3(1.0f); // this material doesn't affect light color, only bounced ray direction 
    }

    Ray reflect(Object::CollisionData& collision, Ray& incomingRay) override {
        // Not Implemented
        std::cout << "Glass::reflect has not been implemented!\n";
        return Ray(collision.position, incomingRay.direction);
    }
    
    float indexOfRefraction; // aka IOR
private:
};