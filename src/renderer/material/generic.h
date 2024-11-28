#pragma once
#include "material.h"
#include "../utils/utils.h"

class GenericDiffuse : public Material {
public:
    GenericDiffuse() : Material() {}
    virtual Ray reflect(Object::CollisionData& collision, Ray& incomingRay) override {
        glm::vec3 lambertianReflected = collision.normal + Utils::pointInHemisphere(collision.normal);
        return Ray(collision.position, lambertianReflected);
    }
    virtual glm::vec3 color(Object::CollisionData& collision, Ray& outgoingRay, glm::vec3 otherColor = glm::vec3(1.0f)) override {
        glm::vec3 emmitedColor = glm::vec3(0.0f);
        glm::vec3 diffuseColor = glm::vec3(1.0f);
        float reflectivity = .5f;
        glm::vec3 normalizedDir = glm::normalize(outgoingRay.direction);
        return emmitedColor + reflectivity*otherColor*glm::dot(collision.normal, normalizedDir)*diffuseColor;
    }
};