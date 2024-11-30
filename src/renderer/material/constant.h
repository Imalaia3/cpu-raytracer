#pragma once
#include "material.h"
#include "../utils/utils.h"

// Isotropic material, Constant sounds better
class ConstantMaterial : public Material {
public:
    ConstantMaterial() : Material() {}
    
    Ray reflect(Object::CollisionData& collision, Ray& incomingRay) override {
        return Ray(collision.position, glm::sphericalRand(1.0f));
    }
    glm::vec3 color(Object::CollisionData& collision, Ray& outgoingRay, glm::vec3 otherColor = glm::vec3(1.0f)) override {
        return diffuseColor;
    }
    void updateSettings(glm::vec3 diffuse) {
        diffuseColor = diffuse;
    }
    glm::vec3 diffuseColor = glm::vec3(1.0f); // albedo, attenuation, etc
};
