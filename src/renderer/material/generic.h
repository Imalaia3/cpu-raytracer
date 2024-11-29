#pragma once
#include "material.h"
#include "../utils/utils.h"

class GenericDiffuse : public Material {
public:
    GenericDiffuse() : Material() {}
    Ray reflect(Object::CollisionData& collision, Ray& incomingRay) override {
        glm::vec3 lambertianReflected = collision.normal + Utils::pointInHemisphere(collision.normal);
        return Ray(collision.position, lambertianReflected);
    }
    glm::vec3 color(Object::CollisionData& collision, Ray& outgoingRay, glm::vec3 otherColor = glm::vec3(1.0f)) override {
        glm::vec3 normalizedDir = glm::normalize(outgoingRay.direction);
        return emmisiveColor + reflectivity*otherColor*glm::dot(collision.normal, normalizedDir)*diffuseColor;
    }

    void updateSettings(glm::vec3 emmisive, glm::vec3 diffuse, float reflective) {
        emmisiveColor = emmisive;
        diffuseColor = diffuse;
        reflectivity = reflective;
    }

    glm::vec3 emmisiveColor = glm::vec3(0.0f);
    glm::vec3 diffuseColor = glm::vec3(1.0f); // albedo, attenuation, etc
    float reflectivity = 0.5f; // how much light is reflected off of the object
};