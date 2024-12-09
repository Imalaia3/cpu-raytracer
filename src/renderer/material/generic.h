#pragma once
#include "material.h"
#include "../utils/utils.h"

class GenericDiffuse : public Material {
public:
    GenericDiffuse() : Material() {}
    Ray reflect(Object::CollisionData& collision, Ray& incomingRay) override {
        glm::dvec3 lambertianReflected = collision.normal + Utils::pointInHemisphere(collision.normal);
        return Ray(collision.position, lambertianReflected);
    }
    glm::dvec3 color(Object::CollisionData& collision, Ray& outgoingRay, glm::dvec3 otherColor = glm::dvec3(1.0)) override {
        glm::dvec3 normalizedDir = glm::normalize(outgoingRay.direction);
        return emmisiveColor + reflectivity*otherColor*glm::dot(collision.normal, normalizedDir)*diffuseColor;
    }

    void updateSettings(glm::dvec3 emmisive, glm::dvec3 diffuse, double reflective) {
        emmisiveColor = emmisive;
        diffuseColor = diffuse;
        reflectivity = reflective;
    }

    glm::dvec3 emmisiveColor = glm::dvec3(0.0);
    glm::dvec3 diffuseColor = glm::dvec3(1.0); // albedo, attenuation, etc
    double reflectivity = 0.5; // how much light is reflected off of the object
};