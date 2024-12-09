#pragma once
#include "material.h"
#include "../utils/utils.h"

// Isotropic material, Constant sounds better
class ConstantMaterial : public Material {
public:
    ConstantMaterial() : Material() {}
    
    Ray reflect(Object::CollisionData& collision, Ray& incomingRay) override {
        return Ray(collision.position, glm::sphericalRand(1.0));
    }
    glm::dvec3 color(Object::CollisionData& collision, Ray& outgoingRay, glm::dvec3 otherColor = glm::dvec3(1.0)) override {
        return diffuseColor;
    }
    void updateSettings(glm::dvec3 diffuse) {
        diffuseColor = diffuse;
    }
    glm::dvec3 diffuseColor = glm::dvec3(1.0); // albedo, attenuation, etc
};
