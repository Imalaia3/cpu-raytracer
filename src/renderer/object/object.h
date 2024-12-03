// Base class for all objects.
#pragma once
#include <glm/glm.hpp>
#include <optional>
#include <memory>
#include <string>
#include <limits>
#include "../ray.h"

class Material; // #include <../material/material.h>

class Object {
public:
    enum FaceType {
        FrontFace = 0,
        BackFace
    };

    struct CollisionData {
        std::string objectName;
        float t;
        glm::vec3 position;
        glm::vec3 normal;
        std::shared_ptr<Material> material;
        FaceType faceType;
    };


    Object(glm::vec3 position, std::string objectName, std::shared_ptr<Material> material) : m_position(position), m_name(objectName), m_material(material) {};
    virtual ~Object() = default;
    // if distance is less than threshold collides() will return no value
    virtual std::optional<CollisionData> collides(Ray& ray, float threshold = 0.0f) const = 0;

    glm::vec3 getPosition() const { return m_position; }
    void setPosition(glm::vec3 position) { m_position = position; }
    std::shared_ptr<Material> getMaterial() const {return m_material; }
    const std::string& getObjectName() const { return m_name; }
protected:
    void setFaceType(CollisionData& collision, glm::vec3 incomingRayDir) const;

    std::string m_name;
    glm::vec3 m_position;
    glm::vec3 m_color;
    std::shared_ptr<Material> m_material;
};